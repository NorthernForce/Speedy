#pragma once

#include <ctre/Phoenix.h>
#include <memory>

#include "utilities/AutoRecorder.h"

class RecordedTalonFX : public WPI_TalonFX, AutoRecorder {
 public:
    RecordedTalonFX() = delete;
    RecordedTalonFX(int id);
    void Set(double value) override;

 private:
    const char* device = "Talon FX";
    int id;
};