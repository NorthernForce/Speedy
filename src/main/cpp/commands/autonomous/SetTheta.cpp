// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/SetTheta.h"

SetTheta::SetTheta(units::degree_t theta) : theta(theta) {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void SetTheta::Initialize() {
  RobotContainer::coordinates->SetTheta(theta);
}

// Called repeatedly when this Command is scheduled to run
void SetTheta::Execute() {}

// Called once the command ends or is interrupted.
void SetTheta::End(bool interrupted) {}

// Returns true when the command should end.
bool SetTheta::IsFinished() {
  return false;
}
