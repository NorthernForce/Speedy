// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/AutoRecorder.h"
#include "utilities/CSVInterface.h"
#include "frc2/command/Subsystem.h"
#include "frc/smartdashboard/SmartDashboard.h"

#include <utility>

AutoRecorder::AutoRecorder() {
    isRecording = false;
    isPlayingBack = false;
    frc::SmartDashboard::PutString("AutoRecorder Name: ", "NULL");
}

void AutoRecorder::StartRecording() {
    if (isPlayingBack)
        isPlayingBack = false;
    sequenceName = frc::SmartDashboard::GetString("AutoRecorder Name: ", "NULL");
    csvInterface = std::make_shared<CSVInterface>("/home/lvuser/" + sequenceName + ".csv");
    if (sequenceName != "NULL")
        isRecording = true;
    startTime = GetCurrentTime();
}

void AutoRecorder::StopRecording() {
    isRecording = false;
}

bool AutoRecorder::GetIsRecording() {
    return isRecording;
}

// This function is called automatically by 'Recorded' devices to add themselves
// to their corresponding std::vector for logging
void AutoRecorder::AddTalon(RecordedTalonFX* device) {
    recordedTalons.push_back(device);
}

// This function is called automatically by 'Recorded' devices to add themselves
// to their corresponding std::vector for logging
void AutoRecorder::AddSpark(RecordedSpark* device) {
    recordedSparks.push_back(device);
}

// This function is called automatically by 'Recorded' devices to add themselves
// to their corresponding std::vector for logging
void AutoRecorder::AddSolenoid(RecordedSolenoid* device) {
    recordedSolenoids.push_back(device);
}

// milliseconds since epoch
units::millisecond_t AutoRecorder::GetCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    auto val = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
    int64_t currentTime = val.count();
    return units::millisecond_t(currentTime);
}

// milliseconds since epoch
units::millisecond_t AutoRecorder::GetStartTime() {
    return startTime;
}

// Format: ID, device, (encoder) position, timestamp, motor speed
void AutoRecorder::Write(const std::vector<std::string>& data) {
    std::string buffer = "";
    std::string separator = ",";
    for (auto dataPoint : data) {
        buffer += (dataPoint + separator);
    }
    csvInterface->WriteLine(buffer);
}

void AutoRecorder::Periodic() {
    RecordPeriodic();
    PlaybackPeriodic();
}

void AutoRecorder::StartPlayback() {
    playbackTooSlowCount = 0;
    playbackTooFastCount = 0;
    printf("start playback\n");
    sequenceName = frc::SmartDashboard::GetString("AutoRecorder Name: ", "NULL");
    csvInterface = std::make_shared<CSVInterface>("/home/lvuser/" + sequenceName + ".csv");
    MapDevicesWithIDs();
    if (isRecording)
        isRecording = false;
    if (sequenceName != "NULL")
        isPlayingBack = true;
    startTime = GetCurrentTime();
}

void AutoRecorder::StopPlayback() {
    isPlayingBack = false;
}

bool AutoRecorder::GetIsPlayingBack() {
    return isPlayingBack;
}

//Mapping indexes of recorded devices in their respective arrays to their
// CAN/PCM IDs gives faster runtime results when playing back a routine
void AutoRecorder::MapDevicesWithIDs() {
    for (size_t i=0; i<recordedTalons.size(); i++) {
        int id = recordedTalons[i]->GetDeviceID();
        recordedTalonIDs.insert(std::pair{id, i});
    }
    for (size_t i=0; i<recordedSparks.size(); i++) {
        int id = recordedSparks[i]->GetDeviceId();
        recordedSparkIDs.insert(std::pair{id, i});
    }
    for (size_t i=0; i<recordedSolenoids.size(); i++) {
        int id = recordedSolenoids[i]->GetChannel();
        recordedSolenoidIDs.insert(std::pair{id, i});
    }
}

