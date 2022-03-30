// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/TwoBalls.h"
#include "commands/autonomous/DriveToDistance.h"
#include "commands/autonomous/DriveToDistanceIntake.h"
#include "commands/MoveArm.h"
#include "commands/ResetEncoders.h"
#include "commands/autonomous/AutoTurnToAngle.h"

TwoBalls::TwoBalls() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void TwoBalls::Initialize() {autoCommandScheduler.reset(new AutoCommandScheduler({
    
    //2 BALL
    new ResetEncoders(),
    new DriveToDistanceIntake(.2, -10, true),
    new ResetEncoders(),
    new AutoTurnToAngle(-170, false),
    new ResetEncoders(),
    new MoveArm(false),
    new AutoTurnToAngle(-15, false),
    new ResetEncoders(),
    new DriveToDistanceIntake(-.4, 28, false),
    new ResetEncoders(),
    new AutoTurnToAngle(-180, false),
    new ResetEncoders(),
    new MoveArm(true),
    new ResetEncoders(),
    new DriveToDistance(-.4, 40),
    new ResetEncoders(),
    new AutoTurnToAngle(-5, false),
    new ResetEncoders(),
    new DriveToDistanceIntake(-.4, 1.5, true),

    }));}

// Called repeatedly when this Command is scheduled to run
void TwoBalls::Execute() {
    autoCommandScheduler->RunSequential();
}

// Called once the command ends or is interrupted.
void TwoBalls::End(bool interrupted) {}

// Returns true when the command should end.
bool TwoBalls::IsFinished() {
  return autoCommandScheduler->IsFinished();
}
