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
  void ConfigureSpark(rev::CANSparkMax& spark);
  void Run(bool reverse=false);
  void UltraShoot();
  void Stop();
  void SetSpeed(double speed);

  ArmState GetPivot();
  void SetArmState(ArmState state);

  void ArmUp();
  void ArmDown();

  ArmState armPosition;

 private:
  std::unique_ptr<rev::CANSparkMax> intakeTopSpark;
  std::unique_ptr<rev::CANSparkMax> intakeBottomSpark;
  std::unique_ptr<frc::Solenoid> arm;

  double ultraDist;
};