void AutoRecorder::RecordPeriodic() {
    if (isRecording) {
        for (auto device : recordedTalons) {
            device->LogData();
        }
        for (auto device : recordedSparks) {
            device->LogData();
        }
        for (auto device : recordedSolenoids) {
            device->LogData();
        }
    }
}

void AutoRecorder::ProcessReadDataChunk() {
    size_t numOfRecordedDevices = recordedTalons.size() + recordedSparks.size() + recordedSolenoids.size();
    for (size_t i=0; i<numOfRecordedDevices; i++) {
        AutoAdjustPlaybackSpeed();
    }
    frc::SmartDashboard::PutNumber("Playback Too Slow Count:", playbackTooSlowCount);   
    frc::SmartDashboard::PutNumber("Playback Too Fast Count:", playbackTooFastCount); 
}

void AutoRecorder::AutoAdjustPlaybackSpeed() {
    units::millisecond_t time = csvInterface->GetLastTime();
    if (IsPlaybackTooFast(time) && time != -1_ms) {
        //skip reading, but consider writing previous values to make motors happy
        ProcessPlaybackData(prevData);
        playbackTooFastCount++;
    }
    else if (IsPlaybackTooSlow(time) && time != -1_ms) {
        for (size_t j=0; j<2; j++) {
            PlaybackData data = UpdatePlaybackData();
            prevData = data;
            ProcessPlaybackData(data);
        }
        playbackTooSlowCount++;
    }
    else {
        PlaybackData data = UpdatePlaybackData();
        prevData = data;
        ProcessPlaybackData(data);
    }
}

bool AutoRecorder::IsPlaybackTooSlow(units::millisecond_t time) {
    auto playbackTime = GetCurrentTime() - startTime;
    return (playbackTime > time + 20.05_ms); //consider adding a couple miliseconds to time for slight margin of error
}

bool AutoRecorder::IsPlaybackTooFast(units::millisecond_t time) {
    auto playbackTime = GetCurrentTime() - startTime;
    return (playbackTime < time + 19.95_ms); //consider subtracting a couple miliseconds from time for slight margin of error
}

AutoRecorder::PlaybackData AutoRecorder::UpdatePlaybackData() {
    PlaybackData data;
    std::vector<std::string> line = csvInterface->ReadLine();
    data.id = std::stoi(line[0]);
    data.device = std::move(line[1]);
    if (line[2] != "N/A")
        data.pos = std::stod(line[2]);
    data.time = units::millisecond_t(std::stol(line[3]));
    if (line[4] != "N/A")
        data.speed = std::stod(line[4]);
    return data;
}

void AutoRecorder::ProcessPlaybackData(const PlaybackData& data) {
    if (data.device == RecordedTalonFX::deviceType) {
        int talonIdx = recordedTalonIDs[data.id];
        // printf("talon index: %i\n", talonIdx);
        recordedTalons[talonIdx]->PlaybackSet(data.speed, data.pos);
    }
    else if (data.device == RecordedSpark::deviceType) {
        int sparkIdx = recordedSparkIDs[data.id];
        //printf("spark index: %i\n", sparkIdx);
        recordedSparks[sparkIdx]->Set(data.speed);
    }
    else if (data.device == RecordedSolenoid::deviceType) {
        int solenoidIdx = recordedSolenoidIDs[data.id];
        //printf("solenoid index: %i\n", solenoidIdx);
        recordedSolenoids[solenoidIdx]->Set(bool(data.pos));
    }
    // std::cout << "recorded device:" << PlaybackData::device << '\n';
    // std::cout << "recorded id:" << PlaybackData::id << '\n';
    // std::cout << "recorded position:" << PlaybackData::pos << '\n';
    // frc::SmartDashboard::PutString("recorded device:", PlaybackData::device);
    // frc::SmartDashboard::PutNumber("recorded id:", PlaybackData::id);
    // frc::SmartDashboard::PutNumber("recorded position:", PlaybackData::pos);


}

void AutoRecorder::PlaybackPeriodic() {
    if (isPlayingBack) {
        ProcessReadDataChunk();
    }
}