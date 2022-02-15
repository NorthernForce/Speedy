// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/PivotToggle.h"
#include "RobotContainer.h"
#include "subsystems/Climber.h"

PivotToggle::PivotToggle() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::climber.get());
}

// Called when the command is initially scheduled.
void PivotToggle::Initialize() {
 if(RobotContainer::climber->GetPivot() == PivotState::Down) {
   RobotContainer::climber->PivotUp();
 } else if (RobotContainer::climber->GetPivot() == PivotState::Up) {
   RobotContainer::climber->PivotDown();
 } else {
   printf("Pivot not in range");
 }

}

// Called repeatedly when this Command is scheduled to run
void PivotToggle::Execute() {}

// Called once the command ends or is interrupted.
void PivotToggle::End(bool interrupted) {}

// Returns true when the command should end.
bool PivotToggle::IsFinished() {
  return false;
}
