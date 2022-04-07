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
    WPI_TalonFX::SetNeutralMode(ctre::phoenix::motorcontrol::Coast);
    RobotContainer::autoRecorder->AddTalon(this);
}

void RecordedTalonFX::LogData() {
    units::millisecond_t startTime = RobotContainer::autoRecorder->GetStartTime();
    units::millisecond_t time = RobotContainer::autoRecorder->GetCurrentTime();
    units::millisecond_t deltaTime = time - startTime;

    RobotContainer::autoRecorder->Write({
        std::to_string(WPI_TalonFX::GetDeviceID()),
        deviceType,
        std::to_string(GetSensorCollection().GetIntegratedSensorPosition()),
        std::to_string(deltaTime.value()),
        std::to_string(WPI_TalonFX::Get())
    });
}

void RecordedTalonFX::PlaybackSet(double speed, double targetEncoder) {
    double currentEncoder = GetSensorCollection().GetIntegratedSensorPosition();
    int direction = GetInverted() ? -1 : 1;

    double runError = currentEncoder - prevEncoder;
    double targError = targetEncoder - prevTargetEncoder;

    double cycleError = runError - targError;

    // If the direction of travel is the same direction as the error
    // in the encoders, then proceed with the direction of travel
    if (speed * direction * cycleError > 0) {
        // If undershooting, drive faster
        if ((direction * targError) > (direction * runError)) {
            frc::SmartDashboard::PutNumber("undershooting count", undershootingCount);
            undershootingCount++;
            double targetSpeed = speed + speed * cycleError / (Constants::cpr * 20);
            WPI_TalonFX::Set(targetSpeed);
        }
        else
            WPI_TalonFX::Set(speed);
    }
    else {
        // We overshot going forwards/backwards so we're going to slow down
        // an alternative would be to stop
        double targetSpeed = speed - speed * cycleError / (Constants::cpr * 30);
        WPI_TalonFX::Set(targetSpeed);
        frc::SmartDashboard::PutNumber("overshooting count", overshootingCount);
        overshootingCount++;
    }
    prevEncoder = currentEncoder;
    prevTargetEncoder = targetEncoder;
}

std::string RecordedTalonFX::GetDeviceType() {
    return deviceType;
}