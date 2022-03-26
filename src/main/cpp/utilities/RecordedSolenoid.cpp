#include "utilities/RecordedSolenoid.h"
#include "RobotContainer.h"

const std::string RecordedSolenoid::deviceType = "Solenoid";

RecordedSolenoid::RecordedSolenoid(int pcmModuleID, frc::PneumaticsModuleType moduleType, int solenoidID)
 : frc::Solenoid(pcmModuleID, moduleType, solenoidID) {
    RobotContainer::autoRecorder->AddSolenoid(this);
}

void RecordedSolenoid::LogData() {
    units::millisecond_t startTime = RobotContainer::autoRecorder->GetStartTime();
    units::millisecond_t time = RobotContainer::autoRecorder->GetCurrentTime();
    units::millisecond_t deltaTime = time - startTime;

    RobotContainer::autoRecorder->Write({
        std::to_string(frc::Solenoid::GetChannel()),
        deviceType,
        std::to_string(frc::Solenoid::Get()),
        std::to_string(deltaTime.value()),
        "N/A"
    });
}

std::string RecordedSolenoid::GetDeviceType() {
    return deviceType;
}