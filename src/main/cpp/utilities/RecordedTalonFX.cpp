#include "utilities/RecordedTalonFX.h"
#include "RobotContainer.h"
    
RecordedTalonFX::RecordedTalonFX(int id) 
 :  BaseMotorController(id, device),
    BaseTalon(id, device),
    TalonFX(id),
    WPI_BaseMotorController(id, device),
    WPI_TalonFX(id),
    id(id)
{
    WPI_TalonFX::SetSelectedSensorPosition(0);
    auto p = this;
    RobotContainer::autoRecorder->AddTalon(&p);
}

void RecordedTalonFX::LogData() {
    units::millisecond_t startTime = RobotContainer::autoRecorder->GetStartTime();
    units::millisecond_t time = RobotContainer::autoRecorder->GetCurrentTime();
    units::millisecond_t deltaTime = time - startTime;

    RobotContainer::autoRecorder->Write({
        std::to_string(id),
        deviceType,
        std::to_string(WPI_TalonFX::GetSensorCollection().GetIntegratedSensorPosition()),
        std::to_string(deltaTime.value()),
        std::to_string(WPI_TalonFX::Get())
    });
}

void RecordedTalonFX::Set(double value) {
    position = value;
    WPI_TalonFX::Set(value);
}

void RecordedTalonFX::PlaybackSet(double speed, double targetEncoder) {
    double currentEncoder = GetSensorCollection().GetIntegratedSensorPosition();
    if (abs(currentEncoder) < abs(targetEncoder)*1.02)
        WPI_TalonFX::Set(speed);
}

void RecordedTalonFX::SetPeriodic() {
    if (position != -2)
        Set(position);
}

void RecordedTalonFX::Set(TalonFXControlMode mode, double value) {
    WPI_TalonFX::Set(mode, value);
}

std::string RecordedTalonFX::GetDeviceType() {
    return deviceType;
}