#include "utilities/RecordedTalonFX.h"
#include <chrono>
#include <sys/time.h>
#include <ctime>
#include "Constants.h"
    
RecordedTalonFX::RecordedTalonFX(int id) 
 :  BaseMotorController(id, device),
    BaseTalon(id, device),
    TalonFX(id),
    WPI_BaseMotorController(id, device),
    WPI_TalonFX(id),
    AutoRecorder(),
    id(id)
{}

void RecordedTalonFX::Set(double value) {
    WPI_TalonFX::Set(value);

    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    auto val = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
    long time = val.count();

    AutoRecorder::Write({
        std::to_string(id),
        std::to_string(WPI_TalonFX::GetSensorCollection().GetIntegratedSensorPosition()),
        std::to_string(time),
        std::to_string(WPI_TalonFX::Get())
    });
}