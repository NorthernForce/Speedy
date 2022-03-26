#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class CSVInterface {
 public:
    CSVInterface(const std::string& filename);
    ~CSVInterface();
    bool WriteLine(std::string line);
    std::vector<std::string> ReadLine();
    bool IsInitialized();
    std::vector<std::string> StringTokenizer(std::string stringOfStrings, std::string delim);
    std::string RemoveWhiteSpace(std::string str);

 private:
    bool isInitialized;
    std::string filename;
    std::ifstream fileRead;
    std::ofstream fileWrite;
    std::string expectedColumns = "ID,type,position,time,speed";
    std::string actualColumns;
};