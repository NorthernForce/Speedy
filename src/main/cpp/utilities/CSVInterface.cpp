#include "utilities/CSVInterface.h"
#include <iostream>
#include <fstream>
#include <vector>

CSVInterface::CSVInterface() {}

void CSVInterface::WriteTextFile(std::vector<double> doubleList, std::string fileName) {

	std::ofstream myfile(fileName);
	if (myfile.is_open())
	{
		for (int count = 0; count < doubleList.size(); count++) {
			myfile << doubleList[count] << " ";
		}
		myfile.close();
	}
	else std::cout << "Unable to open file";
}

std::vector<double> CSVInterface::ReadTextFile(std::string fileName){
	
    std::vector<double> doubleList;

	int number;

	std::ifstream input_file(fileName);
	if (!input_file.is_open()) {
		std::cout << "Could not open the file - '" << fileName << "'" << '\n';

        while (input_file >> number) {
            doubleList.push_back(number);
        }

        for (int i = 0; i < doubleList.size(); i++) {
            std::cout << doubleList.at(i) << '\n';
        }
	
        std::cout << "\n";
        input_file.close();
    }   

    return doubleList;
    
}