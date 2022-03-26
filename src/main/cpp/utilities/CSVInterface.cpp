#include "utilities/CSVInterface.h"
#include <algorithm>
#include "frc/smartdashboard/SmartDashboard.h"

CSVInterface::CSVInterface(const std::string& filename)
 : filename(filename) {
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
    endOfFile = false;
}

CSVInterface::~CSVInterface() {
    fileWrite.close();
    fileRead.close();
}

bool CSVInterface::IsInitialized() {
    return isInitialized;
}

// ID, device, (encoder) position, timestamp, motor speed
bool CSVInterface::WriteLine(std::string line) {
    if (!fileWrite.is_open() && fileRead.is_open()) {
        fileRead.close();
        fileWrite.open(filename.c_str(), std::ios::out | std::ios::app);
    }
    fileWrite << line << '\n';
    return fileWrite.good();
}

std::vector<std::string> CSVInterface::ReadLine() {
    if (fileWrite.is_open() && !fileRead.is_open()) {
        fileWrite.close();
        fileRead.open(filename.c_str(), std::ios::in);
        fileRead.seekg(0);

        //read first line of columns, then disregard
        std::string data;
        std::getline(fileRead, data);
    }
    std::string line;
    std::getline(fileRead, line);
    frc::SmartDashboard::PutString("autoautoauto", line);
    printf("%s\n", line.c_str());

    std::vector<std::string> listOfStrings = StringTokenizer(line, ",");
    return listOfStrings;
}

bool CSVInterface::IsAtEndOfFile() {
    return endOfFile;
}

std::vector<std::string> CSVInterface::StringTokenizer(std::string stringOfstrings, std::string delim) {
    std::vector<std::string> tokens;
    stringOfstrings = RemoveWhiteSpace(stringOfstrings);

    size_t pos = 0;
    while ((pos = stringOfstrings.find(delim)) != std::string::npos) {
        tokens.push_back(stringOfstrings.substr(0, pos));
        stringOfstrings.erase(0, pos + delim.length());
    }
    tokens.push_back(stringOfstrings.substr(0, pos));
    return tokens;
}

std::string CSVInterface::RemoveWhiteSpace(std::string str) {
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
    return str;
}