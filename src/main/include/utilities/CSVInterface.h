#pragma once

#include <iostream>
#include <fstream>
#include <string>

class CSVInterface {
 public:
    CSVInterface(const std::string& filename);
    bool WriteLine(std::string line);

 private:
    std::ifstream fileRead;
    std::ofstream fileWrite;
    std::string expectedColumns = "CAN ID,position,speed,time";
    std::string actualColumns;
};