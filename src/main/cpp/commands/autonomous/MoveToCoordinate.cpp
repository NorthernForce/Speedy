/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#include "commands/autonomous/MoveToCoordinate.h"
#include "RobotContainer.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <memory>
#include <cmath>
#include "subsystems/Drivetrain.h"
#include "Robot.h"
#include <vector>

MoveToCoordinate::MoveToCoordinate(CPlane::Point destination, double speed) 
  : baseSpeed(speed), destination(destination) {
  AddRequirements(RobotContainer::drivetrain.get());
  SetName("MoveToCoordinate");
}

// Called when the command is initially scheduled.
void MoveToCoordinate::Initialize() {}

double MoveToCoordinate::Distance(double x1, double x2, double y1, double y2) {
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double MoveToCoordinate::Limit(double value, double limit) {
  return std::min(std::max(value, -limit), limit);
}

double MoveToCoordinate::DrivePower() {
  distanceToDestination = Distance(0, destination.x, 0, destination.y);
  if (distanceToDestination >= 72.0) {
    driveSpeed = baseSpeed;
  }
  else {
    driveSpeed = Limit(drivePID.Calculate(distanceToDestination), baseSpeed);
  }
  
  return driveSpeed;
}

double MoveToCoordinate::TurnPower() {
  angleToDestination = RobotContainer::navigation->AngleToPoint(destination.x, destination.y);
  if (abs(angleToDestination) >= 90.0) {
    if (angleToDestination > 0.0) {
      turnSpeed = baseSpeed;
    }
    else {
      turnSpeed = -baseSpeed;
    }
  }
  else {
    turnSpeed = Limit(turnPID.Calculate(distanceToDestination), baseSpeed);
  }
  
  return driveSpeed;
}

// Called repeatedly when this Command is scheduled to run
void MoveToCoordinate::Execute() {
  RobotContainer::drivetrain->Drive(DrivePower(), TurnPower());
}  

// Called once the command ends or is interrupted.
void MoveToCoordinate::End(bool interrupted) {
  RobotContainer::drivetrain->Drive(0, 0);
}

// Returns true when the command should end.
bool MoveToCoordinate::IsFinished() {
  if (distanceToDestination < 0.5) {
    finishCounter ++;
  }
  else {
    finishCounter = 0;
  }

  if (finishCounter > 30) {
    return true;
  }
  else {
    return false;
  }
}