// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/AutoTraverse.h"
#include "commands/RaiseClimberPartial.h"
#include "commands/PivotToggle.h"
#include "commands/RaiseClimber.h"
#include "commands/ArmUp.h"
#include "commands/autonomous/SmartBarGrab.h"
#include "commands/LowerClimber.h"

AutoTraverse::AutoTraverse() {
  // Use addRequirements() here to declare subsystem dependencies.
  scheduler.reset(new AutoCommandScheduler({
    new RaiseClimberPartial(),
    new RaiseClimberPartial(),
    new PivotToggle(),
    new ArmUp(),
    new RaiseClimber(),
    new SmartBarGrab(),
    new LowerClimber(),
    new PivotToggle()
  }));
}
// Called when the command is initially scheduled.
void AutoTraverse::Initialize() {
  RobotContainer::climber->ResetSpool();
  scheduler->ResetIndex();
}

// Called repeatedly when this Command is scheduled to run
void AutoTraverse::Execute() {
  scheduler->RunSequential();
  frc::SmartDashboard::PutBoolean("AutoTraverse: ", true);
}


// Called once the command ends or is interrupted.
void AutoTraverse::End(bool interrupted) {
  frc::SmartDashboard::PutBoolean("AutoTraverse: ", false);
}

// Returns true when the command should end.
bool AutoTraverse::IsFinished() {
  return scheduler->IsFinished();
}
