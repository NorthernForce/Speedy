// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/RaiseClimber.h"
#include "RobotContainer.h"
#include "subsystems/Climber.h"

RaiseClimber::RaiseClimber() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::climber.get());
  state = RobotContainer::climber->GetClimberState(RobotContainer::climber->climberPosition);

}

void RaiseClimber::Initialize() {
        //(int)currentState;
}

// Called repeatedly when this Command is scheduled to run
void RaiseClimber::Execute() {
    if((int)state!= (int)RobotContainer::climber->GetClimberState(RobotContainer::climber->climberPosition)+1){
        RobotContainer::climber->Raise();
    }}

void RaiseClimber::End(bool interrupted) {
    RobotContainer::climber->Stop();
}
// Returns true when the command should end.
bool RaiseClimber::IsFinished() {
  return false;
}
