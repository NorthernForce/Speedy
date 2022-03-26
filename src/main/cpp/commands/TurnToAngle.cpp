/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TurnToAngle.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/TimedRobot.h>
#include "RobotContainer.h"
#include <frc2/command/CommandScheduler.h>
#include <tuple>

double TurnToAngle::distanceToTargetAngle;
bool TurnToAngle::isTurnFinished;

TurnToAngle::TurnToAngle(double target) {
    SetName("TurnToAngle");

    AddRequirements(RobotContainer::drivetrain.get());

    if (target != 0)
        SetAngle(target);
    isTurnFinished = false;
}

void TurnToAngle::SetAngle(double angle) {
    distanceToTargetAngle = angle;
}

// Called when the command is initially scheduled.
void TurnToAngle::Initialize() {
    currentAngle = RobotContainer::imu->GetRotation();
    startingAngle = currentAngle;
    //rawTargetAngle = currentAngle + distanceToTargetAngle;
    //integral = 0;
}

// Called repeatedly when this Command is scheduled to run
void TurnToAngle::Execute() {
    currentAngle = RobotContainer::imu->GetRotation();
    error = (currentAngle - startingAngle);

    rotMult = GetRotationMultiplier();
    rotLim = error * rotMult;
    frc::SmartDashboard::PutNumber("final rot:", GetRotationMultiplier());
    
    RobotContainer::drivetrain->DriveUsingSpeeds(-GetRotationMultiplier(), GetRotationMultiplier());

}

double TurnToAngle::GetRotationMultiplier() {
    double rotMultiplier;
    if (error < 0)
        rotMultiplier = (1.2 * pow(7.7, -error)) - .83;
    else
        rotMultiplier = (1.2 * pow(7.7, error)) - .83;
    frc::SmartDashboard::PutNumber("tta: error", error);
    frc::SmartDashboard::PutNumber("rotation multiplier:", rotMultiplier);
    return rotMultiplier;
}

void TurnToAngle::End(bool interrupted) {
    //RobotContainer::drivetrain->DriveUsingSpeeds(0, 0);
}

double TurnToAngle::GetAbsoluteAngleFromStartAndDistance(double start, double distance) {
    double outputAngle;

    if (distance + start >= 180)
        outputAngle = -360 + (distance + start);
    else if (distance + start <= -180)
        outputAngle = 360 + (distance + start);
    else
        outputAngle = rawTargetAngle;

    return outputAngle;
}

double TurnToAngle::ConvertAngleTo360DegreeScale(double angle) {
    angle = (fmod(angle, 360) + (angle - trunc(angle)));

    if (angle > 0)
        return angle;
    else
        return angle + 360;
}

bool TurnToAngle::GetIsAngleBetweenBoundingAngles(double input, double bound_a, double bound_b) {
    bool isAngleBetween;

    input = ConvertAngleTo360DegreeScale(input);
    bound_a = ConvertAngleTo360DegreeScale(bound_a);
    bound_b = ConvertAngleTo360DegreeScale(bound_b);

    if (bound_a < bound_b)
        isAngleBetween = bound_a <= input && input <= bound_b;
    else
        isAngleBetween = bound_a <= input || input <= bound_b;

    if (distanceToTargetAngle >= 0)
        isAngleBetween = !isAngleBetween;

    return isAngleBetween;
}

bool TurnToAngle::HasPassedTargetAngle() {
    targetAngle = GetAbsoluteAngleFromStartAndDistance(startingAngle, distanceToTargetAngle);
    bool isAngleInArea = GetIsAngleBetweenBoundingAngles(currentAngle, startingAngle, targetAngle);
    bool isNearTarget = abs(currentAngle) >= abs(targetAngle)-1 && abs(currentAngle) <= abs(targetAngle)+1;

    return isAngleInArea && isNearTarget;
}

bool TurnToAngle::IsFinished() {
    isTurnFinished = std::abs(error) < minError;
        
    return (isTurnFinished || HasPassedTargetAngle());
    //return (isTurnFinished);

}

double TurnToAngle::GetCurrentError() {
    return error;
}

double TurnToAngle::GetMinimumError() {
    return minError;
}

bool TurnToAngle::GetIsFinished() {
    return isTurnFinished;
}