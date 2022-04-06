// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/LowerClimber.h"
#include "RobotContainer.h"

LowerClimber::LowerClimber() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::climber.get());
}

// Called repeatedly when this Command is scheduled to run
void LowerClimber::Execute() {
  if (RobotContainer::climber->GetOpticalSensor(Constants::DigitalIDs::bottomOptical)) {
    RobotContainer::climber->Lower();
  }
}

void LowerClimber::End(bool interrupted) {
    RobotContainer::climber->Stop();
}

// Returns true when the command should end.
bool LowerClimber::IsFinished() {
  return RobotContainer::climber->GetClimberHeight() == ClimberHeight::Bottom;
}
