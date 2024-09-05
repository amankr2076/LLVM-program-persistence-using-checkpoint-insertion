#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // For exit()

// Simulated function to get battery percentage
// In a real scenario, this would involve reading from /sys/class/power_supply/... or similar
int getBatteryLevel() {
    // return 900;
    std::ifstream batteryFile("/sys/class/power_supply/BAT0/capacity");
    if (batteryFile.is_open()) {
        std::string line;
        if (std::getline(batteryFile, line)) {
            try {
                int batteryLevel = std::stoi(line);
                return batteryLevel;
            } catch (const std::invalid_argument& ex) {
                std::cerr << "Error converting battery level to integer.\n";
            }
        }
    } else {
        std::cerr << "Error opening battery level file.\n";
    }
    // Return a default value if reading fails
    return -1;
}

void saveCheckpoint(const char* functionName, int batteryLevel,int blockID) {
    std::ofstream outFile("program_state.txt", std::ios::trunc); // Open in append mode
    if (outFile) {
        outFile << "Checkpoint reached in function: " << functionName << " at battery level " << batteryLevel << "%.\n";
        std::cout << "Checkpoint saved for " << functionName <<" with starting basic block ID " <<blockID<<" at battery level " << batteryLevel << "%.\n";
        outFile.close();

    } else {
        std::cerr << "Error opening program_state.txt for writing.\n";
    }
}

#include <cstring> // For strcmp()

extern "C"
void perform_checkpoint(const char* functionName, int blockID) {
    int batteryLevel = getBatteryLevel();
    if (batteryLevel < 30) {
        saveCheckpoint(functionName, batteryLevel, blockID);
        std::cerr << "Battery level is below 30%. Exiting program.\n";
        if (std::strcmp(functionName, "main") != 0) {
            std::cout << "Program terminated abruptly due to low battery.\n";
        } 
        exit(EXIT_FAILURE); // Exit the program
    } else {
        saveCheckpoint(functionName, batteryLevel, blockID);
        if (std::strcmp(functionName, "main") == 0) {
            std::cout << "Program successfully executed.\n";
        } 
            
        
    }
}
