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

    bottom = std::make_unique<frc::DigitalInput>(Constants::DigitalIDs::bottomOptical);
    middle = std::make_unique<frc::DigitalInput>(Constants::DigitalIDs::middleOptical);
    top = std::make_unique<frc::DigitalInput>(Constants::DigitalIDs::topOptical);

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
    climber->Set(false);
    pivotPosition = PivotState::Up;
    heightCheckNeeded = true;
}

void Climber::PivotDown() {
    climber->Set(true);
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

void Climber::Stop() {
    leftMotor->Set(0);
    rightMotor->Set(0);
}

double Climber::SpoolRotations() {
    return leftMotor->GetSensorCollection().GetIntegratedSensorPosition();
}

void Climber::ResetSpool() {
    leftMotor->GetSensorCollection().SetIntegratedSensorPosition(0.0);
    rightMotor->GetSensorCollection().SetIntegratedSensorPosition(0.0);
}

bool Climber::TooTall(){
    return ((GetPivot() == PivotState::Up && GetOpticalSensor(Constants::DigitalIDs::middleOptical))
        || (GetOpticalSensor(Constants::DigitalIDs::topOptical)));
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
void Climber::CheckHeight(){
    if (heightCheckNeeded) {
        if(TooTall()) {
            Lower();
        }
        else {
            Stop();
            heightCheckNeeded = false;
        }
    }
}

HookState Climber::GetHookState() {
    return hookPosition;
}

void Climber::SetHookState(HookState state) {
    hookPosition = state;
}

bool Climber::GetOpticalSensor(int sensor) {
    switch (sensor) {
        case Constants::DigitalIDs::bottomOptical:
            return bottom->Get();
        case Constants::DigitalIDs::middleOptical:
            return middle->Get();
        case Constants::DigitalIDs::topOptical:
            return top->Get();
        default:
            return false;
    }
}

// This method will be called once per scheduler run
void Climber::Periodic() {
    CheckHeight();
}