#include "dns_manager.h"
#include "ui.h"
#include "utils.h"

void ToggleDNS() {
    std::string interfaceName = GetActiveInterface();

    if (interfaceName.empty()) {
        PrintWithColor("No active interface found.\n", RED);
        return;
    }

    std::string cmd = "netsh interface ipv4 set dns \"" + interfaceName + "\" static 1.1.1.1";
    int result = system(cmd.c_str());

    if (result == 0)
        PrintSuccess("DNS set to 1.1.1.1 for " + interfaceName);
    else
        PrintError("Failed to set DNS.");
}

void ResetDNS() {
    std::string interfaceName = GetActiveInterface();

    if (interfaceName.empty()) {
        PrintWithColor("No active interface found.\n", RED);
        return;
    }

    std::string cmd = "netsh interface ipv4 set dns \"" + interfaceName + "\" dhcp";
    int result = system(cmd.c_str());

    if (result == 0)
        PrintSuccess("DNS reset to DHCP for " + interfaceName);
    else
        PrintError("Failed to reset DNS.");
}