// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
//Up is true

#include "commands/MoveArm.h"
#include "RobotContainer.h"

MoveArm::MoveArm(bool up) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::intake.get());
    desiredUp = up;
}

// Called when the command is initially scheduled.
void MoveArm::Initialize() {
    if(desiredUp) {
    RobotContainer::intake->ArmUp();
    } else if (!desiredUp) {
    RobotContainer::intake->ArmDown();
    }
}

// Returns true when the command should end.
bool MoveArm::IsFinished() {
  return true;
}
