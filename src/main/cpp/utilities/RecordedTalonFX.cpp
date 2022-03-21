#include "utilities/RecordedTalonFX.h"
#include <chrono>
#include <sys/time.h>
#include <ctime>
#include "RobotContainer.h"
    
RecordedTalonFX::RecordedTalonFX(int id) 
 :  BaseMotorController(id, device),
    BaseTalon(id, device),
    TalonFX(id),
    WPI_BaseMotorController(id, device),
    WPI_TalonFX(id),
    id(id)
{
    RobotContainer::autoRecorder->AddDevice(this);
}

void RecordedTalonFX::LogData() {
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    auto val = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
    long time = val.count();

    RobotContainer::autoRecorder->Write({
        std::to_string(id),
        "TalonFX",
        std::to_string(WPI_TalonFX::GetSensorCollection().GetIntegratedSensorPosition()),
        std::to_string(time),
        std::to_string(WPI_TalonFX::Get())
    });
}

void RecordedTalonFX::Set(double value) {
    WPI_TalonFX::Set(value);
    //LogData();
}

// void RecordedTalonFX::Set(double speed) {
//     SpeedController::Set(speed);
//     LogData();
// }

void RecordedTalonFX::Set(TalonFXControlMode mode, double value) {
    WPI_TalonFX::Set(mode, value);
    LogData();
}