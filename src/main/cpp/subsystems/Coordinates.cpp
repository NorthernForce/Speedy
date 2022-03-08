// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Coordinates.h"
#include "RobotContainer.h"

Coordinates::Coordinates() {}

CPlane::Point Coordinates::GetLocation() {
    return location;
}

void Coordinates::SetLocation(CPlane::Point newLocation) {
    location = newLocation;
}

units::degree_t Coordinates::EncoderDegreesChange() {
    currEncPositions = RobotContainer::drivetrain->GetEncoderRotations();
    units::degree_t avgCurrEncPos{(currEncPositions.first + currEncPositions.second) / 2};
    encChange = avgCurrEncPos - lastAvgEncPos;
    lastAvgEncPos = avgCurrEncPos;
    return encChange;
}

units::inch_t Coordinates::DistanceTravelled() {
    wheelSpinPercent = EncoderDegreesChange() / 360_deg;
    return Constants::wheelCircum * wheelSpinPercent;
}

units::degree_t Coordinates::Theta() {
    return units::degree_t(-RobotContainer::imu->GetRotation()) + navXOffsetAngle;
}

void Coordinates::SetTheta(units::degree_t newTheta) {
    navXOffsetAngle = newTheta - units::degree_t(-RobotContainer::imu->GetRotation());
}

CPlane::Point Coordinates::PointMoved() {
    distance = DistanceTravelled();
    dx = distance * units::math::sin(Theta());
    dy = distance * units::math::cos(Theta());
    return CPlane::Point(dx, dy, true);
}

void Coordinates::UpdateLocation() {
    location = location.Add(PointMoved());
}

// This method will be called once per scheduler run
void Coordinates::Periodic() { 
    UpdateLocation();

    printf("periodic %f,%f\n", location.x.value(), location.y.value());
    frc::SmartDashboard::PutNumber("X Position:", location.x.value());
    frc::SmartDashboard::PutNumber("Y Position:", location.y.value());
    frc::SmartDashboard::PutNumber("Theta: ", Theta().value());
}
