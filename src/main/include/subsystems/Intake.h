// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h>
#include <frc/Solenoid.h>
#include "Constants.h"
#include <memory>

class Intake : public frc2::SubsystemBase {
 public:
  enum class ArmState {
    Down,
    Up
  };
  enum class IntakeDirection {
    outtake,
    intake
  };
  Intake();
  void ConfigureSpark(rev::CANSparkMax& spark);
  rev::SparkMaxRelativeEncoder SparkEncoderPosition();
  void ConfigureController();
  void Run(IntakeDirection direction);
  void ShootHighRPM(double rpm);
  void ShootHigh();
  void ReverseHigh();
  void UltraShoot();
  void Stop();
  void StopHigh();
  void SetSpeed(double speed);
  int GetCurrentRPM();
  int GetError();

  ArmState GetPivot();
  void SetArmState(ArmState state);

  void ArmUp();
  void ArmDown();

  ArmState armPosition;

  std::unique_ptr<rev::CANSparkMax> intakeTopSpark;
  std::unique_ptr<rev::CANSparkMax> intakeBottomSpark;

 private:
  //std::unique_ptr<rev::CANSparkMax> intakeTopSpark;
  //std::unique_ptr<rev::CANSparkMax> intakeBottomSpark;
  std::unique_ptr<WPI_TalonFX> highMotor;
  std::unique_ptr<frc::Solenoid> arm;

  double ultraDist;
  const int currentLimit = 60;
  const int secondaryCurrentLimit = 80;
};
