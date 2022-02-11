// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/PushOutBall.h"
#include "RobotContainer.h"

PushOutBall::PushOutBall(bool timed) : timed(timed) {
    AddRequirements(RobotContainer::intake.get());
    timer = std::unique_ptr<frc::Timer>();
    timer->Start();
}

void PushOutBall::Execute() {
    RobotContainer::intake->Run(reverse);
}

void PushOutBall::End(bool interrupted) {
    RobotContainer::intake->Stop();
}

bool PushOutBall::IsFinished() {
    if (timed)
        return timer->Get() > 1_s;
    return false;
}
