#pragma once
#include <string>

void setDNS(const std::string& interface, const std::string& primary, const std::string& secondary);
void resetDNS();