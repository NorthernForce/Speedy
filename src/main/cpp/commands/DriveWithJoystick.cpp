// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/DriveWithJoystick.h"
#include "RobotContainer.h"

DriveWithJoystick::DriveWithJoystick() {
    SetName("DriveWithJoystick");
    AddRequirements(RobotContainer::drivetrain.get());
}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute() {
    auto driveControls = RobotContainer::oi->GetDriveControls();
    speed = -driveControls.first;
    rotation = driveControls.second;

    RobotContainer::drivetrain->Drive(speed, rotation);
}

// Called once the command ends or is interrupted.
void DriveWithJoystick::End(bool interrupted) {
    RobotContainer::drivetrain->Drive(0, 0);
}

// Returns true when the command should end.
bool DriveWithJoystick::IsFinished() {
  return false;
}
