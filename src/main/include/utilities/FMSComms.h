/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights UnReserved.                           */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>
#include <frc/DriverStation.h>

class FMSComms {
public:

  FMSComms();
  char GetGameData();
  frc::DriverStation::Alliance GetAlliance();
  std::string GetAllianceString(frc::DriverStation::Alliance);
  void GetGameDataRequirements();
  double DisplayMatchTime();
  frc::DriverStation::Alliance alliance;

};