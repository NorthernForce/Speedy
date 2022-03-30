// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/OneBall.h"
#include "commands/autonomous/DriveToDistance.h"
#include "commands/autonomous/DriveToDistanceIntake.h"
#include "commands/MoveArm.h"
#include "commands/ResetEncoders.h"
#include "commands/autonomous/AutoTurnToAngle.h"

OneBall::OneBall() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void OneBall::Initialize() {
    autoCommandScheduler.reset(new AutoCommandScheduler({

    //1 Ball
    new DriveToDistanceIntake(.2, -41.5, true),

    }));
}

// Called repeatedly when this Command is scheduled to run
void OneBall::Execute() {
    autoCommandScheduler->RunSequential();
}

// Called once the command ends or is interrupted.
void OneBall::End(bool interrupted) {}

// Returns true when the command should end.
bool OneBall::IsFinished() {
  return autoCommandScheduler->IsFinished();
}
