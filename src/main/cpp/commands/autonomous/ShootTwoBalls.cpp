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
    
    RobotContainer::intake->ArmUp();
    if(RobotContainer::drivetrain->GetAvgEncoderRotations(RobotContainer::drivetrain->GetEncoderRotations()) > 20) {
        RobotContainer::intake->Run();
    }

    if ((RobotContainer::drivetrain->GetAvgEncoderRotations(RobotContainer::drivetrain->GetEncoderRotations()) < 60)) {
        //brings it behind line
        RobotContainer::drivetrain->DriveUsingSpeeds(.15, .15);
    } else if ((RobotContainer::drivetrain->GetAvgEncoderRotations(RobotContainer::drivetrain->GetEncoderRotations()) > 60 && (RobotContainer::drivetrain->GetAvgEncoderRotations(RobotContainer::drivetrain->GetEncoderRotations()) < 80))) {
        //turn right
        RobotContainer::drivetrain->DriveUsingSpeeds(.4, .3);
    } else if ((RobotContainer::drivetrain->GetAvgEncoderRotations(RobotContainer::drivetrain->GetEncoderRotations()) > 60 && (RobotContainer::drivetrain->GetAvgEncoderRotations(RobotContainer::drivetrain->GetEncoderRotations()) < 80))) {
        //pick up ball
        RobotContainer::drivetrain->DriveUsingSpeeds(.4, .3);
        RobotContainer::intake->Run(true);
        //true is intake reverse

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
