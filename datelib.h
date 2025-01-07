#pragma once
#include <cwchar>
#include <iostream>
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
int get_jul_exception_offset(int, int);
int get_century_offset(int);

struct Cell {

  char gregVal[7] = {' ', ' ', ' ', ' ', ' ', '|', '\0'};
  char ethVal[7] = {' ', ' ', ' ', ' ', ' ', '|', '\0'};
  void set_greg_val(int num) {
    int i = 4;
    while (num > 0) {
      gregVal[i] = char(num % 10 + '0');
      i -= 1;
      num /= 10;
    }
  }
  void set_eth_val(int num, int max) {
    if (num <= 0) // to handle month that start within pagumen
      num += max % 100;
    if (num > max) // if it gets into meskerem
      num -= max;
    if (num > 360) // if it gets to pagumen
      num -= 360;
    num %= 30;    // limits it to a month count of 30
    if (num == 0) // if it's the last day of the month
      num = 30;
    int i = int(log10(num)); // gets the digit length
    while (num > 0) {
      ethVal[i] = char(num % 10 + '0');
      i -= 1;
      num /= 10;
    }
  }
};
