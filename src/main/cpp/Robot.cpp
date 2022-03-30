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

#include <frc/Timer.h>

void Robot::RobotInit() {
    //RobotContainer::climber->SetPivot(PivotState::Up);
    //RobotContainer::intake->SetArmState(ArmState::Down);
    RobotContainer::drivetrain->SetEncoderPositions(0, 0);
    RobotContainer::intake->ArmUp();
    //frc::CameraServer::StartAutomaticCapture();
    //leftSide = RobotContainer::TXTInterface->ReadTextFile("LeftTest");
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
  RobotContainer::drivetrain->PrintEncoderValues();
  printf("Rotation: %lf\n", RobotContainer::imu->GetRotation());
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
    //RobotContainer::drivetrain->WriteLeftMotorPos("LeftTest");
    //RobotContainer::drivetrain->WriteRightMotorPos("RightTest");
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

    //1 Ball
    //new DriveToDistanceIntake(.2, -40, true),
    
    //2 BALL
    // new ResetEncoders(),
    // new DriveToDistanceIntake(.2, -10, true),
    // new ResetEncoders(),
    // new AutoTurnToAngle(-170, false),
    // new ResetEncoders(),
    // new MoveArm(false),
    // new AutoTurnToAngle(-15, false),
    // new ResetEncoders(),
    // new DriveToDistanceIntake(-.4, 28, false),
    // new ResetEncoders(),
    // new AutoTurnToAngle(-180, false),
    // new ResetEncoders(),
    // new DriveToDistance(-.4, 35),
    // new ResetEncoders(),
    // new MoveArm(true),
    // new ResetEncoders(),
    // new AutoTurnToAngle(-5, false),
    // new ResetEncoders(),
    // new DriveToDistanceIntake(-.4, 10, true),


    //3 BALL
    new ResetEncoders(),
    new DriveToDistanceIntake(.2, -20, true),
    new MoveArm(false),
    new ResetEncoders(),
    new AutoTurnToAngle(-117, false),
    new ResetEncoders(),
    new DriveToDistanceIntake(-.4, 37.5, false),
    new ResetEncoders(),
    new AutoTurnToAngle(-135, false),
    new ResetEncoders(),
    new DriveToDistanceIntake(-.4, 16, false),
    new ResetEncoders(),
    new AutoTurnToAngle(-14, false),
    new ResetEncoders(),
    new DriveToDistanceIntake(-.4, 50, false),
    new ResetEncoders(),
    new DriveToDistance(.2, -15),
    new ResetEncoders(),
    new AutoTurnToAngle(-90, false),
    new ResetEncoders(),
    new DriveToDistance(-.4, 25),
    new MoveArm(true),
    new ResetEncoders(),
    new AutoTurnToAngle(-36, false),
    new ResetEncoders(),
    new DriveToDistance(-.4, 12),
    new ResetEncoders(),
    new DriveToDistanceIntake(-.4, 18, true),

    }));
}

void Robot::AutonomousPeriodic() {
    autoCommandScheduler->RunSequential();
}

void Robot::TeleopInit() {
    RobotContainer::intake->ArmUp();
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
