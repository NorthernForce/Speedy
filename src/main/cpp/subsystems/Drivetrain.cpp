// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Drivetrain.h"
#include "Constants.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include <frc/SPI.h>
#include "RobotContainer.h"

std::shared_ptr<WPI_TalonFX> Drivetrain::leftPrimary;
std::shared_ptr<WPI_TalonFX> Drivetrain::rightPrimary;
std::shared_ptr<frc::DifferentialDrive> Drivetrain::robotDrive;

Drivetrain::Drivetrain() {
    leftPrimary = std::make_shared<WPI_TalonFX>(Constants::MotorIDs::leftPrimary);
    rightPrimary = std::make_shared<WPI_TalonFX>(Constants::MotorIDs::rightPrimary);
    leftFollower = std::make_shared<WPI_TalonFX>(Constants::MotorIDs::leftFollower);
    rightFollower = std::make_shared<WPI_TalonFX>(Constants::MotorIDs::rightFollower);

    SetInvert();
    SetFollowers();
    ConfigureAllControllers();

    robotDrive = std::make_shared<frc::DifferentialDrive>(*leftPrimary, *rightPrimary);

    SetEncoderPositions(0, 0);
}

void Drivetrain::SetFollowers() {
    leftFollower->Follow(*leftPrimary);
    rightFollower->Follow(*rightPrimary);
}

void Drivetrain::SetInvert(){
    rightPrimary->SetInverted(true);
    rightFollower->SetInverted(InvertType::FollowMaster);
    leftPrimary->SetInverted(false);
    leftFollower->SetInverted(InvertType::FollowMaster);
}

void Drivetrain::ConfigureAllControllers() {
    ConfigureController(*leftPrimary);
    ConfigureController(*rightPrimary);
    ConfigureController(*leftFollower, true);
    ConfigureController(*rightFollower, true);
}

void Drivetrain::ConfigureController(WPI_TalonFX& controller, bool isFollower) {
    const int currentLimit = 60;
    const int limitThreshold = 90;
    const int triggerThreshTimeInSec = 1;
    controller.ConfigSupplyCurrentLimit(SupplyCurrentLimitConfiguration(true, currentLimit, limitThreshold, triggerThreshTimeInSec));
    if (!isFollower) {
        controller.ConfigClosedloopRamp(rampRate);
        controller.ConfigOpenloopRamp(rampRate);
    }
    controller.SetNeutralMode(ctre::phoenix::motorcontrol::Brake);
}

void Drivetrain::Drive(double speed, double rotation) {
    robotDrive->ArcadeDrive(speed, rotation * 0.75);
}

void Drivetrain::DriveUsingSpeeds(double leftSpeed, double rightSpeed) {
    leftPrimary->Set(leftSpeed);
    rightPrimary->Set(rightSpeed);
}

std::pair<double, double> Drivetrain::GetEncoderRotations() {
    double leftSideRotations = leftPrimary->GetSensorCollection().GetIntegratedSensorPosition() / 2048;
    double rightSideRotations = (rightPrimary->GetSensorCollection().GetIntegratedSensorPosition() * -1) / 2048; ////TODO: check this
    return std::make_pair(leftSideRotations, rightSideRotations);
}

void Drivetrain::SetEncoderPositions(double lt, double rt) {
    leftPrimary->SetSelectedSensorPosition(lt);
    rightPrimary->SetSelectedSensorPosition(rt);
}

double Drivetrain::GetLeftRPM() {
    return leftPrimary->GetSensorCollection().GetIntegratedSensorVelocity();
}

double Drivetrain::GetRightRPM() {
    return rightPrimary->GetSensorCollection().GetIntegratedSensorVelocity();
}

bool Drivetrain::IsTipping() {
    return RobotContainer::imu->GetRollAngle() > abs(tipAngle.value());
}
 
void Drivetrain::Periodic() {
    frc::SmartDashboard::PutNumber("left encoder", GetEncoderRotations().first);
    frc::SmartDashboard::PutNumber("right encoder", GetEncoderRotations().second);
}
