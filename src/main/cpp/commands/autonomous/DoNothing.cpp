// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/DoNothing.h"

DoNothing::DoNothing() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Returns true when the command should end.
bool DoNothing::IsFinished() {
  return true;
}
