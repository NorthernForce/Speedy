/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


#include "commands/autonomous/MoveToCoordinate.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <memory>
#include <cmath>
#include "subsystems/Drivetrain.h"
#include "Robot.h"
#include <vector>

MoveToCoordinate::MoveToCoordinate(CPlane::Point destination, double speed, bool stop) 
  : destination(destination), baseSpeed(speed), stopAtPoint(stop) {
  AddRequirements(RobotContainer::drivetrain.get());
  SetName("MoveToCoordinate");
}

MoveToCoordinate::MoveToCoordinate(double xDestination, double yDestination, double speed, bool stop)
: baseSpeed(speed), stopAtPoint(stop) {
  AddRequirements(RobotContainer::drivetrain.get());
  SetName("MoveToCoordinate");
  units::inch_t x{xDestination};
  units::inch_t y{yDestination};
  destination = CPlane::Point(x, y, false);
}

// Called when the command is initially scheduled.
void MoveToCoordinate::Initialize() {
  if (destination.relative) {
    destination = destination.Add(RobotContainer::coordinates->GetLocation());
  }
  // frc::SmartDashboard::PutNumber("driveP:", 0);
  // frc::SmartDashboard::PutNumber("driveI:", 0);
  // frc::SmartDashboard::PutNumber("driveD:", 0);
  // frc::SmartDashboard::PutNumber("turnP:", 0);
  // frc::SmartDashboard::PutNumber("turnI:", 0);
  // frc::SmartDashboard::PutNumber("turnD:", 0);

  driveP = frc::SmartDashboard::GetNumber("driveP:", driveP);
  driveI = frc::SmartDashboard::GetNumber("driveI:", driveI);
  driveD = frc::SmartDashboard::GetNumber("driveD:", driveD);

  driveP = frc::SmartDashboard::GetNumber("turnP:", turnP);
  driveI = frc::SmartDashboard::GetNumber("turnI:", turnI);
  driveD = frc::SmartDashboard::GetNumber("turnD:", turnD);
}

double MoveToCoordinate::Limit(double value, double limit) {
  return std::min(std::max(value, -limit), limit);
}

double MoveToCoordinate::DrivePower() {
  frc2::PIDController drivePID{driveP, driveI, driveD};

  distanceToDestination = RobotContainer::navigation->DistanceToPoint(destination);
  if (distanceToDestination >= 72_in) {
    driveSpeed = baseSpeed;
  }
  else {
    driveSpeed = Limit(drivePID.Calculate(distanceToDestination.value(), 0), baseSpeed);
  }
  
  return driveSpeed;
}

double MoveToCoordinate::TurnPower() {
  frc2::PIDController turnPID{turnP, turnI, turnD};


  angleToDestination = RobotContainer::navigation->AngleToPoint(destination);
  if (units::math::abs(angleToDestination) >= 90_deg) {
    if (angleToDestination > 0_deg) {
      turnSpeed = baseSpeed;
    }
    else {
      turnSpeed = -baseSpeed;
    }
  }
  else {
    turnSpeed = Limit(turnPID.Calculate(angleToDestination.value(), 0), baseSpeed);
  }

  return turnSpeed;
}

bool MoveToCoordinate::StopFinish() {
  if (stopAtPoint) {

    if (distanceToDestination < 0.5_in) {
      finishCounter ++;
    }
    else {
      finishCounter = 0;
    }

    return finishCounter > 30;
  }
  else {
    return false;
  }
}

bool MoveToCoordinate::SpeedFinish() {
  if (!stopAtPoint && distanceToDestination < 3.0_in) {
    return true;
  }
  else {
    return false;
  }
}

// Called repeatedly when this Command is scheduled to run
void MoveToCoordinate::Execute() {
  printf("Dist Err %f: \n", distanceToDestination);
  // printf("Ang Err %f: \n", angleToDestination);

  // frc::SmartDashboard::PutNumber("driveP:", driveP);
  // frc::SmartDashboard::PutNumber("driveI:", driveI);
  // frc::SmartDashboard::PutNumber("driveD:", driveD);
  RobotContainer::drivetrain->Drive(DrivePower(), TurnPower());
}  

// Called once the command ends or is interrupted.
void MoveToCoordinate::End(bool interrupted) {
  RobotContainer::drivetrain->Drive(0, 0);
}

// Returns true when the command should end.
bool MoveToCoordinate::IsFinished() { return (StopFinish() || SpeedFinish()); }
 