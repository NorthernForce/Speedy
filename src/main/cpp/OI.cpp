#include "Constants.h"
#include "OI.h"
#include "commands/DriveWithJoystick.h"
#include <frc/smartdashboard/SmartDashboard.h>

std::shared_ptr<frc::XboxController> OI::driverController;
std::shared_ptr<frc::XboxController> OI::manipulatorController;

OI::OI() {
    frc::SmartDashboard::PutNumber("Drive Speed:", 1.0); 
    InitControllers();
}

void OI::InitControllers() {
    driverController = std::make_shared<frc::XboxController>(Constants::driverController_id);
    manipulatorController = std::make_shared<frc::XboxController>(Constants::manipulatorController_id);
}

void OI::MapControllerButtons() {}

std::pair<double, double> OI::GetDriveControls() {
  double speed = driverController->GetLeftY();
  double rotation = driverController->GetRightX();
  double multiplier = GetDriveSpeedMultiplier();
  return std::make_pair(speed*multiplier, rotation*multiplier);
}

double OI::GetDriveSpeedMultiplier() {
    double speedMultiplier = frc::SmartDashboard::GetNumber("Drive Speed:", 1.0);
    return CheckAndLimitValue(speedMultiplier);
}

void OI::SetControllerRumble(frc::XboxController *controller, double value, bool lightly) {
  if (lightly)
    controller->SetRumble(frc::GenericHID::RumbleType::kRightRumble, value);
  else
    controller->SetRumble(frc::GenericHID::RumbleType::kLeftRumble, value);
}

double OI::CheckAndLimitValue(double value, double upperLimit, double lowerLimit) {
  if (value < lowerLimit)
    value = lowerLimit;
  else if (value > upperLimit)
    value = upperLimit;
  return value;
}

frc2::Button OI::SimpleButton(std::shared_ptr<frc::GenericHID> controller, int btn) {
  return frc2::Button([this, controller, btn] { return controller->GetRawButton(btn); });
}

frc2::Button OI::SimpleAxis(std::shared_ptr<frc::GenericHID> controller, int axis, double threshold) {
  return frc2::Button([this, controller, axis, threshold] { return controller->GetRawAxis(axis) > threshold; });
}

frc2::Button OI::SimplePOV(std::shared_ptr<frc::GenericHID> controller, int degs) {
    return frc2::Button([this, controller, degs] { return (controller->GetPOV(degs) == degs); });
}