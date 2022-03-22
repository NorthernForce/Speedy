#include "utilities/CSVInterface.h"

CSVInterface::CSVInterface(const std::string& filename) {
    isInitialized = false;
    fileRead.open(filename.c_str(), std::ios::in);
    fileRead.seekg(0);
    std::getline(fileRead, actualColumns);
    fileRead.close();

    fileWrite.open(filename.c_str(), std::ios::out | std::ios::app);
    if (actualColumns != expectedColumns) {
        WriteLine(expectedColumns);
    }
    isInitialized = true;
}

bool CSVInterface::IsInitialized() {
    return isInitialized;
}

// CAN ID, device, (encoder) position, timestamp, motor speed
bool CSVInterface::WriteLine(std::string line) {
    if (!fileWrite.is_open())
        return false;
    fileWrite << line << '\n';
    return fileWrite.good();
}