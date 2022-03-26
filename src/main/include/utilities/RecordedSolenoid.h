#pragma once

#include "frc/Solenoid.h"
#include <memory>
#include <string>

class RecordedSolenoid : public frc::Solenoid {
 public:
    RecordedSolenoid();
    RecordedSolenoid(int pcmModuleID, frc::PneumaticsModuleType moduleType, int solenoidID);
    void Set(bool on) override;
    void GetCurrentTime();
    void LogData();
    std::string GetDeviceType();

 private:
    int id;
    long time = 0;
    bool isSolenoidOn;
    std::string deviceType = "Solenoid";
};