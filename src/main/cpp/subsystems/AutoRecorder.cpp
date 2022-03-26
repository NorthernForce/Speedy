// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/AutoRecorder.h"
#include "utilities/CSVInterface.h"
#include "frc2/command/Subsystem.h"
#include "frc/smartdashboard/SmartDashboard.h"

#include <utility>

//Data read during Playback Mode is stored here
// Note: these values will change frequently
namespace PlaybackData {
    int id;
    std::string device;
    double pos;
    units::millisecond_t time;
    double speed;
}

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
void AutoRecorder::AddTalon(RecordedTalonFX** device) {
    recordedTalons.push_back((*device));
}

// This function is called automatically by 'Recorded' devices to add themselves
// to their corresponding std::vector for logging
void AutoRecorder::AddSpark(RecordedSpark** device) {
    recordedSparks.push_back((*device));
}

// This function is called automatically by 'Recorded' devices to add themselves
// to their corresponding std::vector for logging
void AutoRecorder::AddSolenoid(RecordedSolenoid** device) {
    recordedSolenoids.push_back((*device));
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
void AutoRecorder::Write(std::vector<std::string> data) {
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
    printf("start playback\n");
    startTime = GetCurrentTime();
    sequenceName = frc::SmartDashboard::GetString("AutoRecorder Name: ", "NULL");
    csvInterface = std::make_shared<CSVInterface>("/home/lvuser/" + sequenceName + ".csv");
    MapDevicesWithIDs();
    if (isRecording)
        isRecording = false;
    if (sequenceName != "NULL")
        isPlayingBack = true;
}

void AutoRecorder::StopPlayback() {
    isPlayingBack = false;
}

bool AutoRecorder::GetIsPlayingBack() {
    return isPlayingBack;
}

void AutoRecorder::UpdatePlaybackData() {
    std::vector<std::string> data = csvInterface->ReadLine();
    // if (csvInterface->IsAtEndOfFile())
    //     StopPlayback();
    PlaybackData::id = std::stoi(data[0]);
    PlaybackData::device = data[1];
    if (data[2] != "N/A")
        PlaybackData::pos = std::stod(data[2]);
    PlaybackData::time = units::millisecond_t(std::stol(data[3]));
    if (data[4] != "N/A")
        PlaybackData::speed = std::stod(data[4]);
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
    if (isRecording && csvInterface->IsInitialized()) {
        if (recordedTalons.size() > 0) {
            for (auto device : recordedTalons) {
                if (device != nullptr)
                    device->LogData();
            }
        }
        if (recordedSparks.size() > 0) {
            for (auto device : recordedSparks) {
                if (device != nullptr)
                    device->LogData();
            }
        }
        if (recordedSolenoids.size() > 0) {
            for (auto device : recordedSolenoids) {
                if (device != nullptr)
                    device->LogData();
            }
        }
    }
}

void AutoRecorder::ProcessReadDataChunk() {
    size_t numOfRecordedDevices = 5; //recordedTalons.size() + recordedSparks.size() + recordedSolenoids.size();
    for (size_t i=0; i<numOfRecordedDevices; i++) {
        UpdatePlaybackData();
        // for (auto talon : recordedTalons)
        //     talon->SetPeriodic();
        frc::SmartDashboard::PutString("playback device", PlaybackData::device);
        frc::SmartDashboard::PutNumber("playback dev id", PlaybackData::id);
        frc::SmartDashboard::PutNumber("playback dev speed", PlaybackData::speed);
        frc::SmartDashboard::PutNumber("playback dev pos", PlaybackData::pos);

        if (PlaybackData::device == "TalonFX") {
            int talonIdx = recordedTalonIDs[PlaybackData::id];
            recordedTalons[talonIdx]->Set(PlaybackData::speed);
        }
        else if (PlaybackData::device == "Spark") {
            int sparkIdx = recordedSparkIDs[PlaybackData::id];
            recordedSparks[sparkIdx]->Set(PlaybackData::speed);
        }
        else if (PlaybackData::device == "Solenoid") {
            int solenoidIdx = recordedSolenoidIDs[PlaybackData::id];
            recordedSolenoids[solenoidIdx]->Set(bool(PlaybackData::pos));
        }
    }
}

void AutoRecorder::PlaybackPeriodic() {
    if (isPlayingBack && csvInterface->IsInitialized()) {
        ProcessReadDataChunk();

        if (IsPlaybackTooSlow())
            CorrectPlaybackTooSlow();
    }
}

bool AutoRecorder::IsPlaybackTooSlow() {
    playbackTime = GetCurrentTime() - startTime;
    recordTime = PlaybackData::time;
    return (playbackTime < (recordTime - 19_ms));
}

void AutoRecorder::CorrectPlaybackTooSlow() {
    playbackTime = GetCurrentTime() - startTime;
    recordTime = PlaybackData::time;
    while (playbackTime < (recordTime - 19_ms)) {
        ProcessReadDataChunk();
        playbackTime = GetCurrentTime() - startTime;
        recordTime = PlaybackData::time;
    }
}