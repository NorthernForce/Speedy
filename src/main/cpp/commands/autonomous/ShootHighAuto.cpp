// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/ShootHighAuto.h"
#include "subsystems/Intake.h"
#include "RobotContainer.h"

ShootHighAuto::ShootHighAuto() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::intake.get());
}

// Called when the command is initially scheduled.
void ShootHighAuto::Initialize() {
    shooterCounter = 0;
}

// Called repeatedly when this Command is scheduled to run
void ShootHighAuto::Execute() {
    for (;shooterCounter < 50; shooterCounter++) {
        RobotContainer::intake->ShootHighRPM(500);
        if((500 - RobotContainer::intake->GetCurrentRPM()) < Constants::shooterError) {
            RobotContainer::intake->intakeTopSpark->Set(-.9);
            RobotContainer::intake->intakeBottomSpark->Set(.9 * .18);
        }
    }
}

// Called once the command ends or is interrupted.
void ShootHighAuto::End(bool interrupted) {}

// Returns true when the command should end.
bool ShootHighAuto::IsFinished() {
  return shooterCounter >= 50;
}
