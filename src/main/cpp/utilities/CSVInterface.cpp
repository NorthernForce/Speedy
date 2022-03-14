#include "utilities/CSVInterface.h"

CSVInterface::CSVInterface(const std::string& filename) {
    file.open(filename.c_str(), std::ios::out);
    std::string expectedColumns = "CAN ID, position, speed, time";
    std::string actualColumns;
    std::getline(file, actualColumns);

    if (!(actualColumns == expectedColumns))
        WriteLine(expectedColumns);
    file.close();
    file.open(filename.c_str(), std::ios::out | std::ios::app);
}

// CAN ID, (encoder) position, timestamp, motor speed
bool CSVInterface::WriteLine(std::string line) {
    if (!file.is_open())
        return false;
    file << line << '\n';
    file.close();
    return file.good();
}