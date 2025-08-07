#pragma once
#include <iostream>

inline void clearScreen() {
    system("cls"); // for Windows
}

inline void pauseAndContinue() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}