#include "utilities/RecordedSolenoid.h"
#include "RobotContainer.h"

RecordedSolenoid::RecordedSolenoid(int pcmModuleID, frc::PneumaticsModuleType moduleType, int solenoidID)
 : frc::Solenoid(pcmModuleID, moduleType, solenoidID) {
    auto p = this;
    RobotContainer::autoRecorder->AddSolenoid(&p);
 }

void RecordedSolenoid::Set(bool on) {
    isSolenoidOn = on;
    printf("setting a solenoid to %i\n", on);
    frc::Solenoid::Set(isSolenoidOn);
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