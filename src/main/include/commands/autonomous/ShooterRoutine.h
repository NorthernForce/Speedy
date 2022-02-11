// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "utilities/AutoCommandScheduler.h"

class ShooterRoutine
    : public frc2::CommandHelper<frc2::CommandBase, ShooterRoutine> {
 public:
  ShooterRoutine();

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
    std::shared_ptr<AutoCommandScheduler> commandController;
    bool timed = true;
};
