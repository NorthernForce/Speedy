// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include "commands/DriveWithJoystick.h"

std::shared_ptr<OI> RobotContainer::oi;
std::shared_ptr<Drivetrain> RobotContainer::drivetrain;
std::shared_ptr<Navigation> RobotContainer::navigation;

RobotContainer::RobotContainer() {
    oi.reset(new OI());
    InitSubsystems();
    oi->MapControllerButtons();
    InitDefaultCommands();
}

void RobotContainer::InitSubsystems() {
    drivetrain.reset(new Drivetrain);
    navigation.reset(new Navigation);
}

void RobotContainer::InitDefaultCommands() {
    drivetrain->SetDefaultCommand(DriveWithJoystick());
}