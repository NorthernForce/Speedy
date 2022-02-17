// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/autonomous/SetCoordinates.h"
#include "RobotContainer.h"

SetCoordinates::SetCoordinates(double x, double y) {
    RobotContainer::coordinates->SetLocation(
        CPlane::Point(units::inch_t(x), units::inch_t(y))
        );
}

SetCoordinates::SetCoordinates(CPlane::Point location) {
    RobotContainer::coordinates->SetLocation(location);
}

bool SetCoordinates::IsFinished() {
    return true;
}