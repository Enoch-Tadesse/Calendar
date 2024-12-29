#include "datelib.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

string eth_months[] = {"Meskerem", "Tikimt",  "Hedar",    "Tahesas", "Tir",
                       "Yekatit",  "Megabit", "Miyaziya", "Genbot",  "Sene",
                       "Hamle",    "Nehase",  "Pagume"};
;
int eth_months_count[] = {30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 5};
string greg_months[] = {"January",   "February", "March",    "April",
                        "May",       "June",     "July",     "August",
                        "September", "October",  "November", "December"};
unordered_map<int, int> century_code = {
    {1800, 2}, {1900, 1}, {2000, 0}, {2100, 0}};

vector<int> greg_month_count = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

unordered_map<int, int> greg_century_code = {{1700, 4}, {1800, 2}, {1900, 0},
                                             {2000, 6}, {2100, 4}, {2200, 2},
                                             {2300, 0}};

vector<int> greg_month_code = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};

int calc_days_passed_greg(int month, int year) {
  /* calculates how many days passed since the ethiopian new year in gregorean
   * era and returns it*/
  const int day = 1;
  int days_passed = 0;
  vector<int> month_count = greg_month_count;
  month_count[1] += isGregLeapYear(year); // account february
  int century_id;
  int ethiopianNewYearDay;
  if (month <= 9) { // gets the day of ethiopian new year
    ethiopianNewYearDay = (year - 8) % 4 == 0 ? 12 : 11;
  } else {
    ethiopianNewYearDay = (year - 7) % 4 == 0 ? 12 : 11;
  }

  if (month > 9) {
    century_id =
        ceil(float(year + 1) / 100) * 100; // century transition handling
    days_passed += day - ethiopianNewYearDay + month_count[8];
    for (int i = 9; i < month - 1; i++) {
      days_passed += month_count[i];
    }
    days_passed += day;
  } else {
    /*if month is above below and equal to september, add days from past year
     * too
     */
    century_id = ceil(float(year) / 100) * 100; // century transition handling
    for (int i = 8; i < 12; i++) {
      days_passed += month_count[i];
    } // past year addition
    days_passed += greg_month_count[8] - ethiopianNewYearDay + day;
    for (int i = 0; i < month - 1; i++) {
      days_passed += month_count[i];
    } // current year addition
    days_passed += day - 30;
  }

  int offset = century_code[century_id];
  return days_passed + offset; // consider the offsets
}

int calc_days_passed_jul(int month, int year) {
  /* calculates and returns days passed since ethiopian new year in julian era
   */
  const int day = 1;
  int days_passed = 0;
  vector<int> month_count = greg_month_count;
  month_count[1] += isJulianLeapYear(year); // account february

  int ethiopianNewYearDay;
  if (month <= 8) {
    ethiopianNewYearDay = (year - 8) % 4 == 0 ? 30 : 29;
  } else {
    ethiopianNewYearDay = (year - 7) % 4 == 0 ? 30 : 29;
  } // get the day of the ethiopian new year

  if (month > 8) {
    days_passed += day - ethiopianNewYearDay + month_count[7];
    for (int i = 8; i < month - 1; i++) {
      days_passed += month_count[i];
    }
    days_passed += day;
  } else {
    /* to consider countin from past year since the date is below Ethiopian new
     * year */
    for (int i = 7; i < 12; i++) {
      days_passed += month_count[i];
    }
    days_passed += greg_month_count[7] - ethiopianNewYearDay + day;
    for (int i = 0; i < month - 1; i++) {
      days_passed += month_count[i];
    } // counting current year days
    days_passed -= 30;
  }
  return days_passed + 1 * ((year < 4) || (month <= 8 && year == 4));
}

