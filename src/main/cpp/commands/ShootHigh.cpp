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

// Called repeatedly when this Command is scheduled to run
void ShootHigh::Execute() {
    RobotContainer::intake->ShootHigh();
    if(RobotContainer::intake->GetError() <= Constants::shooterError)
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
