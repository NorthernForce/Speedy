// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ResetSpool.h"
#include "RobotContainer.h"

ResetSpool::ResetSpool() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void ResetSpool::Initialize() {
  RobotContainer::climber->ResetSpool();
}

// Called repeatedly when this Command is scheduled to run
void ResetSpool::Execute() {}

// Called once the command ends or is interrupted.
void ResetSpool::End(bool interrupted) {}

// Returns true when the command should end.
bool ResetSpool::IsFinished() {
  return true;
}
