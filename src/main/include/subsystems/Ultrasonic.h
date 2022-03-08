
#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/AnalogInput.h>

#include "Constants.h"


class Ultrasonic : public frc2::SubsystemBase {
 public:
  Ultrasonic();
  ~Ultrasonic();

  void Periodic();

  double getDistance();

 private:
    std::shared_ptr<frc::AnalogInput> m_ultrasonic;
    double m_dist;
    double m_rawVal;

    double calcDistance();

    
};
