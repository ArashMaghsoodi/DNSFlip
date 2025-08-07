#include "interface_config.hpp"
#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <conio.h> // Add this at the top with other includes

static std::string selectedInterfaceName = "None";
const std::string INTERFACE_FILE = "interface.json";

// Helper to trim whitespace
static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

// List interfaces using ipconfig and parse output
static std::vector<std::string> listInterfaces() {
    std::vector<std::string> interfaces;
    FILE* pipe = _popen("ipconfig /all", "r");
    if (!pipe) return interfaces;

    char buffer[256];
    std::string currentLine;
    while (fgets(buffer, sizeof(buffer), pipe)) {
        currentLine = buffer;
        // Look for lines like "Ethernet adapter Ethernet:"
        auto pos = currentLine.find("adapter ");
        if (pos != std::string::npos) {
            auto colon = currentLine.find(':', pos);
            if (colon != std::string::npos) {
                std::string name = trim(currentLine.substr(pos + 8, colon - (pos + 8)));
                interfaces.push_back(name);
            }
        }
    }
    _pclose(pipe);
    return interfaces;
}

void loadInterfaces() {
    std::ifstream in(INTERFACE_FILE);
    if (in) {
        std::getline(in, selectedInterfaceName);
        selectedInterfaceName = trim(selectedInterfaceName);
        if (selectedInterfaceName.empty()) selectedInterfaceName = "None";
    }
}

std::string getSelectedInterfaceName() {
    return selectedInterfaceName;
}

void manageInterfaces() {
    while (true) {
        clearScreen();
        auto interfaces = listInterfaces();
        if (interfaces.empty()) {
            std::cout << "No interfaces found.\n";
            return;
        }

        std::cout << "Available network interfaces:\n";
        for (size_t i = 0; i < interfaces.size(); ++i) {
            std::cout << i + 1 << ". " << interfaces[i];
            if (interfaces[i] == selectedInterfaceName) {
                std::cout << " [Active]";
            }
            std::cout << "\n";
        }
        std::cout << "Select interface (1-" << interfaces.size() << "), or 0 to return: ";
        char ch = _getch();
        std::cout << ch << "\n"; // Echo the pressed key
        size_t choice = ch - '0';
        if (choice == 0) {
            break;
        }
        if (choice < 1 || choice > interfaces.size()) {
            std::cout << "Invalid selection.\n";
            pauseAndContinue();
            continue;
        }
        selectedInterfaceName = interfaces[choice - 1];
        std::ofstream out(INTERFACE_FILE);
        out << selectedInterfaceName << "\n";
    }
}