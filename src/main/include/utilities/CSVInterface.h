#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <units/time.h>

class CSVInterface {
 public:
    CSVInterface(const std::string& filename);
    ~CSVInterface();
    bool WriteLine(std::string line);
    std::vector<std::string> ReadLine();
    units::millisecond_t GetLastTime();
    bool IsAtEndOfFile();
    std::vector<std::string> StringTokenizer(std::string stringOfStrings, std::string delim);
    std::string RemoveWhiteSpace(std::string str);

 private:
    bool endOfFile;
    std::string filename;
    std::ifstream fileRead;
    std::ofstream fileWrite;
    std::string expectedColumns = "ID,type,position,time,speed";
    std::string actualColumns;
    units::millisecond_t lastReadTime = -1_ms; //initialize to impossible value
};