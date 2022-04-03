// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/NoSensorClimbLower.h"
#include "RobotContainer.h"

NoSensorClimbLower::NoSensorClimbLower() {
  // Use addRequirements() here to declare subsystem dependencies.
    AddRequirements(RobotContainer::climber.get());
}

// Called repeatedly when this Command is scheduled to run
void NoSensorClimbLower::Execute() {
    RobotContainer::climber->Lower();
}

// Called once the command ends or is interrupted.
void NoSensorClimbLower::End(bool interrupted) {
    RobotContainer::climber->Stop();
}

// Returns true when the command should end.
bool NoSensorClimbLower::IsFinished() {
  return false;
}
