#pragma once

#include <ctre/Phoenix.h>
#include <memory>
#include <string>

class RecordedTalonFX : public WPI_TalonFX {
 public:
    RecordedTalonFX();
    RecordedTalonFX(int id);
    void Set(double value) override;
    void PlaybackSet(double speed, double targetEncoder);
    void SetPeriodic();
    void Set(TalonFXControlMode mode, double value) override;
    void LogData();
    std::string GetDeviceType();

 private:
    const char* device = "Talon FX";
    std::string deviceType = "TalonFX";
    int id;
};