//////////////////////////////////////////////////////////////
// Ultrasonic Declarations
//
// This Class represents the Ultrsonic Sensor's Functionality.
//
// Jay Crosby
// March 8, 2022
//////////////////////////////////////////////////////////////

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/AnalogInput.h>

#include "Constants.h"

//Class Declaration
class Ultrasonic : public frc2::SubsystemBase {
 public:
  Ultrasonic();             //Constuctor
  ~Ultrasonic();            //Destructor

  void Periodic();          //Runs durng the Periodic Cycle

  double getDistance();     //Gets te Distance in Inches

 private:
    std::shared_ptr<frc::AnalogInput> m_ultrasonic;   //Analog Port that the Sensor is attached to 
    double m_dist;                                    //Sensed Distance in Inches
    double m_rawVal;                                  //Raw Value from theAnalog Port (0 - 4095)

    double calcDistance();                            //Applies Scaling and Conversion to return Distance 

    const double k_Cvv = 5.0;
    const double k_VperInch = 0.0492; 

    
};
