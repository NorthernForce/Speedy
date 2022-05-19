// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/AutoTraverse.h"
#include "RobotContainer.h"
#include "utilities/AutoCommandScheduler.h"
#include "commands/autonomous/AutoLowerClimber.h"
#include "commands/RaiseClimber.h"
#include "commands/PivotToggle.h"
#include "commands/ToggleArm.h"

AutoTraverse::AutoTraverse() {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(RobotContainer::climber.get());
}

// Called when the command is initially scheduled.
void AutoTraverse::Initialize() {

    autoCommandScheduler.reset(new AutoCommandScheduler({

    //1 Auto Traverse
    new AutoLowerClimber(),
    new PivotToggle(),
    new RaiseClimber(),
    new PivotToggle(),
    new AutoLowerClimber,
    new PivotToggle(),
    new RaiseClimber(),
    new ToggleArm(),
    new PivotToggle,
    new AutoLowerClimber(),

    }));
}

// Called repeatedly when this Command is scheduled to run
void AutoTraverse::Execute() {
    autoCommandScheduler->RunSequential();
}

// Called once the command ends or is interrupted.
void AutoTraverse::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoTraverse::IsFinished() {
  return autoCommandScheduler->IsFinished();
}
