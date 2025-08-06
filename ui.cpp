#include "ui.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

void SetConsoleEncodingUTF8() {
    SetConsoleOutputCP(CP_UTF8);
}

void ClearScreen() {
    system("cls");
}

void PrintWithColor(const std::string& text, ConsoleColor color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    std::cout << text;
    SetConsoleTextAttribute(hConsole, DEFAULT);
}

void PrintHeader() {
    PrintWithColor("=====================================\n", YELLOW);
    PrintWithColor("       DNS Toggle CLI Utility        \n", GREEN);
    PrintWithColor("=====================================\n", YELLOW);
}

void PrintMenu() {
    std::cout << "\nChoose an option:\n";
    PrintWithColor("[1] ", GREEN); std::cout << "Set DNS to 1.1.1.1\n";
    PrintWithColor("[2] ", YELLOW); std::cout << "Reset DNS to DHCP\n";
    PrintWithColor("[0] ", RED); std::cout << "Exit\n";
    PrintWithColor(">> ", DEFAULT);
}

void PrintSuccess(const std::string& message) {
    PrintWithColor("[✔] ", GREEN);
    std::cout << message << "\n";
}

void PrintError(const std::string& message) {
    PrintWithColor("[✘] ", RED);
    std::cout << message << "\n";
}

char GetSingleKey() {
    return _getch();  // No need to press Enter
}