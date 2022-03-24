// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <memory>

#include <frc/Solenoid.h>
#include <ctre/Phoenix.h>
#include <frc/DigitalInput.h>

enum class PivotState {
    Down,
    Up
};

enum class HookState {
    Down,
    Up
};

class Climber : public frc2::SubsystemBase {
 public:
  Climber();
  void ConfigureController(WPI_TalonFX& controller);
  void PivotUp();
  void PivotDown();
  PivotState GetPivot();
  void SetPivot(PivotState state);
  void Raise();
  void Lower();
  void Stop();
  double SpoolRotations();
  void ResetSpool();
  bool TooTall();
  void CheckHeight();
  HookState GetHookState();
  void SetHookState(HookState state);
  void SetPivot(HookState state);
  bool GetOpticalSensor(int sensor);
  void PrintOpticalSensors();
  void Periodic() override;

 private:
  std::unique_ptr<frc::Solenoid> climber;
  PivotState pivotPosition;
  HookState hookPosition;
  std::unique_ptr<WPI_TalonFX> leftMotor;
  std::unique_ptr<WPI_TalonFX> rightMotor;

  bool heightCheckNeeded = true;

  std::unique_ptr<frc::DigitalInput> bottom;
  std::unique_ptr<frc::DigitalInput> middle;
  std::unique_ptr<frc::DigitalInput> top;

  uint8_t heightWaitCycles;
};
