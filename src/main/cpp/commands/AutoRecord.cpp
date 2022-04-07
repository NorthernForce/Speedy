// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoRecord.h"
#include "RobotContainer.h"

AutoRecord::AutoRecord() {}

void AutoRecord::Initialize() {
    RobotContainer::drivetrain->SetEncoderPositions(0, 0);
    RobotContainer::autoRecorder->StartRecording();
}

void AutoRecord::Execute() {
    RobotContainer::autoRecorder->RecordPeriodic();
}

void AutoRecord::End(bool interrupted) {
    RobotContainer::autoRecorder->StopRecording();
}

bool AutoRecord::IsFinished() {
  return false;
}
