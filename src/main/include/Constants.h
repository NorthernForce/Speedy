// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include <units/length.h>
#include <units/math.h>
#include <cmath>

namespace Constants {
    namespace MotorIDs {
        const uint8_t leftPrimary = 1;
        const uint8_t rightPrimary = 2;
        const uint8_t leftFollower = 3;
        const uint8_t rightFollower = 4;

        const uint8_t intake = 5;

        const uint8_t rightClimber = 6;
        const uint8_t leftClimber = 7;
    }

    const uint8_t climber = 4;
    const uint8_t arm = 9;

    const uint8_t driverController_id = 0;
    const uint8_t manipulatorController_id = 1;
    const uint8_t PCMCanBusID = 15;

    const double degreesToRadians = M_PI/180;
    const double XResetMultiplier = 0.996194698092;

    const double gearRatio = (9/62) * (18/30);

    const double encoderToInch = -1175;

    const units::unit_t<units::length::inch> wheelCircum = 6_in;
}