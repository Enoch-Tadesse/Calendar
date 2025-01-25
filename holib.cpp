#include "datelib.h"
#include <string>
#include <unordered_map>
#include <vector>

typedef std::unordered_map<std::string, std::vector<int>> holiday;

holiday eth_holi = {
    {"Meskel", {1, 17, 0}},
    {"Enkutatash", {1, 1, 0}},
    {"Derg Downfall Day", {9, 290, 0}},
    {"Veteran's Day", {7, 237, 0}},
    {"Labour's Day", {7, 233, 0}},
    {"Adwa Victory Day", {5, 173, 0}},
    {"Timket", {5, 131, 0}},
    {"Gena", {4, 119, 0}},
};

holiday specialHoliDates(int year) {
  holiday corrected = eth_holi;
  corrected["Gena"][1] -= int((year - 7) % 4 == 0);
  return corrected;
}

std::vector<std::string> get_eth_holidays(int month, int year,
                                          int days_passed) {
  std::vector<std::string> collections;
  int mod = ethMaxDays(month, year);
  holiday corr_eth_holi = specialHoliDates(year);

  int upper_limit = (days_passed + greg_month_count[month - 1]) % mod;
  int lower_limit = (upper_limit - greg_month_count[month - 1]) % mod;

  for (auto day : corr_eth_holi) {
    if ((day.second[1] % mod < upper_limit &&
         day.second[1] % mod >= lower_limit) ||
        (day.second[1] < upper_limit && day.second[1] >= lower_limit)) {
      int bin_day = day.second[1] % mod;
      bin_day = bin_day - ((bin_day - 1) / 30) * 30;
      std::string send =
          day.first + " : " + greg_months[month - 1] + " " +
          std::to_string((day.second[1] - lower_limit + 1) % mod) + " / " +
          eth_months[day.second[0] - 1] + " " + std::to_string(bin_day);
      collections.push_back(send);
    }
  }
  return collections;
}
