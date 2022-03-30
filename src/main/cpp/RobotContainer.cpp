// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include "commands/DriveWithJoystick.h"
#include "commands/autonomous/OneBall.h"
#include "commands/autonomous/TwoBalls.h"
#include "commands/autonomous/ThreeBall.h"
#include "commands/autonomous/DoNothing.h"

std::shared_ptr<OI> RobotContainer::oi;
std::shared_ptr<Drivetrain> RobotContainer::drivetrain;
std::shared_ptr<IMU> RobotContainer::imu;
std::shared_ptr<Intake> RobotContainer::intake;
std::shared_ptr<Navigation> RobotContainer::navigation;
std::shared_ptr<PCM> RobotContainer::pcm;
std::shared_ptr<Coordinates> RobotContainer::coordinates;
std::shared_ptr<Climber> RobotContainer::climber;
std::shared_ptr<FMSComms> RobotContainer::fmsComms;
std::shared_ptr<Ultrasonic> RobotContainer::ultrasonic;
std::shared_ptr<TXTInterface> RobotContainer::txtInterface;

RobotContainer::RobotContainer() {
    oi.reset(new OI());
    InitSubsystems();
    oi->MapControllerButtons();
    InitDefaultCommands();

    autonomousChooser.SetDefaultOption("1) One Ball", new OneBall());
    autonomousChooser.AddOption("2) Two Balls", new TwoBalls());
    autonomousChooser.AddOption("3) 3 Balls", new ThreeBall());
    autonomousChooser.AddOption("4) Do Nothing", new DoNothing());
    frc::SmartDashboard::PutData("Autonomous Modes", &autonomousChooser);
}

void RobotContainer::InitSubsystems() {
    drivetrain.reset(new Drivetrain);
    imu.reset(new IMU);
    intake.reset(new Intake);
    navigation.reset(new Navigation);
    pcm.reset(new PCM);
    coordinates.reset(new Coordinates);
    climber.reset(new Climber);
    fmsComms.reset(new FMSComms);
    ultrasonic.reset(new Ultrasonic);
    txtInterface.reset(new TXTInterface);
}

void RobotContainer::InitDefaultCommands() {
    drivetrain->SetDefaultCommand(DriveWithJoystick());
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // Runs the chosen command in autonomous
  return autonomousChooser.GetSelected();
}