#include "datelib.h"
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<int, int> century_code = {
    {1800, 2}, {1900, 1}, {2000, 0}, {2100, 0}};

vector<int> greg_month_count = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

unordered_map<int, int> greg_century_code = {{1700, 4}, {1800, 2}, {1900, 0},
                                             {2000, 6}, {2100, 4}, {2200, 2},
                                             {2300, 0}};

vector<int> greg_month_code = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};

int calc_days_passed_greg(int month, int year) {
  const int day = 1;
  int days_passed = 0;
  vector<int> month_count = greg_month_count;
  month_count[1] += isGregLeapYear(year);
  int century_id;
  int ethiopianNewYearDay;
  if (month <= 9) {
    ethiopianNewYearDay = (year - 8) % 4 == 0 ? 12 : 11;
  } else {
    ethiopianNewYearDay = (year - 7) % 4 == 0 ? 12 : 11;
  }

  if (month > 9) {
    century_id = ceil(float(year + 1) / 100) * 100;
    days_passed += day - ethiopianNewYearDay + month_count[8];
    for (int i = 9; i < month - 1; i++) {
      days_passed += month_count[i];
    }
    days_passed += day;
  } else {
    century_id = ceil(float(year) / 100) * 100;
    for (int i = 8; i < 12; i++) {
      days_passed += month_count[i];
    }
    days_passed += greg_month_count[8] - ethiopianNewYearDay + day;
    for (int i = 0; i < month - 1; i++) {
      days_passed += month_count[i];
    }
    days_passed += day - 30;
  }

  int offset = century_code[century_id];
  return days_passed + offset;
}

int calc_days_passed_jul(int month, int year) {
  const int day = 1;
  int days_passed = 0;
  vector<int> month_count = greg_month_count;
  month_count[1] += isJulianLeapYear(year);

  int ethiopianNewYearDay;
  if (month <= 8) {
    ethiopianNewYearDay = (year - 8) % 4 == 0 ? 30 : 29;
  } else {
    ethiopianNewYearDay = (year - 7) % 4 == 0 ? 30 : 29;
  }

  if (month > 8) {
    days_passed += day - ethiopianNewYearDay + month_count[7];
    for (int i = 8; i < month - 1; i++) {
      days_passed += month_count[i];
    }
    days_passed += day;
  } else {
    for (int i = 7; i < 12; i++) {
      days_passed += month_count[i];
    }
    days_passed += greg_month_count[7] - ethiopianNewYearDay + day;
    for (int i = 0; i < month - 1; i++) {
      days_passed += month_count[i];
    }
    // days_passed += day - 30;
    days_passed -= 30;
  }
  return days_passed + 1 * ((year < 4) || (month <= 8 && year == 4));
}

int calc_days_passed(int month, int year) {
  if (year < 1752 || (year == 1752 && month <= 9)) {

    return calc_days_passed_jul(month, year);
  }
  return calc_days_passed_greg(month, year);
}

int get_leap_year_code(int month, int year) {
  // returns a leap year code for basic start day calculation
  if ((isGregLeapYear(year) || isJulianLeapYear(year)) && month <= 2)
    return 1;
  else
    return 0;
}

int isGregLeapYear(int year) {
  // checks if the date is Gregorean Leap Year
  if (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && (year > 1752))
    return 1;
  else
    return 0;
}

int isJulianLeapYear(int year) {
  // checks if the date is a Julian Leap Year
  if (year % 4 == 0 && year != 4 && year <= 1752)
    return 1;
  return 0;
}

int ethMaxDays(int month, int year) {
  // returns maximum ethiopian date 365 || 366
  year += 1;
  if (year < 1752 || (year == 1752 && month <= 8)) {
    if (month <= 8)
      return 365 + int((year - 8) % 4 == 0);
    else
      return 365 + int((year - 7) % 4 == 0);
  } else {
    if (month <= 9)
      return 365 + int((year - 8) % 4 == 0);
    else {
      return 365 + int((year - 7) % 4 == 0);
    }
  }
}
