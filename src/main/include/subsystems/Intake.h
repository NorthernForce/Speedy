// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <frc/Solenoid.h>
#include <memory>

enum class ArmState{
    Down,
    Up
};

class Intake : public frc2::SubsystemBase {
 public:
  Intake();
  void ConfigureSpark();
  void Run(bool reverse=false);
  void Stop();
  void SetSpeed(double speed);

  ArmState GetPivot();
  void SetArmState(ArmState state);

  void ArmUp();
  void ArmDown();

  void Periodic() override;

 private:
  ArmState armPosition = ArmState::Up;
  std::unique_ptr<rev::CANSparkMax> intakeSpark;
  std::unique_ptr<frc::Solenoid> arm;
};
