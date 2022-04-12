// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ResetEncoders.h"
#include "RobotContainer.h"

ResetEncoders::ResetEncoders() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::drivetrain.get());
}

// Called when the command is initially scheduled.
void ResetEncoders::Initialize() {
    RobotContainer::drivetrain->SetEncoderPositions(0,0);
    RobotContainer::imu->ZeroRotation();
}

// Returns true when the command should end.
bool ResetEncoders::IsFinished() {
  return true;
}
