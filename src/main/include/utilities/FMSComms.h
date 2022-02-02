/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights UnReserved.                           */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>

class FMSComms {

  char GetGameData();
  void GetGameDataRequirements();
  std::string gameData;
  char desiredColor;

};