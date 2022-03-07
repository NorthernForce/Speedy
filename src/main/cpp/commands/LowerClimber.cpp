// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/LowerClimber.h"
#include "RobotContainer.h"

LowerClimber::LowerClimber() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::climber.get());
  ClimberState state = RobotContainer::climber->GetClimberState(RobotContainer::climber->climberPosition);
  //set climber state equal to state
}

// Called repeatedly when this Command is scheduled to run
void LowerClimber::Execute() {
    //if statement with state == climber state-1
    if((int)state!= (int)RobotContainer::climber->GetClimberState(RobotContainer::climber->climberPosition)-1){
    RobotContainer::climber->Lower();
    }
}

void LowerClimber::End(bool interrupted) {
    //set climber state equal to zero
    RobotContainer::climber->Stop();
}

// Returns true when the command should end.
bool LowerClimber::IsFinished() {
  return false;
}
