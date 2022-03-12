// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ClimberHeightUnderLimit.h"
#include "RobotContainer.h"

ClimberHeightUnderLimit::ClimberHeightUnderLimit() {
  AddRequirements(RobotContainer::climber.get());
}

// Called when the command is initially scheduled.
void ClimberHeightUnderLimit::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ClimberHeightUnderLimit::Execute() {
  if (
    RobotContainer::climber->GetPivot() == PivotState::Up &&
    RobotContainer::climber->GetOpticalSensor(Constants::DigitalIDs::middleOptical)
  ) {
    RobotContainer::climber->Lower();
  }
}

// Called once the command ends or is interrupted.
void ClimberHeightUnderLimit::End(bool interrupted) {}

// Returns true when the command should end.
bool ClimberHeightUnderLimit::IsFinished() { return false; }
