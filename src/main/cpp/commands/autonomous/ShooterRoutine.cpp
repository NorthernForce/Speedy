// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/ShooterRoutine.h"

ShooterRoutine::ShooterRoutine() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void ShooterRoutine::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ShooterRoutine::Execute() {
    
}

// Called once the command ends or is interrupted.
void ShooterRoutine::End(bool interrupted) {}

// Returns true when the command should end.
bool ShooterRoutine::IsFinished() {
  return false;
}
