/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "Constants.h"
#include <ctre/Phoenix.h>
#include "utilities/CPlane.h"

class Navigation : public frc2::SubsystemBase {
 public:
  Navigation();
  void Periodic();
  
  units::inch_t DistanceToPoint(CPlane::Point p1, CPlane::Point p2);
  units::inch_t DistanceToPoint(CPlane::Point p2);
  
  units::degree_t SimplifyAngle(units::degree_t angle);

  units::degree_t AngleToPoint(CPlane::Point p1, CPlane::Point p2);
  units::degree_t AngleToPoint(CPlane::Point p2);

 private:
    CPlane::Point delta{};
    units::degree_t angleToPoint;

    double NavXScaling = Constants::XResetMultiplier;
};
