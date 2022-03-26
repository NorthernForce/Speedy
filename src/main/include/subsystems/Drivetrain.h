// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/drive/DifferentialDrive.h>
#include "utilities/RecordedTalonFX.h"
#include "Constants.h"

class Drivetrain : public frc2::SubsystemBase {
 public:
  Drivetrain();
  void SetFollowers();
  void SetInvert();
  void ConfigureAllControllers();
  void ConfigureController(RecordedTalonFX& controller, bool isFollower=false);
  void Drive(double speed, double rotation);
  void DriveUsingSpeeds(double leftSpeed, double rightSpeed);
  bool DriveToDistance(double desiredDistance, double speed);
  std::pair<double, double> GetEncoderRotations();
  std::pair<units::inch_t, units::inch_t> GetInchesTravelled();
  double GetAvgEncoderRotations(std::pair<double, double>);
  void SetEncoderPositions(double lt, double rt);
  void PrintEncoderValues();
  double GetLeftRPM();
  double GetRightRPM();
  bool IsTipping();
  void Periodic() override;

  static std::shared_ptr<RecordedTalonFX> leftPrimary;
  static std::shared_ptr<RecordedTalonFX> rightPrimary;
  static std::shared_ptr<frc::DifferentialDrive> robotDrive;
  
 private:
  std::shared_ptr<WPI_TalonFX> leftFollower;
  std::shared_ptr<WPI_TalonFX> rightFollower;
  const int rampRate = 0.2;
  units::degree_t tipAngle = 15_deg;
};
