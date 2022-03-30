// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/DoNothing.h"

DoNothing::DoNothing() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void DoNothing::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DoNothing::Execute() {}

// Called once the command ends or is interrupted.
void DoNothing::End(bool interrupted) {}

// Returns true when the command should end.
bool DoNothing::IsFinished() {
  return true;
}
