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
};