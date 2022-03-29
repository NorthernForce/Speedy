// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Wait.h"

Wait::Wait(int cycles) : maxCycles(cycles) {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void Wait::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Wait::Execute() {
  currCycles++;
}

// Called once the command ends or is interrupted.
void Wait::End(bool interrupted) {}

// Returns true when the command should end.
bool Wait::IsFinished() {
  return (currCycles > maxCycles);
}
