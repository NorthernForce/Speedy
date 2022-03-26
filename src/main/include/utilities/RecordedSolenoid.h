#pragma once

#include "frc/Solenoid.h"
#include <memory>
#include <string>

class RecordedSolenoid : public frc::Solenoid {
 public:
    RecordedSolenoid();
    RecordedSolenoid(int pcmModuleID, frc::PneumaticsModuleType moduleType, int solenoidID);
    void GetCurrentTime();
    void LogData();
    std::string GetDeviceType();

    static const std::string deviceType;
};