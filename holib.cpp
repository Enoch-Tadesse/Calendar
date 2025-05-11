#include "datelib.h"
#include <cmath>
#include <map>
#include <string>

typedef std::map<std::vector<int>, std::string> holiday;

holiday eth_holi = {

    {{1, 1}, "Enkutatash"},
    {{1, 17}, "Meskel"},
    {{4, 119}, "Gena"},
    {{5, 131}, "Timket"},
    {{6, 173}, "Adwa Victory Day"},
    {{8, 233}, "Labour's Day"},
    {{8, 237}, "Veteran's Day"},
    {{9, 241}, "The Navity of Virgin Mary"},
    {{9, 290}, "Derg Downfall Day"},
}; // the Ethiopian Holidays month with corresponding day since the new year

holiday specialHoliDates(int year) {
  holiday corrected = eth_holi;
  std::map<int, int> tewsak_relation = {{0, 6}, {1, 5}, {2, 4}, {3, 3},
                                        {4, 2}, {5, 8}, {6, 7}};
  year -= 8; // to convert the gregorean year into Ethiopian year
  int month, day;
  int BC = year + 5500;
  int wengelawi = BC % 4;           // mathew, marqos, lucas, yohannes
  int meskerem = (BC / 4 + BC) % 7; // the day of meskerem
  int wenber = (BC % 19) - 1;
  int abekte = (wenber * 11) % 30;
  int metqe = (wenber * 19) % 30;

  if (metqe > 14)
    month = 1; // nenewe is in meskerem
  else
    month = 2;                                            // nenewe is in tikimt
  int tewsak = (meskerem + (month - 1) * 30 + metqe) % 7; // means additon
  int nenewe =
      (metqe + tewsak_relation[tewsak] + 1) % 30; // the nenewe fasting day
  day = (month + 5 - 1) * 30 + nenewe;            // day of nenewe

  corrected.insert({{(day - 1) / 30 + 1, day}, "Nenewe Tsom"});
  corrected.insert({{(day + 69 - 1) / 30 + 1, day + 69}, "Tinsae"});
  corrected.insert({{(day + 67 - 1) / 30 + 1, day + 67}, "Seqlet"});
  corrected.insert({{(day + 14 - 1) / 30 + 1, day + 14}, "Abiy Tsom"});
  corrected.insert({{(day + 119 - 1) / 30 + 1, day + 119}, "Yehawaryat Tsom"});
  corrected.insert({{(day + 41 - 1) / 30 + 1, day + 41}, "Debre Zeyt"});
  corrected.insert({{(day + 62 - 1) / 30 + 1, day + 62}, "Hosana"});
  return corrected;
}

std::vector<std::string> get_eth_holidays(int month, int year,
                                          int days_passed) {
  std::vector<std::string> collections;
  int mod = ethMaxDays(month, year); // gets the max length of this year
  holiday corr_eth_holi =
      specialHoliDates(year); // corrects and add special holidays

  int upper_limit = (days_passed + greg_month_count[month - 1]) %
                    mod; // upper limit of the month to be printed
  int lower_limit = (upper_limit - greg_month_count[month - 1]) %
                    mod; // lower limi tof the month to be printed

  for (auto &day : corr_eth_holi) {
    bool offset = (day.second == "Gena" && (year - 7) % 4 == 0) ? true : false;
    // considers leap year for Gena or Christmas
    int corr_day = day.first[1] - offset; // corrects the day
    if ((corr_day % mod < upper_limit && corr_day % mod >= lower_limit) ||
        (corr_day < upper_limit && corr_day >= lower_limit)) {
      /*cheks if any of the holidays fall into the current month being printed
       */
      int bin_day = corr_day % mod;
      bin_day =
          bin_day - ((bin_day - 1) / 30) * 30; // gets the correct ethiopian day
      std::string send = day.second + " : " + greg_months[month - 1] + " " +
                         std::to_string((corr_day - lower_limit + 1) % mod) +
                         " / " + eth_months[day.first[0] - 1] + " " +
                         std::to_string(bin_day);
      collections.push_back(send);
    }
  }
  return collections;
}
