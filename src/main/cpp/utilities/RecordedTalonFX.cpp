#include "utilities/RecordedTalonFX.h"
#include "RobotContainer.h"
    
const std::string RecordedTalonFX::deviceType = "Talon FX";

RecordedTalonFX::RecordedTalonFX(int id) 
 :  BaseMotorController(id, deviceType.c_str()),
    BaseTalon(id, deviceType.c_str()),
    TalonFX(id),
    WPI_BaseMotorController(id, deviceType.c_str()),
    WPI_TalonFX(id)
{
    WPI_TalonFX::SetSelectedSensorPosition(0);
    RobotContainer::autoRecorder->AddTalon(this);
}

void RecordedTalonFX::LogData() {
    units::millisecond_t startTime = RobotContainer::autoRecorder->GetStartTime();
    units::millisecond_t time = RobotContainer::autoRecorder->GetCurrentTime();
    units::millisecond_t deltaTime = time - startTime;

    RobotContainer::autoRecorder->Write({
        std::to_string(WPI_TalonFX::GetDeviceID()),
        deviceType,
        std::to_string(WPI_TalonFX::GetSensorCollection().GetIntegratedSensorPosition()),
        std::to_string(deltaTime.value()),
        std::to_string(WPI_TalonFX::Get())
    });
}

void RecordedTalonFX::PlaybackSet(double speed, double targetEncoder) {
    double currentEncoder = GetSensorCollection().GetIntegratedSensorPosition();
    int direction = WPI_TalonFX::GetInverted() ? -1 : 1;

    // If the direction of travel is the same direction as the error
    // in the encoders, then proceed with the direction of travel
    if (speed * direction * (targetEncoder - currentEncoder) > 0) {
        WPI_TalonFX::Set(speed);
    }
    else {
        // We overshot going forwards/backwards so we're going to stop
        // an alternative would be to correct if needed later
        WPI_TalonFX::Set(0);
    }
}

std::string RecordedTalonFX::GetDeviceType() {
    return deviceType;
}