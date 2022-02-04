// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <AHRS.h>

class IMU : public frc2::SubsystemBase {
 public:
  IMU();
  void Periodic() override;
  double GetRollAngle();
  double GetRotation();
  void ZeroRotation();
  void Reset();

 private:
    std::unique_ptr<AHRS> ahrs;
};
