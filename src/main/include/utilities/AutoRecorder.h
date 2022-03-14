#pragma once

#include "utilities/CSVInterface.h"
#include <memory>
#include <vector>

class AutoRecorder {
 public:
    AutoRecorder();
    void Write(std::vector<std::string> data);
    
 private:
    std::shared_ptr<CSVInterface> csvInterface;
};