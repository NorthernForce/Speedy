// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <memory>
#include <frc/DigitalInput.h>

#include <frc/Solenoid.h>
#include <ctre/Phoenix.h>

enum class PivotState {
    Down,
    Up
};

enum class HookState {
    Down,
    Up
};

enum class ClimberState {
    Unknown,
    Down,
    Mid,
    Up
};

class Climber : public frc2::SubsystemBase {
 public:
  Climber();
  void ConfigureController(WPI_TalonFX& controller);

  void PivotUp();
  void PivotDown();

  PivotState GetPivot();
  HookState GetHookState();
  void InitClimberPositionSensors();
  ClimberState GetClimberState(std::vector<frc::DigitalInput*> climberPosition);
  void SetPivot(PivotState state);
  void SetHookState(HookState state);
  void SetClimberState(ClimberState state);

  void Raise(ClimberState state);
  void Lower(ClimberState state);
  void Stop();
  void Periodic() override;

  std::vector<frc::DigitalInput*> climberPosition;

 private:
  std::unique_ptr<frc::Solenoid> climber;
  PivotState pivotPosition;
  HookState hookPosition;
  ClimberState climberState;
  std::unique_ptr<WPI_TalonFX> leftMotor;
  std::unique_ptr<WPI_TalonFX> rightMotor;
};
