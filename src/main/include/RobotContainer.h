// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>
#include "OI.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "Constants.h"

#include "subsystems/Drivetrain.h"
#include "subsystems/IMU.h"
#include "subsystems/Intake.h"
#include "subsystems/Navigation.h"
#include "subsystems/PCM.h"
#include "subsystems/Coordinates.h"
#include "subsystems/Climber.h"
#include "subsystems/Ultrasonic.h"

#include "commands/autonomous/ShootThenCrossLine.h"

#include "utilities/FMSComms.h"
#include "utilities/TXTInterface.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();
  static std::shared_ptr<OI> oi;
  static std::shared_ptr<Drivetrain> drivetrain;
  static std::shared_ptr<IMU> imu;
  static std::shared_ptr<Intake> intake;
  static std::shared_ptr<Navigation> navigation;
  static std::shared_ptr<PCM> pcm;
  static std::shared_ptr<Coordinates> coordinates;
  static std::shared_ptr<Climber> climber;
  static std::shared_ptr<FMSComms> fmsComms;
  static std::shared_ptr<ShootThenCrossLine> shootThenCrossLine;
  static std::shared_ptr<Ultrasonic> ultrasonic;
  static std::shared_ptr<TXTInterface> txtInterface;

 private:
  // The robot's subsystems and commands are defined here...
  void InitSubsystems();
  void InitDefaultCommands();
};
