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

bool Drivetrain::DriveToDistance(double desiredDistance, double speed) {
    if(desiredDistance < GetAvgEncoderRotations(GetEncoderRotations()) * Constants::encoderToInch) {
        leftPrimary->Set(speed);
        rightPrimary->Set(speed);
        return false;
    } else {
        leftPrimary->Set(0);
        rightPrimary->Set(0);
        return true;
    }
}

std::pair<double, double> Drivetrain::GetEncoderRotations() {
    double leftSideRotations = (leftPrimary->GetSensorCollection().GetIntegratedSensorPosition() * -1) / 2048;
    double rightSideRotations = rightPrimary->GetSensorCollection().GetIntegratedSensorPosition() / 2048;
    return std::make_pair(leftSideRotations, rightSideRotations);
}

std::pair<units::inch_t, units::inch_t> Drivetrain::GetInchesTravelled() {
    std::pair<double, double> rotations = GetEncoderRotations();
    units::inch_t leftInches = units::inch_t(rotations.first * Constants::encoderToInch);
    units::inch_t rightInches = units::inch_t(rotations.second * Constants::encoderToInch);
    return std::make_pair(leftInches, rightInches);
}

double Drivetrain::GetAvgEncoderRotations(std::pair<double, double>) {
    double avgRotations = (GetEncoderRotations().first + GetEncoderRotations().second)/2;
    return avgRotations;
}

void Drivetrain::SetEncoderPositions(double lt, double rt) {
    leftPrimary->SetSelectedSensorPosition(lt);
    rightPrimary->SetSelectedSensorPosition(rt);
}

void Drivetrain::PrintEncoderValues() {
  printf("Left Encoder : %lf\n", leftPrimary->GetSelectedSensorPosition());
  printf("Right Encoder: %lf\n", rightPrimary->GetSelectedSensorPosition());
  printf("Avg Encoder: %lf\n", GetAvgEncoderRotations(GetEncoderRotations()));
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

    if (IsTipping()) {
        RobotContainer::drivetrain->Drive(0 ,0);
    }
}
