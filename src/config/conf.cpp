#include <fstream>
#include <string>
#include "ConstantsGame.h"
#include "ConstantsEngine.h"

bool ACCEPT_ONLY_VERIFIED_FILES;
int MIN_MAX_DEPTH;
int KING_RANK;
int QUEEN_RANK;
int KNIGHT_RANK;
int ROCK_RANK;
int BISHOP_RANK;
int PAWN_RANK;

bool readFromConfigFileAndSetVariables() {
    int NUM_OF_VARIABLES_TO_READ = 8;
    // Open the config file for reading
    std::ifstream configFile("file.conf");
    if (!configFile.is_open()) {
        // The config file failed to open, so use default values
        return false;
    }

    // Read the config file and set the variables
    std::string line;
    int variablesReadSuccess = 0;
    while (std::getline(configFile, line)) {
        // Skip lines starting with "//"
        if (line.find("#") == 0) {
            continue;
        }

        try {
            if (line.find("MIN_MAX_DEPTH") != std::string::npos) {
                // Found the MIN_MAX_DEPTH variable in the config file
                int value = std::stoi(line.substr(line.find("=") + 1));
                MIN_MAX_DEPTH = value;
                variablesReadSuccess++;
            }
            else if (line.find("ACCEPT_ONLY_VERIFIED_FILE") != std::string::npos) {
                // Found the ACCEPT_ONLY_VERIFIED_FILE variable in the config file
                int value = std::stoi(line.substr(line.find("=") + 1));
                ACCEPT_ONLY_VERIFIED_FILES = ( (value == 1) ? true: false);
                variablesReadSuccess++;
            }
            else if (line.find("KING_RANK") != std::string::npos) {
                // Found the KING_RANK variable in the config file
                int value = std::stoi(line.substr(line.find("=") + 1));
                KING_RANK = value;
                variablesReadSuccess++;
            }
            else if (line.find("QUEEN_RANK") != std::string::npos) {
                // Found the QUEEN_RANK variable in the config file
                int value = std::stoi(line.substr(line.find("=") + 1));
                QUEEN_RANK = value;
                variablesReadSuccess++;
            }
            else if (line.find("KNIGHT_RANK") != std::string::npos) {
                // Found the KNIGHT_RANK variable in the config file
                int value = std::stoi(line.substr(line.find("=") + 1));
                KNIGHT_RANK = value;
                variablesReadSuccess++;
            }
            else if (line.find("ROCK_RANK") != std::string::npos) {
                // Found the ROCK_RANK variable in the config file
                int value = std::stoi(line.substr(line.find("=") + 1));
                ROCK_RANK = value;
                variablesReadSuccess++;
            }
            else if (line.find("BISHOP_RANK") != std::string::npos) {
                // Found the BISHOP_RANK variable in the config file
                int value = std::stoi(line.substr(line.find("=") + 1));
                BISHOP_RANK = value;
                variablesReadSuccess++;
            }
            else if (line.find("PAWN_RANK") != std::string::npos) {
                // Found the PAWN_RANK variable in the config file
                int value = std::stoi(line.substr(line.find("=") + 1));
                PAWN_RANK = value;
                variablesReadSuccess++;
            }
        } catch (const std::exception& e) {
            // Something went wrong during reading, so close the file and return false
            configFile.close();
            return false;
        }
    }

    // Close the config file and return true to indicate success
    configFile.close();
    return (NUM_OF_VARIABLES_TO_READ == variablesReadSuccess);
}


