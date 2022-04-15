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

// Called repeatedly when this Command is scheduled to run
void DriveToDistanceIntake::Execute() {
    auto error = std::abs((RobotContainer::drivetrain->GetEncoderRotations().first-desiredDistance)/desiredDistance);

    if(desiredDistance > 0) {
        RobotContainer::drivetrain->DriveUsingSpeeds(-GetDriveMultiplier(error), -GetDriveMultiplier(error));
        //RobotContainer::drivetrain->DriveUsingSpeeds(-.3, -.3); 
        isFinished = RobotContainer::drivetrain->GetEncoderRotations().first > desiredDistance;
    }   
    else if (desiredDistance < 0) {
        RobotContainer::drivetrain->DriveUsingSpeeds(GetDriveMultiplier(error), GetDriveMultiplier(error)); 
        //RobotContainer::drivetrain->DriveUsingSpeeds(.3, .3); 
        isFinished = RobotContainer::drivetrain->GetEncoderRotations().first < desiredDistance;
    }
    RobotContainer::intake->Run(desiredReverse ? Intake::IntakeDirection::outtake : Intake::IntakeDirection::intake);
    }    

double DriveToDistanceIntake::GetDriveMultiplier(double error) {
    return -1 * pow(-.7 * error + .35, 2) + .52;
    }

// Called once the command ends or is interrupted.
void DriveToDistanceIntake::End(bool interrupted) {
    //printf("Drive To Distance Intake Complete \n");
    RobotContainer::intake->Stop();
}

// Returns true when the command should end.
bool DriveToDistanceIntake::IsFinished() {
  return isFinished;
}

