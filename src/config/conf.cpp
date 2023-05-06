#include <fstream>
#include <string>
#include "ConstantsGame.h"

bool ACCEPT_ONLY_VERIFIED_FILES;
int MIN_MAX_DEPTH;

void readFromConfigFileAndSetVariables() {
    // Open the config file for reading
    std::ifstream configFile("file.conf");
    if (!configFile.is_open()) {
        // The config file failed to open, so use default values
        return;
    }

    // Read the config file and set the variables
    std::string line;
    while (std::getline(configFile, line)) {
        // Skip lines starting with "//"
        if (line.find("//") == 0) {
            continue;
        }

        if (line.find("MIN_MAX_DEPTH") != std::string::npos) {
            // Found the MIN_MAX_DEPTH variable in the config file
            int value = std::stoi(line.substr(line.find("=") + 1));
            MIN_MAX_DEPTH = value;
        }
        else if (line.find("ACCEPT_ONLY_VERIFIED_FILES") != std::string::npos) {
            // Found the ACCEPT_ONLY_VERIFIED_FILES variable in the config file
            int value = std::stoi(line.substr(line.find("=") + 1));
            ACCEPT_ONLY_VERIFIED_FILES = (value != 0);
            //throw std::runtime_error(std::to_string(ACCEPT_ONLY_VERIFIED_FILES));
        }
    }

    // Close the config file
    configFile.close();
}
