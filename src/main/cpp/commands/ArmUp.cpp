// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ArmUp.h"
#include "RobotContainer.h"

void ArmUp::Initialize() {
    RobotContainer::intake->ArmUp();
}

bool ArmUp::IsFinished() {
    return true;
}
