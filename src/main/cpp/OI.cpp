#include "Constants.h"
#include "RobotContainer.h"
#include "commands/DriveWithJoystick.h"
#include "commands/IntakeBall.h"
#include "commands/PushOutBall.h"
#include "commands/MoveArm.h"
#include "commands/ToggleArm.h"
#include "commands/LowerClimber.h"
#include "commands/RaiseClimber.h"
#include "commands/PivotToggle.h"
#include "commands/ShootHigh.h"
#include "commands/PushOutBallUltraSonic.h"
#include "commands/ResetEncoders.h"
#include "commands/NoSensorClimbLower.h"
#include "commands/NoSensorClimbRaise.h"
#include "commands/autonomous/MoveToCoordinate.h"
#include "commands/autonomous/SetCoordinates.h"
#include "commands/autonomous/SetTheta.h"
#include <frc/smartdashboard/SmartDashboard.h>

std::shared_ptr<frc::XboxController> OI::driverController;
std::shared_ptr<frc::XboxController> OI::manipulatorController;

OI::OI()
{
  frc::SmartDashboard::PutNumber("Drive Speed:", 1.0);
  InitControllers();
  frc::SmartDashboard::PutNumber("Shooter RPM", 700);
  frc::SmartDashboard::PutNumber("Push forward duration", 10);
  frc::SmartDashboard::PutNumber("Intake Shoot Speed", .9);
}

void OI::InitControllers()
{
  driverController = std::make_shared<frc::XboxController>(Constants::driverController_id);
  manipulatorController = std::make_shared<frc::XboxController>(Constants::manipulatorController_id);
}

void OI::MapControllerButtons() {
    //driver
    SimpleAxis(driverController, XboxAxis::lt_trigger).WhileHeld(new ShootHigh);
    SimpleAxis(driverController, XboxAxis::rt_trigger).WhenPressed(new ToggleArm);
    SimpleButton(driverController, Xbox::rt_bumper).WhileHeld(new IntakeBall);
    SimpleButton(driverController, Xbox::lt_bumper).WhileHeld(new PushOutBallUltraSonic);
    SimpleButton(manipulatorController, Xbox::B_button).WhileHeld(new RaiseClimber);
    SimpleButton(manipulatorController, Xbox::A_button).WhileHeld(new LowerClimber);
    SimplePOV(driverController, XboxPOV::up).WhenPressed(new PivotToggle);
    //SimpleButton(driverController, Xbox::Y_button).WhenPressed(new ResetEncoders());
    //SimpleButton(driverController, Xbox::B_button).WhileHeld(new SetCoordinates(CPlane::Point(0_in, 0_in)));
    //SimpleButton(driverController, Xbox::B_button).WhileHeld(new SetTheta(0_deg));
    //SimpleButton(driverController, Xbox::X_button).WhenPressed(new MoveToCoordinate(CPlane::Point(24_in, 0_in)), 0.4);
    //SimpleButton(driverController, Xbox::B_button).WhenPressed(new MoveArm(false));

  // manipulator

  SimpleButton(manipulatorController, Xbox::X_button).WhileHeld(new LowerClimber);
  SimpleButton(manipulatorController, Xbox::Y_button).WhileHeld(new RaiseClimber);
  SimpleButton(manipulatorController, Xbox::B_button).WhileHeld(new NoSensorClimbRaise);
  SimpleButton(manipulatorController, Xbox::A_button).WhileHeld(new NoSensorClimbLower);

  // SimpleButton(manipulatorController, Xbox::X_button).WhenPressed(new ToggleArm);
  SimpleButton(manipulatorController, Xbox::lt_bumper).WhenPressed(new MoveArm(false));
  SimpleButton(manipulatorController, Xbox::rt_bumper).WhenPressed(new MoveArm(true));
  SimplePOV(manipulatorController, XboxPOV::up).WhenPressed(new PivotToggle);
}

std::pair<double, double> OI::GetDriveControls()
{
  double speed = driverController->GetLeftY();
  double rotation = driverController->GetRightX() * -1;
  double multiplier = GetDriveSpeedMultiplier();
  return std::make_pair(speed * multiplier, rotation * multiplier);
}

double OI::GetDriveSpeedMultiplier()
{
  double speedMultiplier = frc::SmartDashboard::GetNumber("Drive Speed:", 1.0);
  return CheckAndLimitValue(speedMultiplier);
}

void OI::SetControllerRumble(frc::XboxController *controller, double value, bool lightly)
{
  if (lightly)
    controller->SetRumble(frc::GenericHID::RumbleType::kRightRumble, value);
  else
    controller->SetRumble(frc::GenericHID::RumbleType::kLeftRumble, value);
}

double OI::CheckAndLimitValue(double value, double upperLimit, double lowerLimit)
{
  if (value < lowerLimit)
    value = lowerLimit;
  else if (value > upperLimit)
    value = upperLimit;
  return value;
}

frc2::Button OI::SimpleButton(std::shared_ptr<frc::GenericHID> controller, int btn)
{
  return frc2::Button([this, controller, btn]
                      { return controller->GetRawButton(btn); });
}

frc2::Button OI::SimpleAxis(std::shared_ptr<frc::GenericHID> controller, int axis, double threshold)
{
  return frc2::Button([this, controller, axis, threshold]
                      { return controller->GetRawAxis(axis) > threshold; });
}

frc2::Button OI::SimplePOV(std::shared_ptr<frc::GenericHID> controller, int degs)
{
  return frc2::Button([this, controller, degs]
                      { return (controller->GetPOV(degs) == degs); });
}