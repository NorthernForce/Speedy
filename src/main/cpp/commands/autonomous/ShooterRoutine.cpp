// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/ShooterRoutine.h"
#include <memory>

#include "commands/ArmDown.h"
#include "commands/ArmUp.h"
#include "commands/autonomous/MoveToCoordinate.h"
#include "commands/IntakeBall.h"
#include "commands/PushOutBall.h"
#include "commands/autonomous/SetCoordinates.h"

ShooterRoutine::ShooterRoutine() {}

// Called when the command is initially scheduled.
void ShooterRoutine::Initialize() {
    commandController.reset(new AutoCommandScheduler({
        new SetCoordinates(21.5, 56),
        new ArmDown(),
        new MoveToCoordinate(150.79, 25.91), // move to ball
        new IntakeBall(),
        new ArmUp(),
        new MoveToCoordinate(11.97, 31.72), // move to goal
        new PushOutBall(),
        new MoveToCoordinate(44.52, 112.78), // move out of zone
        new ArmDown()
    }));
}

// Called repeatedly when this Command is scheduled to run
void ShooterRoutine::Execute() {
    commandController->RunSequential();
}

// Called once the command ends or is interrupted.
void ShooterRoutine::End(bool interrupted) {}

// Returns true when the command should end.
bool ShooterRoutine::IsFinished() {
    return commandController->IsFinished();
}
