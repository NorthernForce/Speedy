// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/AutoTurnToAngle.h"
#include "RobotContainer.h"

AutoTurnToAngle::AutoTurnToAngle(double targetAngle, bool side) {
  // Use addRequirements() here to declare subsystem dependencies.
  //AddRequirements(RobotContainer::drivetrain.get());
  desiredAngle = targetAngle;
  desiredSide = side;
}

// Called when the command is initially scheduled.
void AutoTurnToAngle::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AutoTurnToAngle::Execute() {
    currentAngle = RobotContainer::imu->GetRotation();
    error = currentAngle-desiredAngle;
    if(desiredSide && currentAngle < desiredAngle) {
        //RobotContainer::drivetrain->Drive(0, GetDriveMultiplier());
        //RobotContainer::drivetrain->DriveUsingSpeeds(GetDriveMultiplier(), -GetDriveMultiplier());
    } else if(!desiredSide && currentAngle > desiredAngle) {
        //RobotContainer::drivetrain->Drive(0, GetDriveMultiplier());
        //RobotContainer::drivetrain->DriveUsingSpeeds(-GetDriveMultiplier(), GetDriveMultiplier());
    } else {
        //RobotContainer::drivetrain->DriveUsingSpeeds(0,0)
    }
}

double AutoTurnToAngle::GetDriveMultiplier() {
    double driveMultiplier;
    if (error < 0)
        driveMultiplier = (1.2 * pow(7.7, -error)) - .83;
    else
        driveMultiplier = (1.2 * pow(7.7, error)) - .83;
        
    return driveMultiplier;
}
// Called once the command ends or is interrupted.
void AutoTurnToAngle::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoTurnToAngle::IsFinished() {
    // if (abs(error) <= 5)
    //     return true;
    // else 
        return false;
}
