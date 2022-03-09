// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/DriveToDistanceIntake.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/Intake.h"
#include "RobotContainer.h"

DriveToDistanceIntake::DriveToDistanceIntake(double speed, double distance, bool reverse) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::drivetrain.get());
  AddRequirements(RobotContainer::intake.get());
  desiredDistance = distance;
  desiredReverse = reverse;
  desiredSpeed = speed;
}

// Called when the command is initially scheduled.
void DriveToDistanceIntake::Initialize() {
    RobotContainer::drivetrain->SetEncoderPositions(0, 0);
}

// Called repeatedly when this Command is scheduled to run
void DriveToDistanceIntake::Execute() {
    //if(desiredDistance != RobotContainer::drivetrain->GetAvgEncoderRotations(RobotContainer::drivetrain->GetEncoderRotations()) +- 3) {
        RobotContainer::drivetrain->DriveUsingSpeeds(desiredSpeed, desiredSpeed);
        RobotContainer::intake->Run(desiredReverse);
    //}
}

// Called once the command ends or is interrupted.
void DriveToDistanceIntake::End(bool interrupted) {
    RobotContainer::drivetrain->DriveUsingSpeeds(0, 0);
}

// Returns true when the command should end.
bool DriveToDistanceIntake::IsFinished() {
  return (abs(desiredDistance) < abs(RobotContainer::drivetrain->GetAvgEncoderRotations(RobotContainer::drivetrain->GetEncoderRotations())));
}

