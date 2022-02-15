// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Climber.h"
#include "Constants.h"

Climber::Climber() {
    leftClimber = std::make_unique<frc::Solenoid>(frc::PneumaticsModuleType::REVPH, Constants::leftClimber);
    rightClimber = std::make_unique<frc::Solenoid>(frc::PneumaticsModuleType::REVPH, Constants::rightClimber);

    leftMotor = std::make_unique<WPI_TalonFX>(Constants::MotorIDs::leftClimber);
    rightMotor = std::make_unique<WPI_TalonFX>(Constants::MotorIDs::rightClimber);
}

void Climber::ConfigureController(WPI_TalonFX& controller, bool isFollower) {
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

void Climber::PivotUp() {
    leftClimber->Set(true);
    rightClimber->Set(true);
    pivotPosition = PivotState::Up;
}

void Climber::PivotDown() {
    leftClimber->Set(false);
    rightClimber->Set(false);
    pivotPosition = PivotState::Down;
}

PivotState Climber::GetPivot() {
    return pivotPosition;
}

void Climber::Raise() [
    leftMotor->Set(0.5);
    rightMotor->Set(0.5);
    
]

void Climber::Lower() {
    leftMotor->Set(0.5);
    rightMotor->Set(0.5);
}

HookState Climber::GetHookState() {

}

// This method will be called once per scheduler run
void Climber::Periodic() {}
