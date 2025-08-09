#include "dns_profiles.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include "dns_commands.hpp" // for setDNS
#include "interface_config.hpp" // for getSelectedInterfaceName
#include "utils.hpp"
#include <conio.h> // Add this for _getch
#include <limits> // Add this at the top if not already present

using json = nlohmann::json;

static const std::string PROFILE_PATH = "dns_profiles.json";
static json profilesJson;

void saveProfiles() {
    std::ofstream file(PROFILE_PATH);
    file << profilesJson.dump(4);
}

void loadProfiles() {
    std::ifstream file(PROFILE_PATH);
    if (!file) {
        profilesJson = {
            { "selected", 0 },
            { "profiles", json::array({
                {
                    { "name", "OpenDNS" },
                    { "primary", "208.67.222.222" },
                    { "secondary", "208.67.220.220" }
                },
                {
                    { "name", "Google DNS" },
                    { "primary", "8.8.8.8" },
                    { "secondary", "8.8.4.4" }
                },
                {
                    { "name", "Cloudflare" },
                    { "primary", "1.1.1.1" },
                    { "secondary", "1.0.0.1" }
                }
            }) }
        };

        // Fill to 9 entries
        while (profilesJson["profiles"].size() < 9)
            profilesJson["profiles"].push_back({});
        saveProfiles();
    } else {
        file >> profilesJson;
    }
}

std::string getSelectedProfileName() {
    int selected = profilesJson["selected"];
    const auto& p = profilesJson["profiles"][selected];
    return p.contains("name") ? p["name"].get<std::string>() : "None";
}

void applySelectedDNS() {
    int sel = profilesJson["selected"];
    const auto& p = profilesJson["profiles"][sel];
    if (!p.contains("primary") || !p.contains("secondary")) {
        std::cout << "Selected profile has invalid data.\n";
        return;
    }

    std::string interface = getSelectedInterfaceName();
    setDNS(interface, p["primary"], p["secondary"]);
    std::cout << "DNS set to " << p["name"] << " for interface " << interface << ".\n";
}

// Add color macros if not already present
#ifndef COLOR_RESET
#define COLOR_RESET   "\033[0m"
#define COLOR_GREY    "\033[90m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_BWHITE  "\033[97m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_RED     "\033[31m"
#endif

