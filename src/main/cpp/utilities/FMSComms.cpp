/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights UnReserved.                           */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DriverStation.h>
#include <math.h>
#include <utilities/FMSComms.h>
#include <iostream>

FMSComms::FMSComms(){
    if(frc::DriverStation::GetAlliance() != frc::DriverStation::kInvalid) {
        FMSComms::GetAlliance();
    }
}

frc::DriverStation::Alliance FMSComms::GetAlliance(){
    alliance = frc::DriverStation::GetAlliance();
    return alliance;
}


