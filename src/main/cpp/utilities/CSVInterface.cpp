#include "/home/hunter/git/Speedy-RapidReact2022/src/main/include/utilities/CSVInterface.h"

CSVInterface::CSVInterface(const std::string& filename) {
    fileRead.open(filename.c_str(), std::ios::in);
    fileRead.seekg(0);
    std::getline(fileRead, actualColumns);
    fileRead.close();

    fileWrite.open(filename.c_str(), std::ios::out | std::ios::app);
    if (actualColumns != expectedColumns) {
        WriteLine(expectedColumns);
    }
}

// CAN ID, (encoder) position, timestamp, motor speed
bool CSVInterface::WriteLine(std::string line) {
    if (!fileWrite.is_open())
        return false;
    fileWrite << line << '\n';
    return fileWrite.good();
}

int main() {
    CSVInterface interface("file.csv");
    interface.WriteLine("15,-3.6,74974287927349274924,-0.45");
    return 0;
}