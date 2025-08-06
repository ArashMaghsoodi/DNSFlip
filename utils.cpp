#include "utils.h"
#include <cstdlib>
#include <windows.h>
#include <iostream>

std::string GetActiveInterface() {
    // NOTE: This is a placeholder. Replace with your actual logic.
    return "Wi-Fi";
}

void PauseAndClear() {
    system("pause > nul");
    system("cls");
}