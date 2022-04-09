// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ShootHigh.h"
#include "subsystems/Intake.h"
#include "RobotContainer.h"

ShootHigh::ShootHigh() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::intake.get());
}

void ShootHigh::Initialize() {
    startTime = RobotContainer::fmsComms->GetMatchTime().value();
    // spark5Encoder = RobotContainer::intake->SparkEncoderPosition();
    // startPosition = spark5Encoder.GetPosition();
}

// Called repeatedly when this Command is scheduled to run
void ShootHigh::Execute() {

    // if((startPosition + 2) <= spark5Encoder.GetPosition()) {
    //      RobotContainer::intake->Run(Intake::IntakeDirection::outtake);
    //  }

     if((startTime + 1.9) <= RobotContainer::fmsComms->GetMatchTime()) {
         RobotContainer::intake->Run(Intake::IntakeDirection::outtake);
     }

    RobotContainer::intake->ShootHigh();
    printf("%f \n", RobotContainer::intake->GetCurrentRPM());
    if(RobotContainer::intake->GetCurrentRPM() >= 14000)
        RobotContainer::intake->Run(Intake::IntakeDirection::intake);
}

// Called once the command ends or is interrupted.
void ShootHigh::End(bool interrupted) {
    RobotContainer::intake->Stop();
}

// Returns true when the command should end.
bool ShootHigh::IsFinished() {
  return false;
}
