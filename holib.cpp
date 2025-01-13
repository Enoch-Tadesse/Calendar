#include "datelib.h"
#include <string>
#include <unordered_map>
#include <vector>

typedef std::unordered_map<std::string, std::pair<int, int>> holiday;
holiday eth_holi = {{"Enkutatash", {1, 366}},
                    {"Meskel", {1, 382}},
                    {"Gena", {4, 119}},
                    {"Timket", {5, 131}},
                    {"Labour's Day", {7, 233}},
                    {"Veteran's Day", {7, 237}},
                    {"Adwa Victory Day", {5, 173}},
                    {"*Eid al-Fitr", {6, 202}},
                    {"Derg Downfall Day", {8, 260}},
                    {"*Eid al-Adha", {9, 270}},
                    {"*The Prophet's Birthday", {12, 360}}};

holiday specialHoliDates(int year) {
  holiday corrected = eth_holi;
  corrected["Gena"].second -= int((year - 7) % 3 == 0);
  return corrected;
}
std::vector<std::string> get_eth_holidays(int month, int year,
                                          int days_passed) {
  std::vector<std::string> collections;
  holiday corr_eth_holi = specialHoliDates(year);
  int upper_limit = (days_passed + greg_month_count[month - 1]);

  int lower_limit = upper_limit - greg_month_count[month - 1];

  for (auto day : corr_eth_holi) {
    if ((day.second.second % 365 <= upper_limit &&
         day.second.second % 365 >= lower_limit) ||
        (day.second.second <= upper_limit &&
         day.second.second >= lower_limit)) {
      int bin_day = day.second.second % 365;
      if (bin_day >= 360)
        bin_day -= 330;
      std::string send =
          day.first + " : " + greg_months[month - 1] + " " +
          std::to_string((day.second.second - lower_limit + 1) % 365) + " / " +
          eth_months[day.second.first - 1] + " " + std::to_string(bin_day);
      collections.push_back(send);
    }
  }
  return collections;
}
