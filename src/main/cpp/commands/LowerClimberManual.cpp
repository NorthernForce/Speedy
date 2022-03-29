// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/LowerClimberManual.h"
#include "RobotContainer.h"

LowerClimberManual::LowerClimberManual() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::climber.get());
}

// Called when the command is initially scheduled.
void LowerClimberManual::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void LowerClimberManual::Execute() {
  RobotContainer::climber->Lower();
}

// Called once the command ends or is interrupted.
void LowerClimberManual::End(bool interrupted) {
  RobotContainer::climber->Stop();
}

// Returns true when the command should end.
bool LowerClimberManual::IsFinished() {
  return false;
}
