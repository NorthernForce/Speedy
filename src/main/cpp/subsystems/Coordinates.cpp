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

units::inch_t Coordinates::GetInchesChange() {
    currInches = RobotContainer::drivetrain->GetInchesTravelled();
    units::inch_t avgInches{(currInches.first.value() + currInches.second.value()) / 2};
    inchChange = avgInches - lastAvgInches;
    lastAvgInches = avgInches;
    return inchChange;
}

// units::inch_t Coordinates::DistanceTravelled() {
//     wheelSpinPercent = EncoderDegreesChange() / 360_deg;
//     return Constants::wheelCircum * wheelSpinPercent;
// }

units::degree_t Coordinates::Theta() {
    return units::degree_t(-RobotContainer::imu->GetRotation()) + navXOffsetAngle;
}

void Coordinates::SetTheta(units::degree_t newTheta) {
    navXOffsetAngle = newTheta - units::degree_t(-RobotContainer::imu->GetRotation());
}

CPlane::Point Coordinates::PointMoved() {
    distance = GetInchesChange();
    dx = distance * units::math::cos(Theta());
    dy = distance * units::math::sin(Theta());
    return CPlane::Point(dx, dy, true);
}

void Coordinates::UpdateLocation() {
    location = location.Add(PointMoved());
}

// This method will be called once per scheduler run
void Coordinates::Periodic() { 
    // UpdateLocation();
    
    frc::SmartDashboard::PutNumber("X Position:", location.x.value());
    frc::SmartDashboard::PutNumber("Y Position:", location.y.value());
    frc::SmartDashboard::PutNumber("Get Inches: ", RobotContainer::drivetrain->GetInchesTravelled().first.value());
    frc::SmartDashboard::PutNumber("Theta: ", Theta().value());
}
