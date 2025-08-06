#pragma once
#include <string>

enum ConsoleColor {
    RED = 12,
    GREEN = 10,
    YELLOW = 14,
    DEFAULT = 15
};

void SetConsoleEncodingUTF8();
void PrintWithColor(const std::string& text, ConsoleColor color);
void PrintHeader();
void PrintMenu();
void PrintSuccess(const std::string& message);
void PrintError(const std::string& message);
char GetSingleKey();
void ClearScreen();