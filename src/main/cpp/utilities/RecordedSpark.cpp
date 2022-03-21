#include "utilities/RecordedSpark.h"
#include "RobotContainer.h"

#include <chrono>
#include <sys/time.h>
#include <ctime>

RecordedSpark::RecordedSpark(int id, rev::CANSparkMaxLowLevel::MotorType type) 
 : CANSparkMax(id, type) {
    RobotContainer::autoRecorder->AddDevice(this);
 }

void RecordedSpark::Set(double value) {
    CANSparkMax::Set(value);
    //LogData();
}

void RecordedSpark::LogData() {
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    auto val = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
    long time = val.count();

    RobotContainer::autoRecorder->Write({
        std::to_string(id),
        "SparkMax",
        std::to_string(CANSparkMax::GetEncoder().GetPosition()),
        std::to_string(time),
        std::to_string(CANSparkMax::Get())
    });
}