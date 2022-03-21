#include "utilities/AutoRecorder.h"
#include "utilities/CSVInterface.h"
#include "frc2/command/Subsystem.h"

#include <utility>

std::shared_ptr<CSVInterface> AutoRecorder::csvInterface;
bool AutoRecorder::isRecording;

AutoRecorder::AutoRecorder() {
    csvInterface = std::make_shared<CSVInterface>("auto.csv");
    isRecording = false;
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