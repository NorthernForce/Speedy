// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "utilities/CPlane.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class SetCoordinates
    : public frc2::CommandHelper<frc2::CommandBase, SetCoordinates> {
 public:
  SetCoordinates(double x, double y);
  SetCoordinates(CPlane::Point location);
  bool IsFinished() override;
};
