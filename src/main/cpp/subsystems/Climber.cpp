// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Climber.h"
#include "Constants.h"
#include "RobotContainer.h"


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
    leftMotor->Set(-1);
    rightMotor->Set(1);
}

void Climber::Lower() {
    leftMotor->Set(1);
    rightMotor->Set(-1);
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

void Climber::Initialize() {
    // states = {
    //     frc::DigitalInput dio0{0},
    //     frc::Digitalnput dio1{1},
    //     frc::DigitalInput dio2{2}
    // };
}

// This method will be called once per scheduler run
void Climber::Periodic() {
    frc::SmartDashboard::PutBoolean("Digital 0: ", dio0.Get());
    frc::SmartDashboard::PutBoolean("Digital 1: ", dio1.Get());
    frc::SmartDashboard::PutBoolean("Digital 2: ", dio2.Get());
    //TRUE IS WHEN THE SHAFT IS ABOVE
    //DIGITAL 2 IS BOTTOM
    //DIGITAL 0 IS MID SENSOR
    //DIGITAL 1 IS TOP SENSOR
}
