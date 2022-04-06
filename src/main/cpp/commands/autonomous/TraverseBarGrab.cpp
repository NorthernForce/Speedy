// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/TraverseBarGrab.h"
#include "RobotContainer.h"

TraverseBarGrab::TraverseBarGrab() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::climber.get());
}

// Called when the command is initially scheduled.
void TraverseBarGrab::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TraverseBarGrab::Execute() {
  bool swingMax = (abs(RobotContainer::imu->GetPitchSpeed()) < 2);
  if (RobotContainer::imu->GetPitchAngle() < armDown && swingMax) {
    RobotContainer::climber->PivotDown();
  }
  else if (RobotContainer::imu->GetPitchAngle() > tryGrab && swingMax) {
    RobotContainer::climber->PivotUp();
    finished = true;
  }
}

// Called once the command ends or is interrupted.
void TraverseBarGrab::End(bool interrupted) {}

// Returns true when the command should end.
bool TraverseBarGrab::IsFinished() { return finished; }
