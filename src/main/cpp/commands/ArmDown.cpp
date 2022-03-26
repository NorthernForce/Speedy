// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ArmDown.h"
#include "RobotContainer.h"

void ArmDown::Initialize() {
    RobotContainer::intake->ArmDown();
}

bool ArmDown::IsFinished() {
    return true;
}