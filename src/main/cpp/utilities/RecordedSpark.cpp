#include "utilities/RecordedSpark.h"
#include "RobotContainer.h"

const std::string RecordedSpark::deviceType = "Spark";

RecordedSpark::RecordedSpark(int id, rev::CANSparkMaxLowLevel::MotorType type) 
 : CANSparkMax(id, type) {
    RobotContainer::autoRecorder->AddSpark(this);
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