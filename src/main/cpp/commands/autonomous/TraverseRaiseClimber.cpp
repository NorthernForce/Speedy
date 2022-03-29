// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/TraverseRaiseClimber.h"
#include "RobotContainer.h"

TraverseRaiseClimber::TraverseRaiseClimber() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::climber.get());
}

// Called when the command is initially scheduled.
void TraverseRaiseClimber::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TraverseRaiseClimber::Execute() {
  if (RobotContainer::imu->GetPitchAngle() < safeRaiseAngle) {
    RobotContainer::climber->Raise();
  }
}

// Called once the command ends or is interrupted.
void TraverseRaiseClimber::End(bool interrupted) {
  RobotContainer::climber->Stop();
}

// Returns true when the command should end.
bool TraverseRaiseClimber::IsFinished() {
  return RobotContainer::climber->TooTall();


}
