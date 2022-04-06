//////////////////////////////////////////////////////////////
// Ultrasonic Declarations
//
// This Class represents the Ultrsonic Sensor's Functionality.
//
// Jay Crosby
// March 8, 2022
//////////////////////////////////////////////////////////////

#include "subsystems/Ultrasonic.h"
#include "Constants.h"
#include <frc/RobotController.h>
#include <memory>
#include <frc/smartdashboard/SmartDashboard.h>

//Constructor
Ultrasonic::Ultrasonic() 
{
   m_ultrasonic = std::make_shared<frc::AnalogInput>(Constants::kUltrasonicPort); //Setup Ultrasonic Analog Port
  
}

//Destructor
Ultrasonic::~Ultrasonic() 
{
  
}


// Periodic Method: This method will be called once per scheduler run
//This value is saved in attribute m_dist
void Ultrasonic::Periodic() 
{
   m_dist = calcDistance();
//    frc::SmartDashboard::PutNumber("Ultrasonic: ", m_dist);
}

//Retuns the last Distance seen in Inches from m_dist
double Ultrasonic::getDistance( )
{
    return m_dist;
}

//Calaulates and Returns the Instantaneous Distance 
double Ultrasonic::calcDistance()
{
    m_rawVal = m_ultrasonic->GetValue();                            //Raw Value (0 - 4095)

    //Detemine the Scale Factor for 5V Voltage Variation
    double scaleFactor = k_Cvv / frc::RobotController::GetVoltage5V();  

    //Mtuliplies the Raw Value by the 5v Variable Facotr and the SCaling Factor for Volts to Inches
    //This returns the Distance in Inches
    return (m_rawVal * scaleFactor * k_VperInch) ;          

}


