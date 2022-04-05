// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Climber.h"
#include "RobotContainer.h"


Climber::Climber() {
    climber = std::make_unique<frc::Solenoid>(Constants::PCMCanBusID, frc::PneumaticsModuleType::REVPH, Constants::PneumaticIDs::climber);

    leftMotor = std::make_unique<WPI_TalonFX>(Constants::MotorIDs::leftClimber);
    rightMotor = std::make_unique<WPI_TalonFX>(Constants::MotorIDs::rightClimber);

    bottom = std::make_unique<frc::DigitalInput>(Constants::DigitalIDs::bottomOptical);
    middle = std::make_unique<frc::DigitalInput>(Constants::DigitalIDs::middleOptical);
    top = std::make_unique<frc::DigitalInput>(Constants::DigitalIDs::topOptical);

    ConfigureController(*leftMotor);
    ConfigureController(*rightMotor);

    pivotPosition = PivotState::Up;
    frc::SmartDashboard::PutBoolean("Optical Sensor Get Error", false);
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
    leftMotor->Set(-1);
    rightMotor->Set(1);
}

void Climber::Lower() {
    leftMotor->Set(1);
    rightMotor->Set(-1);
}

void Climber::LowerSlow() {
    leftMotor->Set(0.1);
    rightMotor->Set(-0.1);
}

void Climber::Stop(){
    leftMotor->Set(0);
    rightMotor->Set(0);
}

bool Climber::TooTall() {
    return (
        (GetPivot() == PivotState::Up && GetOpticalSensor(Constants::DigitalIDs::middleOptical)) ||
        (GetOpticalSensor(Constants::DigitalIDs::topOptical))
    );
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
void Climber::CheckHeight(){
    if (TooTall()) {
        //LowerSlow();
        Stop();   
    }
    // else {
    //     //Stop();
    // }
}

bool Climber::GetOpticalSensor(Constants::DigitalIDs sensor) {
    switch (sensor) {
        case Constants::DigitalIDs::bottomOptical:
            return bottom->Get();
        case Constants::DigitalIDs::middleOptical:
            return middle->Get();
        case Constants::DigitalIDs::topOptical:
            return top->Get();
        default:
            frc::SmartDashboard::PutBoolean("Optical Sensor Get Error", true);
            return false;
    }
}

// void Climber::PrintOpticalSensors() {
//     frc::SmartDashboard::PutBoolean("Bottom Optical:", bottom->Get());
//     frc::SmartDashboard::PutBoolean("Middle Optical:", middle->Get());
//     frc::SmartDashboard::PutBoolean("Top Optical:", top->Get());
// }

// This method will be called once per scheduler run
void Climber::Periodic() {
    // CheckHeight();
    // PrintOpticalSensors();
}