#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

const extern std::vector<int> greg_month_count;
const extern std::string eth_months[];
const extern std::vector<int> eth_months_count;
const extern std::string greg_months[];

const extern std::vector<int> greg_month_code;

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
  int gregVal = 0;
  int ethVal = 0;
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
    ethVal = num;
  }
};
