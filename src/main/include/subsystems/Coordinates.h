// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "utilities/CPlane.h"

class Coordinates : public frc2::SubsystemBase {
 public:
  Coordinates();

  CPlane::Point GetLocation();

  units::degree_t EncoderDegreesChange();

  units::inch_t DistanceTravelled();

  units::degree_t Theta();

  CPlane::Point PointMoved();

  void UpdateLocation();

  void SetLocation(CPlane::Point newLocation);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
  CPlane::Point location{0_in, 0_in};

  units::degree_t lastAvgEncPos;
  std::pair<double, double> currEncPositions;
  units::degree_t avgCurrEncPos;
  units::degree_t encChange;

  units::dimensionless_t wheelSpinPercent;

  units::inch_t distance;
  units::inch_t dx;
  units::inch_t dy;

  CPlane::Point p1{1_in, 1_in};
  CPlane::Point p2{2_in, 2_in};
  CPlane::Point p3{0_in, 0_in};
};
