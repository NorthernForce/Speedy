// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include "RobotContainer.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>

#include "subsystems/Climber.h"
#include "commands/autonomous/ShootThenCrossLine.h"

#include <frc/Timer.h>

void Robot::RobotInit() {
    //RobotContainer::climber->SetPivot(PivotState::Up);
    //RobotContainer::intake->SetArmState(ArmState::Down);
    RobotContainer::drivetrain->SetEncoderPositions(0, 0);
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
  
  }
/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit() {
    //RobotContainer::climber->PivotDown();
     autoCommandScheduler.reset(new AutoCommandScheduler({
         new ShootThenCrossLine()
    }));

    //new ShootThenCrossLine();
    }

void Robot::AutonomousPeriodic() {
    autoCommandScheduler->RunSequential();
    //frc2::CommandScheduler::GetInstance().Run();
}

void Robot::TeleopInit() {}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
