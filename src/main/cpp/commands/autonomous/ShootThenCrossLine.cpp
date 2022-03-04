// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/ShootThenCrossLine.h"
#include "RobotContainer.h"
#include "subsystems/Drivetrain.h"

ShootThenCrossLine::ShootThenCrossLine() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::drivetrain.get());
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void ShootThenCrossLine::Initialize() {
    RobotContainer::drivetrain->SetEncoderPositions(0, 0);
}

// Called repeatedly when this Command is scheduled to run
void ShootThenCrossLine::Execute() {
    RobotContainer::drivetrain->DriveUsingSpeeds(.2, .2);
    RobotContainer::intake->Run(reverse);

}

// Called once the command ends or is interrupted.
void ShootThenCrossLine::End(bool interrupted) {}

// Returns true when the command should end.
bool ShootThenCrossLine::IsFinished() {
    RobotContainer::drivetrain->GetAvgEncoderRotations(RobotContainer::drivetrain->GetEncoderRotations());
  return (true);

}
