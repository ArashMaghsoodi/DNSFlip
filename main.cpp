#include <iostream>
#include <conio.h>
#include "dns_profiles.hpp"
#include "interface_config.hpp"
#include "dns_commands.hpp"
#include "utils.hpp"

// Windows color codes
#define COLOR_RESET   "\033[0m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_BWHITE  "\033[97m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_RED     "\033[31m"

int main() {
    loadProfiles();          // loads or creates dns_profiles.json
    loadInterfaces();        // loads or creates interface.json

    while (true) {
        clearScreen();

        std::cout << COLOR_CYAN << "=== DNSFlip ===\n" << COLOR_RESET;

        std::cout << COLOR_GREEN << "1." << COLOR_BWHITE << " Connect DNS (" << COLOR_YELLOW << getSelectedProfileName() << COLOR_BWHITE << ")\n";
        std::cout << COLOR_GREEN << "2." << COLOR_BWHITE << " Manage DNS IPs\n";
        std::cout << COLOR_GREEN << "3." << COLOR_BWHITE << " Manage Network Interface (" << COLOR_YELLOW << getSelectedInterfaceName() << COLOR_BWHITE << ")\n";
        std::cout << COLOR_GREEN << "4." << COLOR_BWHITE << " Reset to Automatic DNS\n";
        std::cout << COLOR_RED << "0." << COLOR_BWHITE << " Exit\n" << COLOR_RESET;
        std::cout << "Choice: ";

        char ch = _getch();
        std::cout << ch << "\n"; // Echo the pressed key
        int choice = ch - '0';

        switch (choice) {
            case 1:
                applySelectedDNS();
                pauseAndContinue();
                break;
            case 2:
                manageDNSProfiles();
                break;
            case 3:
                manageInterfaces();
                break;
            case 4:
                resetDNS();
                pauseAndContinue();
                break;
            case 0:
                return 0;
            default:
                std::cout << "Invalid choice.\n";
                pauseAndContinue();
        }
    }
}