#include <iostream>
#include "ui.h"
#include "utils.h"
#include "dns_manager.h"

int main() {
    SetConsoleEncodingUTF8();
    ClearScreen();

    PrintHeader();

    while (true) {
        PrintMenu();
        char choice = GetSingleKey();

        switch (choice) {
            case '1':
                ToggleDNS();
                break;
            case '2':
                ResetDNS();
                break;
            case '0':
                PrintWithColor("Exiting...\n", YELLOW);
                return 0;
            default:
                PrintWithColor("Invalid option!\n", RED);
                break;
        }

        PauseAndClear();
    }

    return 0;
}