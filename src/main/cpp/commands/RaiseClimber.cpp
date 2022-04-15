// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/RaiseClimber.h"
#include "RobotContainer.h"
#include "subsystems/Climber.h"

RaiseClimber::RaiseClimber() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::climber.get());
}

// Called repeatedly when this Command is scheduled to run
void RaiseClimber::Execute() {
//  if(!RobotContainer::climber->GetOpticalSensor(Constants::DigitalIDs::middleOptical) && (RobotContainer::intake->GetPivot() == Intake::ArmState::Up)) {
//     RobotContainer::climber->Raise();
// } else if (RobotContainer::climber->GetOpticalSensor(Constants::DigitalIDs::middleOptical) && (RobotContainer::intake->GetPivot() == Intake::ArmState::Up)) {
//     RobotContainer::climber->Stop();
// }
RobotContainer::climber->Raise();
}

void RaiseClimber::End(bool interrupted) {
    RobotContainer::climber->Stop();
}

// Returns true when the command should end.
bool RaiseClimber::IsFinished() {
  return RobotContainer::climber->TooTall();
}
