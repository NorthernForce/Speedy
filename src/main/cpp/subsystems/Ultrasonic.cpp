#include "subsystems/Ultrasonic.h"
#include "Constants.h"
#include <frc/RobotController.h>
#include <memory>


Ultrasonic::Ultrasonic() 
{
   m_ultrasonic = std::make_shared<frc::AnalogInput>(Constants::kUltrasonicPort);
  
}

Ultrasonic::~Ultrasonic() 
{
  
}


// This method will be called once per scheduler run
void Ultrasonic::Periodic() 
{
   m_dist = calcDistance();
}

double Ultrasonic::getDistance( )
{
    return m_dist;
}

double Ultrasonic::calcDistance()
{
    m_rawVal = m_ultrasonic->GetValue();
    double scaleFactor = 5 / frc::RobotController::GetVoltage5V();
    return (m_rawVal * scaleFactor * 0.0492) ;

}


