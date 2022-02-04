// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/IMU.h"
#include "RobotContainer.h"
#include <frc/SPI.h>

IMU::IMU() {
    ahrs = std::make_unique<AHRS>(frc::SPI::Port::kMXP);
    ahrs->ResetDisplacement();
    ZeroRotation();
}

// This method will be called once per scheduler run
void IMU::Periodic() {
    frc::SmartDashboard::PutNumber("Robot angle: ", GetRotation());
}

double IMU::GetRollAngle() {
    return ahrs->GetRoll();
}

double IMU::GetRotation() {
    return ahrs->GetYaw();
}

void IMU::ZeroRotation() {
    ahrs->ZeroYaw();
}

void IMU::Reset() {
    ahrs->Reset();
}