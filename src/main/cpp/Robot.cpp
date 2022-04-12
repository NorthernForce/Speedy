// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include "RobotContainer.h"
#include <cameraserver/CameraServer.h>

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>

#include "subsystems/Climber.h"
#include "commands/autonomous/DriveToDistance.h"
#include "commands/autonomous/DriveToDistanceIntake.h"
#include "commands/TurnToAngle.h"
#include "commands/MoveArm.h"
#include "commands/ResetEncoders.h"
#include "commands/autonomous/AutoTurnToAngle.h"

#include "commands/AutoPlayback.h"
#include "commands/AutoRecord.h"

#include <frc/Timer.h>

void Robot::RobotInit() {
    //RobotContainer::climber->SetPivot(PivotState::Up);
    //RobotContainer::intake->SetArmState(ArmState::Down);
    RobotContainer::drivetrain->SetEncoderPositions(0, 0);
    RobotContainer::intake->ArmUp();
    autoPlayback = std::make_unique<AutoPlayback>();
    autoRecord = std::make_unique<AutoRecord>();
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
  RobotContainer::fmsComms->DisplayMatchTime();
  //RobotContainer::drivetrain->PrintEncoderValues();
  //frc::SmartDashboard::PutNumber("distance: ", RobotContainer::ultrasonic->getDistance());
  //frc::SmartDashboard::PutString("Drive Speed", RobotContainer::fmsComms->GetAllianceString(RobotContainer::fmsComms->GetAlliance()));
  //printf("Please work %f: \n", leftSide[4]);
  
  }
/**
 * This function is called once each time the robot enters Disabled mode. You`
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {
    RobotContainer::intake->ArmUp();
    wannaRecord = false;
    wannaPlayback = false;
    frc::SmartDashboard::PutBoolean("Recording Mode: ", wannaRecord);
    frc::SmartDashboard::PutBoolean("Playback Mode: ", wannaPlayback);
    autoRecord->Cancel();
    autoPlayback->Cancel();
}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit() {
    RobotContainer::imu->ZeroRotation();
    //RobotContainer::climber->PivotDown();
    autoCommandScheduler.reset(new AutoCommandScheduler({
    
    new ResetEncoders(),
    new DriveToDistanceIntake(.2, -10, true),
    new AutoTurnToAngle(-180, false),
    new DriveToDistanceIntake(-.4, 20, false),
    new AutoTurnToAngle(-180, false),

    // 3 BALL
    // new ResetEncoders(),
    // new DriveToDistanceIntake(.2, -20, true),
    // new MoveArm(false),
    // new ResetEncoders(),
    // new AutoTurnToAngle(-92.7, false),
    // new ResetEncoders(),
    // new DriveToDistanceIntake(-.4, 38, false),
    // new ResetEncoders(),
    // new AutoTurnToAngle(-113.8, false),
    // new ResetEncoders(),
    // new DriveToDistanceIntake(-.4, 55, false),
    // new ResetEncoders(),
    // new AutoTurnToAngle(-79, false),
    // new ResetEncoders(),
    // new DriveToDistance(-.4, 18),
    // new MoveArm(true),
    // new ResetEncoders(),
    // new AutoTurnToAngle(-20, false),
    // new ResetEncoders(),
    // new DriveToDistanceIntake(-.4, 15, true),

    //new ResetEncoders(),
    //new AutoTurnToAngle(-35, false),
    //new ResetEncoders(),
    //new DriveToDistanceIntake(-.4, 80, false),



    }));
}

void Robot::AutonomousPeriodic() {
    autoCommandScheduler->RunSequential();
}

void Robot::TeleopInit() {
    RobotContainer::intake->ArmUp();
    wannaRecord = frc::SmartDashboard::GetBoolean("Recording Mode: ", false);
    if (wannaRecord)
        autoRecord->Schedule();
    wannaPlayback = frc::SmartDashboard::GetBoolean("Playback Mode: ", false);
    if (wannaPlayback)
        autoPlayback->Schedule();
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {
    //RobotContainer::drivetrain->RecordMotorPos();
}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