int calc_days_passed(int month, int year) {
  /* returns the days passed since Ethiopian new year based of Julian and
   * Gregorean era. */
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
  // returns maximum ethiopian date 365 || 366 of that current year
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

void print_header(int year, int month, int eth_passed, int max_eth) {
  /* prints header for Gregorean year and Ethiopian year
   * also Gregorean months and Ethiopian months */

  cout << "Gregorean Year: " << year << "\t";
  if ((month == 9 && year > 1752) || (month == 8 && year <= 1752)) {
    cout << "Ethiopian Year: " << year - 8 << " - " << year - 7 << endl;
  } else {
    cout << "Ethiopian Year: "
         << year - 7 -
                1 * ((month < 9 && year > 1752) || (month < 8 && year >= 1752))
         << endl;
    ;
  }

  cout << greg_months[month - 1] << "\t";
  int start = floor(eth_passed / 30);
  eth_months_count[12] = max_eth % 360;
  eth_months_count[start % 13] -= eth_passed % 30;
  int days_greg =
      greg_month_count[month - 1] +
      (month == 2 && (isGregLeapYear(year) || isJulianLeapYear(year)));
  if (eth_passed % 30 == 0)
    cout << eth_months[start - 1] << "-";
  while (days_greg > 0) {
    start %= 13;
    days_greg -= eth_months_count[start];
    if (days_greg > 0)
      cout << eth_months[start] << "-";
    else
      cout << eth_months[start] << '\t';

    start++;
  }
  cout << endl;
}

vector<vector<int>> con_matirx(int month, int year) {
  /* returns a matrix of gregorean days using columns as
   * days of the week and mat[r][c] as the value */
  int century_code;
  if (year < 1752 || (month <= 9 && year == 1752)) {
    century_code = (18 - year / 100) % 7;
  } else {
    century_code = greg_century_code[year / 100 * 100];
  }

  int year_code = ((year % 100) + (year % 100) / 4) % 7;
  int leap_year_code =
      get_leap_year_code(month, year); // check if it is a leap year
  int start_day =
      (year_code + greg_month_code[month - 1] + century_code + 1 -
       leap_year_code + 1 * (year < 4)) %
      7; // gets the starting day of the week of the first day of the month

  int rows;
  int cols = 7;
  int days = greg_month_count[month - 1] +
             (isGregLeapYear(year) + leap_year_code * (year <= 1752)) *
                 (month - 1 == 1); // how many days to fill the matrix

  int remaining_days = days - (7 - start_day);
  rows = ceil((float)(remaining_days) / 7.0) +
         1; // calculates how many rows needed
  int offset = start_day;

  vector<int> single_row(cols,
                         0); // initializes a single row to all zero values
  if (!(month == 9 && year == 1752)) {
    /* if it is not the special transition date between
     * Julian and Gregorean */
    vector<vector<int>> mat(rows, single_row);
    for (int i = 0; i < days; i++) {
      mat[(offset + i) / cols][(offset + i) % cols] = i + 1;
    }
    return mat;
  }

  // this hald is for the special date sep, 1572
  int fillValues = 0;
  rows = ceil((float)(remaining_days - 11) / 7.0) + 1;
  vector<vector<int>> mat(rows, single_row);

  for (int i = 0; i < days; i++) {
    if (fillValues < greg_month_count[month - 1]) {
      mat[(offset + i) / cols][(offset + i) % cols] = fillValues + 1;
      fillValues += 1 + 11 * (i == 1);
    } else {
      break;
    }
  }
  return mat;
}

void print(int month, int year) {
  /* this function prints the whole body and is responsible
   * for the call of every other function */

  int ethDay = calc_days_passed(month, year);
  int ethMax = ethMaxDays(month, year);

  print_header(year, month, ethDay, ethMax);

  vector<vector<int>> mat = con_matirx(month, year);

  cout << "|-----------------------------------------|" << endl;
  cout << "|Sun  |Mon  |Tue  |Wed  |Thu  |Fri  |Sat  |" << endl;
  cout << "|-----------------------------------------|" << endl;

  for (int r = 0; r < mat.size(); r++) {

    cout << "|";
    Cell cell[7]; // intilializes 7 days of the week to print
    for (int c = 0; c < mat[r].size(); c++) {
      cell[c].set_greg_val(mat[r][c]); // fill the Gregorean days
      if (mat[r][c] != 0) {
        cell[c].set_eth_val(ethDay, ethMax); // fill the Ethiopian days
        ethDay++;
      }

      cout << cell[c].gregVal; // prints the gregorean half
    }
    cout << endl;

    cout << "|";
    for (int c = 0; c < mat[r].size(); c++) {
      cout << cell[c].ethVal; // prints the Ethiopian half
    }
    cout << endl;
    cout << "|-----------------------------------------|" << endl;
  }
}
