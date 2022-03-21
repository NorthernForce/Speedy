#pragma once

#include <ctre/Phoenix.h>
#include <memory>

class RecordedTalonFX : public WPI_TalonFX {
 public:
    RecordedTalonFX();
    RecordedTalonFX(int id);
    void Set(double value) override;

    //void Set(double speed) override;
    void Set(TalonFXControlMode mode, double value) override;
    void LogData();

 private:
    const char* device = "Talon FX";
    int id;
};