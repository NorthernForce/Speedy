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
void SmartBarGrab::Initialize() {}

void SmartBarGrab::ControlClimberPivot() {
  if (RobotContainer::imu->GetPitchAngle() < -35) {
    RobotContainer::climber->PivotDown();
  }
}

void SmartBarGrab::TryGrab() {
  if (RobotContainer::imu->GetPitchAngle() > -10) {
    RobotContainer::climber->PivotUp();
  }
}

// Called repeatedly when this Command is scheduled to run
void SmartBarGrab::Execute() {}

// Called once the command ends or is interrupted.
void SmartBarGrab::End(bool interrupted) {}

// Returns true when the command should end.
bool SmartBarGrab::IsFinished() {
  return false;
}
