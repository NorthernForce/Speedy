// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/OneBallHigh.h"
#include "commands/autonomous/DriveToDistance.h"
#include "commands/autonomous/ShootHighAuto.h"
#include "commands/MoveArm.h"
#include "commands/ResetEncoders.h"
#include "commands/autonomous/AutoTurnToAngle.h"
#include "subsystems/Intake.h"

OneBallHigh::OneBallHigh() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void OneBallHigh::Initialize() {
        autoCommandScheduler.reset(new AutoCommandScheduler({

    //1 Ball High

    new ShootHighAuto(),
    new DriveToDistance(-.2, 41.5),

    }));
}

// Called repeatedly when this Command is scheduled to run
void OneBallHigh::Execute() {
    autoCommandScheduler->RunSequential();
}

// Called once the command ends or is interrupted.
void OneBallHigh::End(bool interrupted) {}

// Returns true when the command should end.
bool OneBallHigh::IsFinished() {
    return autoCommandScheduler->IsFinished();
}
