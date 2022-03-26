#pragma once

#include "rev/CANSparkMax.h"
#include <memory>
#include <string>

class RecordedSpark : public rev::CANSparkMax {
 public:
    RecordedSpark();
    RecordedSpark(int id, rev::CANSparkMaxLowLevel::MotorType type);
    void Set(double value) override;
    void LogData();
    std::string GetDeviceType();

 private:
    int id;
    std::string deviceType = "Spark";
};