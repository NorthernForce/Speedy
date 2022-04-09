// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ShootHigh.h"
#include "subsystems/Intake.h"
#include "RobotContainer.h"
#include "frc/smartdashboard/SmartDashboard.h"

ShootHigh::ShootHigh() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::intake.get());
}

void ShootHigh::Initialize() {
    desiredRPM = frc::SmartDashboard::GetNumber("Shooter RPM", 1500);
    i = 0;
    warmUp = false;
}

// Called repeatedly when this Command is scheduled to run
void ShootHigh::Execute() {

    if (i < 20) {
        RobotContainer::intake->intakeBottomSpark->Set(-.1);
        i++;
    } else {
    RobotContainer::intake->ShootHighRPM(desiredRPM);
    }

    printf("%f \n", RobotContainer::intake->GetCurrentRPM());
    if(RobotContainer::intake->GetError() < Constants::shooterError)
        RobotContainer::intake->Run(Intake::IntakeDirection::intake);
    // else {
    //     RobotContainer::intake->Stop();
    // }
}

// Called once the command ends or is interrupted.
void ShootHigh::End(bool interrupted) {
    RobotContainer::intake->Stop();
    RobotContainer::intake->StopHigh();
}

// Returns true when the command should end.
bool ShootHigh::IsFinished() {
  return false;
}
