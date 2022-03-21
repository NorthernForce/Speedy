#pragma once

#include "rev/CANSparkMax.h"
#include <memory>

class RecordedSpark : public rev::CANSparkMax {
 public:
    RecordedSpark();
    RecordedSpark(int id, rev::CANSparkMaxLowLevel::MotorType type);
    void Set(double value) override;
    void LogData();

 private:
    int id;
};