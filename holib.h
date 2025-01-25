#pragma once

#include <string>
#include <unordered_map>
#include <vector>

extern std::unordered_map<int, std::string> eth_holi;

std::vector<std::string> get_eth_holidays(int, int, int);
