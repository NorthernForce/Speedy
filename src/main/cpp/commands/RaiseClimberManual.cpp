// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/RaiseClimberManual.h"
#include "RobotContainer.h"

RaiseClimberManual::RaiseClimberManual() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::climber.get());
}

// Called when the command is initially scheduled.
void RaiseClimberManual::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RaiseClimberManual::Execute() {
  RobotContainer::climber->Raise();
}

// Called once the command ends or is interrupted.
void RaiseClimberManual::End(bool interrupted) {
  RobotContainer::climber->Stop();
}

// Returns true when the command should end.
bool RaiseClimberManual::IsFinished() {
  return false;
}
