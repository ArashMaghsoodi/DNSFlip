#include "dns_commands.hpp"
#include "interface_config.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

void setDNS(const std::string& interface, const std::string& primary, const std::string& secondary) {

    std::string cmd1 = "netsh interface ip set dns name=\"" + interface + "\" static " + primary + " primary";
    int result1 = system(cmd1.c_str());
    if (result1 != 0) {
        std::cout << "Failed to set primary DNS. Make sure to run as administrator.\n";
        return;
    }

    if (!secondary.empty()) {
        std::string cmd2 = "netsh interface ip add dns name=\"" + interface + "\" " + secondary + " index=2";
        int result2 = system(cmd2.c_str());
        if (result2 != 0) {
            std::cout << "Failed to set secondary DNS.\n";
        }
    }
    std::cout << "DNS applied successfully.\n";
}

void resetDNS() {
    std::string interface = getSelectedInterfaceName();
    if (interface == "None") {
        std::cout << "No network interface selected.\n";
        return;
    }
    std::string cmd = "netsh interface ip set dns name=\"" + interface + "\" dhcp";
    int result = system(cmd.c_str());
    if (result != 0) {
        std::cout << "Failed to reset DNS. Make sure to run as administrator.\n";
    } else {
        std::cout << "DNS reset to automatic (DHCP) for interface: " << interface << "\n";
    }
}