// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/SetCoordinates.h"
#include "RobotContainer.h"

SetCoordinates::SetCoordinates(double x, double y) {
    RobotContainer::navigation->SetCoordinatePosition(x, y);
}

bool SetCoordinates::IsFinished() {
    return true;
}