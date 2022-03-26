#include "utilities/RecordedSpark.h"
#include "RobotContainer.h"

RecordedSpark::RecordedSpark(int id, rev::CANSparkMaxLowLevel::MotorType type) 
 : CANSparkMax(id, type) {
    auto p = this;
    RobotContainer::autoRecorder->AddSpark(&p);
 }

void RecordedSpark::Set(double value) {
    printf("setting a sparko to %f\n", value);
    CANSparkMax::Set(value);
}

void RecordedSpark::LogData() {
    units::millisecond_t startTime = RobotContainer::autoRecorder->GetStartTime();
    units::millisecond_t time = RobotContainer::autoRecorder->GetCurrentTime();
    units::millisecond_t deltaTime = time - startTime;

    double speed = CANSparkMax::Get();
    RobotContainer::autoRecorder->Write({
        std::to_string(CANSparkMax::GetDeviceId()),
        deviceType,
        "N/A",
        std::to_string(deltaTime.value()),
        std::to_string(speed)
    });
}

std::string RecordedSpark::GetDeviceType() {
    return deviceType;
}