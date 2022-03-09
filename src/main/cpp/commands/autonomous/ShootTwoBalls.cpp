// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/ShootTwoBalls.h"
#include "RobotContainer.h"
#include "Constants.h"
#include "subsystems/Drivetrain.h"

//I know this is very ugly Hunter and I'm sorry but it does work hopefully

ShootTwoBalls::ShootTwoBalls() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::drivetrain.get());
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void ShootTwoBalls::Initialize() {
    RobotContainer::drivetrain->SetEncoderPositions(0, 0);

}

// Called repeatedly when this Command is scheduled to run
void ShootTwoBalls::Execute() {

    if (stepOne == false && (RobotContainer::drivetrain->GetAvgEncoderRotations(RobotContainer::drivetrain->GetEncoderRotations()) > -20)) {
        //brings it behind line
        RobotContainer::drivetrain->DriveUsingSpeeds(.25, .25);
        RobotContainer::intake->ArmDown();
        RobotContainer::intake->Run();

    } else if (stepOne == false && (RobotContainer::drivetrain->GetAvgEncoderRotations(RobotContainer::drivetrain->GetEncoderRotations()) < -20 && (RobotContainer::drivetrain->GetAvgEncoderRotations(RobotContainer::drivetrain->GetEncoderRotations()) > -53))) {
        //behind line
        RobotContainer::drivetrain->DriveUsingSpeeds(.4, .4);
    } else if (stepOne == false && RobotContainer::drivetrain->GetAvgEncoderRotations(RobotContainer::drivetrain->GetEncoderRotations()) < -53) {
        stepOne = true;
        RobotContainer::drivetrain->SetEncoderPositions(0, 0);
    }

    if(stepOne == true && stepTwo == false && RobotContainer::drivetrain->GetEncoderRotations().first < 25106 && RobotContainer::drivetrain->GetEncoderRotations().second > -22679) {
        //turn left
        RobotContainer::drivetrain->DriveUsingSpeeds(-.25, .25);
    } else if(stepOne == true && stepTwo == false && RobotContainer::drivetrain->GetEncoderRotations().first > 25106 && RobotContainer::drivetrain->GetEncoderRotations().second < -22679) {
        stepTwo = true;
        RobotContainer::drivetrain->SetEncoderPositions(0, 0);
    }

    if(stepTwo == true && stepThree == false && (RobotContainer::drivetrain->GetAvgEncoderRotations(RobotContainer::drivetrain->GetEncoderRotations()) < 35.6)) {
        //go forward to and pick up ball
        RobotContainer::drivetrain->DriveUsingSpeeds(.4, .4);
        RobotContainer::intake->ArmUp();
        RobotContainer::intake->Run(true);
    } else if(stepTwo == true && stepThree == false && (RobotContainer::drivetrain->GetAvgEncoderRotations(RobotContainer::drivetrain->GetEncoderRotations()) > 35.6)) {
        stepThree = true;
        RobotContainer::drivetrain->SetEncoderPositions(0, 0);
    }
}

// Called once the command ends or is interrupted.
void ShootTwoBalls::End(bool interrupted) {}

// Returns true when the command should end.
bool ShootTwoBalls::IsFinished() {
    if ((RobotContainer::drivetrain->GetAvgEncoderRotations(RobotContainer::drivetrain->GetEncoderRotations()) > 60)) {
        RobotContainer::drivetrain->DriveUsingSpeeds(0, 0);
        return true;
    } else {
        return false;
    }
}
