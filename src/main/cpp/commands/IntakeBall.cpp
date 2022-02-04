// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/IntakeBall.h"
#include "RobotContainer.h"

IntakeBall::IntakeBall() {
  AddRequirements(RobotContainer::intake.get());
}

void IntakeBall::Execute() {
    RobotContainer::intake->Run();
}

void IntakeBall::End(bool interrupted) {
    RobotContainer::intake->Stop();
}

bool IntakeBall::IsFinished() {
  return false;
}
