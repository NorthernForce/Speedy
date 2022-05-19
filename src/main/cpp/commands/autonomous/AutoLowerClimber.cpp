// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/AutoLowerClimber.h"
#include "RobotContainer.h"

AutoLowerClimber::AutoLowerClimber() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::climber.get());
}

// Called when the command is initially scheduled.
void AutoLowerClimber::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoLowerClimber::Execute() {
    lowerSensor = RobotContainer::climber->GetOpticalSensor(Constants::DigitalIDs::bottomOptical);
    middleSensor = RobotContainer::climber->GetOpticalSensor(Constants::DigitalIDs::middleOptical);

    if(lowerSensor && middleSensor) {
        RobotContainer::climber->Lower();
    } else if (!middleSensor && lowerSensor) {
        RobotContainer::climber->LowerSlow();
    }
}

// Called once the command ends or is interrupted.
void AutoLowerClimber::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoLowerClimber::IsFinished() {
  return !lowerSensor;
}
