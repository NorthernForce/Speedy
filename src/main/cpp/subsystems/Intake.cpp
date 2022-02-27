// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

Intake::Intake() {
    intakeSpark = std::make_unique<rev::CANSparkMax>(Constants::MotorIDs::intake, rev::CANSparkMax::MotorType::kBrushless);

    arm = std::make_unique<frc::Solenoid>(Constants::PCMCanBusID, frc::PneumaticsModuleType::REVPH, Constants::arm);
}

void Intake::Run(bool reverse) {
    intakeSpark->Set(reverse ? -1.0 : 0.45);
}

void Intake::Stop() {
    intakeSpark->Set(0);
}

void Intake::SetSpeed(double speed) {
    intakeSpark->Set(speed);
}

void Intake::ConfigureSpark() {
    const uint16_t currentLimit = 60;
    const uint16_t limitThreshold = 90;
    intakeSpark->SetSmartCurrentLimit(currentLimit);
    intakeSpark->SetSecondaryCurrentLimit(limitThreshold);
    intakeSpark->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    intakeSpark->SetInverted(true);
}

ArmState Intake::GetPivot() {
    return armPosition;
}

void Intake::SetArmState(ArmState state) {
    armPosition = state;
}

void Intake::ArmUp() {
    arm->Set(true);
    armPosition = ArmState::Up;
}

void Intake::ArmDown() {
    arm->Set(false);
    armPosition = ArmState::Down;
}

// This method will be called once per scheduler run
void Intake::Periodic() {}
