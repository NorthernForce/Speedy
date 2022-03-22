// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/AutoRecorder.h"
#include "utilities/CSVInterface.h"
#include "frc2/command/Subsystem.h"

#include <utility>

AutoRecorder::AutoRecorder() {
    csvInterface = std::make_shared<CSVInterface>("/home/lvuser/auto1.csv");
}

void AutoRecorder::Start() {
    isRecording = true;
}

void AutoRecorder::Stop() {
    isRecording = false;
}

bool AutoRecorder::GetIsRecording() {
    return isRecording;
}

// This function is called automatically by 'Recorded' devices to add themselves
// to their corresponding std::vector for logging
void AutoRecorder::AddDevice(RecordedTalonFX* device) {
    recordedTalons.push_back(device);
}

// This function is called automatically by 'Recorded' devices to add themselves
// to their corresponding std::vector for logging
void AutoRecorder::AddDevice(RecordedSpark* device) {
    recordedSparks.push_back(device);
}

// This function is called automatically by 'Recorded' devices to add themselves
// to their corresponding std::vector for logging
void AutoRecorder::AddDevice(RecordedSolenoid* device) {
    recordedSolenoids.push_back(device);
}

// Format: CAN ID, device, (encoder) position, timestamp, motor speed
void AutoRecorder::Write(std::vector<std::string> data) {
    std::string buffer = "";
    for (auto dataPoint : data) {
        buffer += (dataPoint += std::to_string(','));
    }
    csvInterface->WriteLine(buffer);
}

void AutoRecorder::Periodic() {
    printf("periodic recording\n");

    if (isRecording && csvInterface->IsInitialized()) {
        printf("runnnnnnn\n");
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