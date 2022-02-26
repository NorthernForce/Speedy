// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include "commands/DriveWithJoystick.h"

std::shared_ptr<OI> RobotContainer::oi;
std::shared_ptr<Drivetrain> RobotContainer::drivetrain;
std::shared_ptr<IMU> RobotContainer::imu;
std::shared_ptr<Intake> RobotContainer::intake;
std::shared_ptr<Navigation> RobotContainer::navigation;
std::shared_ptr<PCM> RobotContainer::pcm;
std::shared_ptr<Coordinates> RobotContainer::coordinates;
std::shared_ptr<Climber> RobotContainer::climber;


RobotContainer::RobotContainer() {
    oi.reset(new OI());
    InitSubsystems();
    oi->MapControllerButtons();
    InitDefaultCommands();
}

void RobotContainer::InitSubsystems() {
    drivetrain.reset(new Drivetrain);
    imu.reset(new IMU);
    intake.reset(new Intake);
    navigation.reset(new Navigation);
    pcm.reset(new PCM);
    coordinates.reset(new Coordinates);
}

void RobotContainer::InitDefaultCommands() {
    drivetrain->SetDefaultCommand(DriveWithJoystick());
}