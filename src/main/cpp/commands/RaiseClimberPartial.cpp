// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/RaiseClimberPartial.h"
#include "commands/RaiseClimber.h"

RaiseClimberPartial::
RaiseClimberPartial() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::climber.get());
}

// Called when the command is initially scheduled.
void RaiseClimberPartial::Initialize() {
  RobotContainer::climber->ResetSpool();
}

// Called repeatedly when this Command is scheduled to run
void RaiseClimberPartial::Execute() {
  RobotContainer::climber->Raise();
  frc::SmartDashboard::PutBoolean("RaisePrtl: ", true);
}

// Called once the command ends or is interrupted.
void RaiseClimberPartial::End(bool interrupted) {
  RobotContainer::climber->Stop();
  frc::SmartDashboard::PutBoolean("RaisePrtl: ", false);

}

// Returns true when the command should end.
bool RaiseClimberPartial::IsFinished() {
  return (abs(RobotContainer::climber->SpoolRotations()) > 1.5);
}
