#pragma once

#include <frc2/command/SubsystemBase.h>

#include "utilities/CSVInterface.h"
#include <memory>
#include <vector>
#include <variant>

#include "utilities/RecordedTalonFX.h"
#include "utilities/RecordedSpark.h"
#include "utilities/RecordedSolenoid.h"

class AutoRecorder : public frc2::SubsystemBase {
 public:
    AutoRecorder();
    void Start();
    void Stop();
    bool GetIsRecording();
    void Write(std::vector<std::string> data);
    void AddDevice(RecordedTalonFX* device);
    void AddDevice(RecordedSpark* device);
    void AddDevice(RecordedSolenoid* device);
    void Periodic() override;
    
 private:
    static std::shared_ptr<CSVInterface> csvInterface;
    static bool isRecording;

    std::vector<RecordedTalonFX*> recordedTalons;
    std::vector<RecordedSpark*> recordedSparks;
    std::vector<RecordedSolenoid*> recordedSolenoids;
};