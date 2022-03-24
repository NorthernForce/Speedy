// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/SmartBarGrab.h"
#include "RobotContainer.h"

SmartBarGrab::SmartBarGrab() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::climber.get());
}

// Called when the command is initially scheduled.
void SmartBarGrab::Initialize() {
  prevTip=0;
}

void SmartBarGrab::ControlClimberPivot() {
  if (RobotContainer::imu->GetPitchAngle() < -18) {
    RobotContainer::climber->PivotDown();
  }
}

void SmartBarGrab::TryGrab() {
  if (RobotContainer::imu->GetPitchAngle() > -12) {
    RobotContainer::climber->PivotUp();
  }
}

// Called repeatedly when this Command is scheduled to run
void SmartBarGrab::Execute() {
  if (abs(prevTip - RobotContainer::imu->GetTipAngle()) < 1) {
    stableCycles++;
  }
  else {
    stableCycles=0;
  }
  prevTip = RobotContainer::imu->GetTipAngle();
}

// Called once the command ends or is interrupted.
void SmartBarGrab::End(bool interrupted) {}

// Returns true when the command should end.
bool SmartBarGrab::IsFinished() {
  return (stableCycles > 30);
}
