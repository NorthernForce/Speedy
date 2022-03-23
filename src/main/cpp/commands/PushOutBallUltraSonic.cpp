// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/PushOutBallUltraSonic.h"

PushOutBallUltraSonic::PushOutBallUltraSonic() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void PushOutBallUltraSonic::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void PushOutBallUltraSonic::Execute() {
  RobotContainer::intake->UltraShoot();
}

// Called once the command ends or is interrupted.
void PushOutBallUltraSonic::End(bool interrupted) {
  RobotContainer::intake->Stop();
}

// Returns true when the command should end.
bool PushOutBallUltraSonic::IsFinished() {
  return false;
}
