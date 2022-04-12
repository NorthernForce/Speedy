#include "utilities/TXTInterface.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>


TXTInterface::TXTInterface() {}

void TXTInterface::WriteTextFile(std::vector<double> doubleList, std::string fileName) {

	std::ofstream myfile("/home/lvuser/" + fileName + ".txt", std::ios::out);
	if (myfile.is_open())
	{
		for (size_t count = 0; count < doubleList.size(); count++) {
			myfile << doubleList[count] << ",";
		}
		myfile.close();
	}
	else std::cout << "Unable to open file";
}

std::vector<double> TXTInterface::ReadTextFile(std::string fileName){
	
    std::ifstream input_file("/home/lvuser/" + fileName + ".txt", std::ios::in);

    std::vector<double> doubleList;

    std::string line{};

    //input_file.open();
	if (input_file.is_open()) {

    while(std::getline(input_file, line)) {
        std::istringstream iss(line);

        std::string substring{};
        
        while (std::getline(iss, substring, ',')) {

            // Add the substring to the std::vector
            doubleList.push_back(strtod(substring.c_str(), NULL));
        }
    }
    }

    return doubleList;
    
}