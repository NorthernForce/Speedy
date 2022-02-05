// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <memory>

class Intake : public frc2::SubsystemBase {
 public:
  Intake();
  void ConfigureSpark();
  void Run(bool reverse=false);
  void Stop();
  void SetSpeed(double speed);
  void Periodic() override;

 private:
  std::unique_ptr<rev::CANSparkMax> intakeSpark;
  units::unit_t<units::time::second> rampRate = 1_s;
};