void manageDNSProfiles() {
    while (true) {
        clearScreen();
        std::cout << COLOR_CYAN << "== Manage DNS Profiles ==\n" << COLOR_RESET;

        for (int i = 0; i < 9; ++i) {
            const auto& p = profilesJson["profiles"][i];
            std::cout << COLOR_GREEN << (i + 1) << "." << COLOR_RESET << " ";
            if (p.contains("name")) {
                std::cout << COLOR_BWHITE << p["name"].get<std::string>() << COLOR_GREY;
                if (i == profilesJson["selected"]) std::cout << COLOR_YELLOW << " [Active]" << COLOR_RESET;
                std::cout << "\n";
            } else {
                std::cout << "Empty\n";
            }
        }
        std::cout << COLOR_RED << "0." << COLOR_RESET << " Back\nChoice: ";

        char ch = _getch(); // Waits for a single key press
        std::cout << ch << "\n"; // Echo the pressed key
        int choice = ch - '0';

        if (choice == 0) break;
        if (choice < 1 || choice > 9) continue;

        int index = choice - 1;
        auto& profile = profilesJson["profiles"][index];

        if (!profile.contains("name")) {
            // Add new profile (still needs Enter for text fields)
            std::string name, primary, secondary;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << COLOR_CYAN << "Enter DNS profile name: " << COLOR_RESET;
            std::getline(std::cin, name);
            std::cout << COLOR_CYAN << "Enter primary DNS IP: " << COLOR_RESET;
            std::getline(std::cin, primary);
            std::cout << COLOR_CYAN << "Enter secondary DNS IP: " << COLOR_RESET;
            std::getline(std::cin, secondary);

            profile["name"] = name;
            profile["primary"] = primary;
            profile["secondary"] = secondary;

            profilesJson["selected"] = index;
            saveProfiles();
        } else {
            // Show secondary menu
            while (true) {
                clearScreen();
                std::cout << COLOR_CYAN << "Selected Profile: " << COLOR_BWHITE << profile["name"].get<std::string>() << COLOR_RESET << "\n";
                std::cout << COLOR_GREEN << "1." << COLOR_RESET << " Set as Active\n";
                std::cout << COLOR_GREEN << "2." << COLOR_RESET << " Edit DNS Entry\n";
                std::cout << COLOR_GREEN << "3." << COLOR_RESET << " Delete DNS Entry\n";
                std::cout << COLOR_RED << "0." << COLOR_RESET << " Back\nChoice: ";
                char subCh = _getch();
                std::cout << subCh << "\n";
                int subChoice = subCh - '0';

                if (subChoice == 0) break;
                if (subChoice == 1) {
                    profilesJson["selected"] = index;
                    saveProfiles();
                    break;
                }
                if (subChoice == 2) {
                    std::string input;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << COLOR_CYAN << "Enter new DNS name (or press Enter to keep current: " << COLOR_BWHITE << profile["name"] << COLOR_CYAN << "): " << COLOR_RESET;
                    std::getline(std::cin, input);
                    if (!input.empty()) profile["name"] = input;

                    std::cout << COLOR_CYAN << "Enter new primary DNS IP (or press Enter to keep current: " << COLOR_BWHITE << profile["primary"] << COLOR_CYAN << "): " << COLOR_RESET;
                    std::getline(std::cin, input);
                    if (!input.empty()) profile["primary"] = input;

                    std::cout << COLOR_CYAN << "Enter new secondary DNS IP (or press Enter to keep current: " << COLOR_BWHITE << profile["secondary"] << COLOR_CYAN << "): " << COLOR_RESET;
                    std::getline(std::cin, input);
                    if (!input.empty()) profile["secondary"] = input;

                    saveProfiles();
                    clearScreen();
                    std::cout << COLOR_GREEN << "Profile updated.\n" << COLOR_RESET;
                    std::cout << COLOR_CYAN << "Selected Profile: " << COLOR_BWHITE << profile["name"].get<std::string>() << COLOR_RESET << "\n";
                    std::cout << COLOR_GREEN << "1." << COLOR_RESET << " Set as Active\n";
                    std::cout << COLOR_GREEN << "2." << COLOR_RESET << " Edit DNS Entry\n";
                    std::cout << COLOR_GREEN << "3." << COLOR_RESET << " Delete DNS Entry\n";
                    std::cout << COLOR_RED << "0." << COLOR_RESET << " Back\n";
                    continue; // Show menu again
                }
                if (subChoice == 3) {
                    std::cout << COLOR_YELLOW << "Are you sure you want to delete this DNS profile? (y/n): " << COLOR_RESET;
                    std::string confirm;
                    std::getline(std::cin, confirm);
                    if (!confirm.empty() && (confirm[0] == 'y' || confirm[0] == 'Y')) {
                        bool wasSelected = (profilesJson["selected"] == index);
                        profile = nlohmann::json::object(); // Clear profile

                        // If deleted profile was selected, select first non-empty or 0
                        if (wasSelected) {
                            int newSel = 0;
                            bool found = false;
                            for (int i = 0; i < 9; ++i) {
                                if (profilesJson["profiles"][i].contains("name")) {
                                    newSel = i;
                                    found = true;
                                    break;
                                }
                            }
                            profilesJson["selected"] = found ? newSel : 0;
                        }
                        saveProfiles();
                        std::cout << COLOR_GREEN << "Profile deleted.\n" << COLOR_RESET;
                        break;
                    }
                }
            }
        }
    }
}