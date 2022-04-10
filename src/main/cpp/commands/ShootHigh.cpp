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
    desiredRPM = frc::SmartDashboard::GetNumber("Shooter RPM", 700);
    desiredOutakeTime = frc::SmartDashboard::GetNumber("Push forward duration", 10);
    desiredIntakeShootSpeed = frc::SmartDashboard::GetNumber("Intake Shoot Speed", .9);
    i = 0;
    warmUp = false;
}

// Called repeatedly when this Command is scheduled to run
void ShootHigh::Execute() {

    printf("%f \n", desiredRPM);

    if (i < desiredOutakeTime) {
        RobotContainer::intake->intakeBottomSpark->Set(-.17);
        RobotContainer::intake->intakeTopSpark->Set(.17);
        i++;
    } else {
    RobotContainer::intake->ShootHighRPM(desiredRPM);
    }

    if((desiredRPM - RobotContainer::intake->GetCurrentRPM()) < Constants::shooterError) {
        RobotContainer::intake->intakeTopSpark->Set(-desiredIntakeShootSpeed);
        RobotContainer::intake->intakeBottomSpark->Set(desiredIntakeShootSpeed * .18);
    }
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
