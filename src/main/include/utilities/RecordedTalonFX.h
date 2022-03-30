#pragma once

#include <ctre/Phoenix.h>
#include <memory>
#include <string>

class RecordedTalonFX : public WPI_TalonFX {
 public:
    RecordedTalonFX() = delete;
    RecordedTalonFX(int id);
    void PlaybackSet(double speed, double targetEncoder);
    void LogData();
    std::string GetDeviceType();

    static const std::string deviceType;
 private:
    int cycleCount = 0;
    int overshootingCount = 0;
    int undershootingCount = 0;
    double prevEncoder = 0;
    double prevTargetEncoder = 0;
};