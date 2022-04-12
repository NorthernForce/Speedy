// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/AutoTurnToAngle.h"
#include "RobotContainer.h"
#include "Constants.h"

AutoTurnToAngle::AutoTurnToAngle(double targetAngle, bool side) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::drivetrain.get());
  desiredAngle = targetAngle;
  desiredSide = side;
}

// Called when the command is initially scheduled.
void AutoTurnToAngle::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoTurnToAngle::Execute() {
    auto currentAngle = RobotContainer::imu->GetRotation();
    auto error = (currentAngle-desiredAngle)/100;

    if (desiredSide && currentAngle < desiredAngle) {
        RobotContainer::drivetrain->Drive(0, -GetDriveMultiplier(error));
    } else if (!desiredSide && currentAngle > desiredAngle) {
        RobotContainer::drivetrain->Drive(0, GetDriveMultiplier(error));
    } else {
        RobotContainer::drivetrain->DriveUsingSpeeds(0,0);
    }

    if (error <= Constants::attaError) {
        isDone = true;
    }
}

double AutoTurnToAngle::GetDriveMultiplier(double error) {
    double driveMultiplier;
    if (error < 0 && error < 1)
        driveMultiplier = (1.2 * pow(2.2, -error)) - .83;
    else if (error > 0 && error < 1)
        driveMultiplier = (1.2 * pow(2.2, error)) - .83;
    else 
        driveMultiplier = .85;

    return driveMultiplier;
}

// Called once the command ends or is interrupted.
void AutoTurnToAngle::End(bool interrupted) {
    RobotContainer::drivetrain->DriveUsingSpeeds(0,0);
}

// Returns true when the command should end.
bool AutoTurnToAngle::IsFinished() {
    return isDone;
}
