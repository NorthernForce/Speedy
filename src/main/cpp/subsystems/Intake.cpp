// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include "subsystems/Intake.h"

Intake::Intake() {
    intakeTopSpark = std::make_unique<rev::CANSparkMax>(Constants::MotorIDs::intakeTop, rev::CANSparkMax::MotorType::kBrushless);
    intakeBottomSpark = std::make_unique<rev::CANSparkMax>(Constants::MotorIDs::intakeBottom, rev::CANSparkMax::MotorType::kBrushless);

    highMotor = std::make_unique<WPI_TalonFX>(Constants::MotorIDs::highShooter);

    ConfigureSpark(*intakeTopSpark);
    ConfigureSpark(*intakeBottomSpark);
    ConfigureController(*highMotor);

    arm = std::make_unique<frc::Solenoid>(Constants::PCMCanBusID, frc::PneumaticsModuleType::REVPH, Constants::PneumaticIDs::arm);
}

void Intake::ConfigureController(WPI_TalonFX& controller) {
    const int currentLimit = 60;
    const int limitThreshold = 90;
    const int triggerThreshTimeInSec = 1;
    controller.ConfigSupplyCurrentLimit(SupplyCurrentLimitConfiguration(true, currentLimit, limitThreshold, triggerThreshTimeInSec));
    controller.SetNeutralMode(ctre::phoenix::motorcontrol::Brake);
}

void Intake::Run(IntakeDirection direction) {
    intakeBottomSpark->Set(bool(direction) ? 0.9 : -0.9);
    intakeTopSpark->Set(bool(direction) ? -.5 : .5);
}

void Intake::ShootHigh() {
    highMotor->Set(.8);
    //printf("%f \n", highMotor->GetSensorCollection().GetIntegratedSensorVelocity());
}

void Intake::ReverseHigh() {
    highMotor->Set(-.3);
}

void Intake::UltraShoot() {
    ultraDist = RobotContainer::ultrasonic->getDistance();
    if (ultraDist < 20) {
        intakeTopSpark->Set(0.7);
        intakeBottomSpark->Set(-0.9);
    }
    else {
        Run(IntakeDirection::outtake);
    }
}

void Intake::Stop() {
    intakeTopSpark->Set(0);
    intakeBottomSpark->Set(0);
    highMotor->Set(0);
}

void Intake::SetSpeed(double speed) {
    intakeTopSpark->Set(speed);
    intakeBottomSpark->Set(speed);
}

rev::SparkMaxRelativeEncoder Intake::SparkEncoderPosition() {
    //return spark.GetEncoder().GetPosition();
    return intakeTopSpark->GetEncoder();
}

void Intake::ConfigureSpark(rev::CANSparkMax& spark) {
    // const uint16_t currentLimit = 60;
    // const uint16_t limitThreshold = 90;
    // intakeTopSpark->SetSmartCurrentLimit(currentLimit);
    // intakeTopSpark->SetSecondaryCurrentLimit(limitThreshold);
    spark.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
}

int Intake::GetCurrentRPM() {
    //double velocity = -highMotor->GetSensorCollection().GetIntegratedSensorVelocity();
    //int rpm = (velocity * 600) / 2048;
    return highMotor->GetSensorCollection().GetIntegratedSensorVelocity();
}

int Intake::GetError() {
    return Constants::targetRPM - GetCurrentRPM();
}

Intake::ArmState Intake::GetPivot() {
    return armPosition;
}

void Intake::SetArmState(ArmState state) {
    armPosition = state;
}

void Intake::ArmUp() {
    arm->Set(false);
    armPosition = ArmState::Up;
}

void Intake::ArmDown() {
    arm->Set(true);
    armPosition = ArmState::Down;
}
