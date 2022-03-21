#include "utilities/RecordedSolenoid.h"
#include "RobotContainer.h"

RecordedSolenoid::RecordedSolenoid(int pcmModuleID, frc::PneumaticsModuleType moduleType, int solenoidID)
 : frc::Solenoid(pcmModuleID, moduleType, solenoidID) {
    RobotContainer::autoRecorder->AddDevice(this);
 }

void RecordedSolenoid::Set(bool on) {
    frc::Solenoid::Set(on);
    //LogData();
}

void RecordedSolenoid::LogData() {
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    auto val = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
    long time = val.count();

    RobotContainer::autoRecorder->Write({
        std::to_string(id),
        "Solenoid",
        std::to_string(frc::Solenoid::Get()),
        std::to_string(time),
    });
}