/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/* This is version 2020/7/20                                                  */
/*----------------------------------------------------------------------------*/

#include "subsystems/Navigation.h"
#include "RobotContainer.h"
#include "Constants.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <cmath>

#include <thread>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

Navigation::Navigation() {}
// This method will be called once per scheduler run
void Navigation::Periodic() {}

units::inch_t Navigation::DistanceToPoint(CPlane::Point p1, CPlane::Point p2) {
    delta = p2.Subtract(p1, true);
    return units::math::hypot(delta.x, delta.y);
}

//If only given one point --> assumes 1st point is robot
units::inch_t Navigation::DistanceToPoint(CPlane::Point p2) {
    return DistanceToPoint(RobotContainer::coordinates->GetLocation(), p2);
}

units::degree_t Navigation::SimplifyAngle(units::degree_t angle) {
    if (units::math::abs(angle) < 180_deg) {
        return angle;
    }
    else {
        if (angle < 0_deg) {
            return angle + 360_deg;
        }
        else {
            return angle - 360_deg;
        }
    }
}

units::degree_t Navigation::AngleToPoint(CPlane::Point p1, CPlane::Point p2) {
    delta = p2.Subtract(p1, true);
    if (delta.x == 0_in) {
        if (delta.y < 0_in) {
            return -90_deg;
        }
        else {
            return 90_deg;
        }
    }
    else {
        angleToPoint = units::math::atan2(delta.y, delta.x);
        if (delta.x < 0_in) {
            return SimplifyAngle(angleToPoint + 180_deg);
        }
        else {
            return angleToPoint;
        }
    }
}

units::degree_t Navigation::AngleToPoint(CPlane::Point p2) {
    return SimplifyAngle(
        AngleToPoint( RobotContainer::coordinates->GetLocation(), p2)
        - RobotContainer::coordinates->Theta()
    );
}