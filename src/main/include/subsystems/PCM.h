/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Compressor.h>

class PCM : public frc2::SubsystemBase {
 public:
  PCM();
  void Periodic();

 private:
  std::shared_ptr<frc::Compressor> compressor;
  units::pounds_per_square_inch_t pressure_read;
};