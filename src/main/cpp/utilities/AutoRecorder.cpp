#include "utilities/AutoRecorder.h"
#include "utilities/CSVInterface.h"

AutoRecorder::AutoRecorder() {
    csvInterface = std::make_shared<CSVInterface>("auto.csv");
}

// Format: CAN ID, (encoder) position, timestamp, motor speed
void AutoRecorder::Write(std::vector<std::string> data) {
    std::string buffer = "";
    for (auto dataPoint : data) {
        buffer += (dataPoint += std::to_string(','));
    }
    csvInterface->WriteLine(buffer);
}