// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/DriveToDistance.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/Intake.h"
#include "RobotContainer.h"

DriveToDistance::DriveToDistance(double speed, double distance) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::drivetrain.get());
   desiredSpeed = speed;
   desiredDistance = distance;
}

// Called repeatedly when this Command is scheduled to run
void DriveToDistance::Execute() {
    RobotContainer::drivetrain->DriveUsingSpeeds(desiredSpeed, desiredSpeed);
    isFinished = std::abs(desiredDistance) < std::abs(RobotContainer::drivetrain->GetEncoderRotations().first);
}

// Called once the command ends or is interrupted.
void DriveToDistance::End(bool interrupted) {
    //printf("Drive To Distance Complete \n");
}

// Returns true when the command should end.
bool DriveToDistance::IsFinished() {
  return isFinished;
}
