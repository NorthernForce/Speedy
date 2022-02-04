// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <frc/drive/DifferentialDrive.h>

class Drivetrain : public frc2::SubsystemBase {
 public:
  Drivetrain();
  void SetFollowers();
  void SetInvert();
  void ConfigureAllControllers();
  void ConfigureController(WPI_TalonFX& controller, bool isFollower=false);
  void Drive(double speed, double rotation);
  void DriveUsingSpeeds(double leftSpeed, double rightSpeed);
  std::pair<double, double> GetEncoderRotations();
  void SetEncoderPositions(double lt, double rt);
  double GetLeftRPM();
  double GetRightRPM();
  void Periodic() override;

  static std::shared_ptr<WPI_TalonFX> leftPrimary;
  static std::shared_ptr<WPI_TalonFX> rightPrimary;
  static std::shared_ptr<frc::DifferentialDrive> robotDrive;
  
 private:
  std::shared_ptr<WPI_TalonFX> leftFollower;
  std::shared_ptr<WPI_TalonFX> rightFollower;
  const int rampRate = 0.2;
};
