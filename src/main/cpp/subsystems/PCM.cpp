/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/PCM.h"
#include "Constants.h"
#include <memory>

PCM::PCM() {
    compressor = std::make_shared<frc::Compressor>(Constants::PCMCanBusID, frc::PneumaticsModuleType::REVPH);
    compressor->EnableDigital();
}

// This method will be called once per scheduler run
void PCM::Periodic() 
{
    pressure_read = compressor->GetPressure();
}