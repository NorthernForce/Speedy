/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "RobotContainer.h"
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "frc2/command/PIDCommand.h"
#include <memory>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class MoveToCoordinate
    : public frc2::CommandHelper<frc2::CommandBase, MoveToCoordinate> {
 public:
  MoveToCoordinate(CPlane::Point destination, double speed=0.3, bool stop=true);
  MoveToCoordinate(double xDestination, double yDestination, double speed=0.3, bool stop=true);

  void Initialize() override;

  // double RemoveJumps(double angToFinalWithJumps);

  double Limit(double value, double limit=0.5);

  double DrivePower();

  double TurnPower();

  bool StopFinish();

  bool SpeedFinish();

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  CPlane::Point destination{0_in, 0_in};
  double baseSpeed;
  bool stopAtPoint;

  double turnP;
  double turnI;
  double turnD;
  double driveP;
  double driveI;
  double driveD;

  // frc2::PIDController turnPID;
  // frc2::PIDController drivePID;

  units::inch_t distanceToDestination;
  units::degree_t angleToDestination;

  double turnSpeed;
  double driveSpeed;

  int finishCounter = 0;
};
