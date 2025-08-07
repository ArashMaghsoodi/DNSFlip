#include <iostream>
#include <conio.h>
#include "dns_profiles.hpp"
#include "interface_config.hpp"
#include "dns_commands.hpp"
#include "utils.hpp"

int main() {
    loadProfiles();          // loads or creates dns_profiles.json
    loadInterfaces();        // loads or creates interface.json

    while (true) {
        clearScreen();

        std::cout << "=== DNSFlip ===\n";
        std::cout << "1. Connect DNS (" << getSelectedProfileName() << ")\n";
        std::cout << "2. Manage DNS IPs\n";
        std::cout << "3. Manage Network Interface (" << getSelectedInterfaceName() << ")\n";
        std::cout << "4. Reset to Automatic DNS\n";
        std::cout << "0. Exit\n";
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