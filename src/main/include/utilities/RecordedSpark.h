#pragma once

#include "rev/CANSparkMax.h"
#include <memory>
#include <string>

class RecordedSpark : public rev::CANSparkMax {
 public:
    RecordedSpark();
    RecordedSpark(int id, rev::CANSparkMaxLowLevel::MotorType type);
    void LogData();
    std::string GetDeviceType();

    static const std::string deviceType;
};