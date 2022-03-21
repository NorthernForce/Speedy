#pragma once

#include "frc/Solenoid.h"
#include <memory>

class RecordedSolenoid : public frc::Solenoid {
 public:
    RecordedSolenoid();
    RecordedSolenoid(int pcmModuleID, frc::PneumaticsModuleType moduleType, int solenoidID);
    void Set(bool on) override;
    void LogData();

 private:
    int id;
};