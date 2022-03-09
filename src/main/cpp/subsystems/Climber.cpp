// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Climber.h"
#include "Constants.h"

Climber::Climber() {
    climber = std::make_unique<frc::Solenoid>(Constants::PCMCanBusID, frc::PneumaticsModuleType::REVPH, Constants::climber);

    leftMotor = std::make_unique<WPI_TalonFX>(Constants::MotorIDs::leftClimber);
    rightMotor = std::make_unique<WPI_TalonFX>(Constants::MotorIDs::rightClimber);

    ConfigureController(*leftMotor);
    ConfigureController(*rightMotor);
}

void Climber::ConfigureController(WPI_TalonFX& controller) {
    const int currentLimit = 60;
    const int limitThreshold = 90;
    const int triggerThreshTimeInSec = 1;
    controller.ConfigSupplyCurrentLimit(SupplyCurrentLimitConfiguration(true, currentLimit, limitThreshold, triggerThreshTimeInSec));
    controller.SetNeutralMode(ctre::phoenix::motorcontrol::Brake);
}

void Climber::PivotUp() {
    climber->Set(true);
    pivotPosition = PivotState::Up;
}

void Climber::PivotDown() {
    climber->Set(false);
    pivotPosition = PivotState::Down;
}

PivotState Climber::GetPivot() {
    return pivotPosition;
}

void Climber::SetPivot(PivotState state) {
    pivotPosition = state;
}

void Climber::Raise() {
    leftMotor->Set(-0.85);
    rightMotor->Set(0.85);
}

void Climber::Lower() {
    leftMotor->Set(0.65);
    rightMotor->Set(-0.65);
}

void Climber::Stop(){
    leftMotor->Set(0);
    rightMotor->Set(0);
}

HookState Climber::GetHookState() {
    return hookPosition;
}

void Climber::SetHookState(HookState state) {
    hookPosition = state;
}

// This method will be called once per scheduler run
void Climber::Periodic() {}
