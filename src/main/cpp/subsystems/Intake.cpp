// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

Intake::Intake() {
    intakeSpark = std::make_unique<rev::CANSparkMax>(Constants::MotorIDs::intake, rev::CANSparkMax::MotorType::kBrushless);
    ConfigureSpark(*intakeSpark);
}

void Intake::Run(bool reverse) {
    intakeSpark->Set(reverse ? -0.3 : 0.3);
}

void Intake::Stop() {
    intakeSpark->Set(0);
}

void Intake::SetSpeed(double speed) {
    intakeSpark->Set(speed);
}

// rt bumper driver controller
void Intake::ConfigureSpark(rev::CANSparkMax& controller) {
    const uint16_t currentLimit = 60;
    const uint16_t limitThreshold = 90;
    controller.SetSmartCurrentLimit(currentLimit);
    controller.SetSecondaryCurrentLimit(limitThreshold);
    controller.SetOpenLoopRampRate(rampRate.value());
    controller.SetClosedLoopRampRate(rampRate.value());
    controller.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
}

// This method will be called once per scheduler run
void Intake::Periodic() {}
