// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <memory>

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

class Climber : public frc2::SubsystemBase {
 public:
  Climber();
  void ConfigureController(WPI_TalonFX& controller, bool isFollower);
  void PivotUp();
  void PivotDown();
  PivotState GetPivot();
  void Raise();
  void Lower();
  void GetHookState();
  void Periodic() override;

 private:
  std::unique_ptr<frc::Solenoid> leftClimber;
  std::unique_ptr<frc::Solenoid> rightClimber;
  PivotState pivotPosition;
  HookState hookPosition;

  std::unique_ptr<WPI_TalonFX> leftMotor;
  std::unique_ptr<WPI_TalonFX> rightMotor;
};
