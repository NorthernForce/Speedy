// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/ThreeBall.h"
#include "commands/autonomous/DriveToDistance.h"
#include "commands/autonomous/DriveToDistanceIntake.h"
#include "commands/MoveArm.h"
#include "commands/ResetEncoders.h"
#include "commands/autonomous/AutoTurnToAngle.h"

ThreeBall::ThreeBall() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void ThreeBall::Initialize() {
    autoCommandScheduler.reset(new AutoCommandScheduler({

    //3 BALL
    new ResetEncoders(),
    new DriveToDistanceIntake(.2, -20, true),
    new MoveArm(false),
    new ResetEncoders(),
    new AutoTurnToAngle(-112, false),
    new ResetEncoders(),
    new DriveToDistanceIntake(-.4, 41, false), //first ball
    new ResetEncoders(),
    new AutoTurnToAngle(-135, false),
    new ResetEncoders(),
    new DriveToDistanceIntake(-.4, 27, false),
    new ResetEncoders(),
    new AutoTurnToAngle(-39, false),
    new ResetEncoders(),
    new DriveToDistanceIntake(-.4, 37, false), //second ball
    new ResetEncoders(),
    new DriveToDistance(.2, -15),
    new ResetEncoders(),
    new AutoTurnToAngle(-89, false),
    new ResetEncoders(),
    new MoveArm(true),
    new ResetEncoders(),
    new DriveToDistance(-.4, 22),
    new ResetEncoders(),
    new AutoTurnToAngle(-6, false),
    new ResetEncoders(),
    new DriveToDistance(-.4, 13),
    new ResetEncoders(),
    new AutoTurnToAngle(-5, false),
    new ResetEncoders(),
    new DriveToDistanceIntake(-.4, 5, true), //scores both

    }));}

// Called repeatedly when this Command is scheduled to run
void ThreeBall::Execute() {
    autoCommandScheduler->RunSequential();
}

// Returns true when the command should end.
bool ThreeBall::IsFinished() {
  return autoCommandScheduler->IsFinished();
}
