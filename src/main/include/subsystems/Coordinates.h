// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "utilities/CPlane.h"
#include <units/length.h>

class Coordinates : public frc2::SubsystemBase {
 public:
  Coordinates();

  CPlane::Point GetLocation();

  void SetLocation(CPlane::Point newLocation);

  units::degree_t EncoderDegreesChange();

  units::inch_t DistanceTravelled();

  units::degree_t Theta();

  void SetTheta(units::degree_t newTheta);

  CPlane::Point PointMoved();

  void UpdateLocation();


  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
  CPlane::Point location{0_in, 0_in};

  units::degree_t lastAvgEncPos;
  std::pair<units::inch_t, units::inch_t> currEncPositions;
  units::degree_t avgCurrEncPos;
  units::degree_t encChange;

  units::dimensionless_t wheelSpinPercent;

  units::degree_t navXOffsetAngle = 0_deg;

  units::inch_t distance;
  units::inch_t dx;
  units::inch_t dy;

  CPlane::Point p1{1_in, 1_in};
  CPlane::Point p2{2_in, 2_in};
  CPlane::Point p3{0_in, 0_in};
};
