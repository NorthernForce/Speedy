// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/AutoTraverseDouble.h"
#include "commands/autonomous/AutoTraverse.h"

AutoTraverseDouble::AutoTraverseDouble() {
  scheduler.reset(new AutoCommandScheduler({
    new AutoTraverse(),
    new AutoTraverse()
  }));
}

// Called when the command is initially scheduled.
void AutoTraverseDouble::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoTraverseDouble::Execute() {
  scheduler->RunSequential();
}

// Called once the command ends or is interrupted.
void AutoTraverseDouble::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoTraverseDouble::IsFinished() {
  return scheduler->IsFinished();
}
