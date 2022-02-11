// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/IntakeBall.h"
#include "RobotContainer.h"

IntakeBall::IntakeBall(bool timed) : timed(timed) {
    AddRequirements(RobotContainer::intake.get());
    timer = std::make_unique<frc::Timer>();
    timer->Start();
}

void IntakeBall::Execute() {
    RobotContainer::intake->Run();
}

void IntakeBall::End(bool interrupted) {
    RobotContainer::intake->Stop();
}

bool IntakeBall::IsFinished() {
    if (timed)
        return timer->Get() > 2_s;
    return false;
}
