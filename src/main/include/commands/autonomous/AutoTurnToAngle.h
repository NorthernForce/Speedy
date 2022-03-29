// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class AutoTurnToAngle
    : public frc2::CommandHelper<frc2::CommandBase, AutoTurnToAngle> {
 public:
  AutoTurnToAngle(double targetAngle, bool side);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  double GetDriveMultiplier(double error);

  private:

  bool desiredSide; // side=true is turn right
  double desiredAngle;
  bool isDone = false;

};
