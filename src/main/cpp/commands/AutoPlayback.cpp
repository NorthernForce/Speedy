// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoPlayback.h"
#include "RobotContainer.h"

AutoPlayback::AutoPlayback() {
  AddRequirements(RobotContainer::drivetrain.get());
}

void AutoPlayback::Initialize() {
    RobotContainer::drivetrain->SetEncoderPositions(0, 0);
    RobotContainer::autoRecorder->StartPlayback();
}

void AutoPlayback::Execute() {
    RobotContainer::autoRecorder->PlaybackPeriodic();
}

void AutoPlayback::End(bool interrupted) {
    RobotContainer::autoRecorder->StopPlayback();
}

bool AutoPlayback::IsFinished() {
  return RobotContainer::autoRecorder->IsPlaybackFinished();
}
