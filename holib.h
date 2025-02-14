#pragma once

#include <map>
#include <string>
#include <vector>

extern std::map<int, std::string> eth_holi;

std::vector<std::string> get_eth_holidays(int, int, int);
