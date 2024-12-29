#pragma once
#include <cwchar>
#include <string>
#include <unordered_map>
#include <vector>

extern std::unordered_map<int, int> century_code;

extern std::vector<int> greg_month_count;
extern std::string eth_months[];
extern int eth_months_count[];
extern std::string greg_months[];
extern std::unordered_map<int, int> greg_century_code;

extern std::vector<int> greg_month_code;

void print_header(int, int, int, int);
int calc_days_passed_greg(int, int);
int calc_days_passed_jul(int, int);

void print(int, int);
std::vector<std::vector<int>> con_matirx(int, int);

int get_leap_year_code(int, int);
int isJulianLeapYear(int);
int isGregLeapYear(int);

int calc_days_passed(int, int);
int ethMaxDays(int, int);

struct Cell {

  std::string gregVal = "     |";
  std::string ethVal = "     |";

  void set_greg_val(int num) {
    int i = 4;
    while (num > 0) {
      gregVal[i] = char(num % 10 + '0');
      i -= 1;
      num /= 10;
    }
  }
  void set_eth_val(int num, int max) {
    if (num > max)
      num -= max;
    if (num > 360)
      num -= 360;
    num %= 30;
    if (num == 0)
      num = 30;
    int i = int(log10(num));
    while (num > 0) {
      ethVal[i] = char(num % 10 + '0');
      i -= 1;
      num /= 10;
    }
  }
};
