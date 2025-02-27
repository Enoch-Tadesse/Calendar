#include "datelib.h"
#include "holib.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string eth_months[] = {
    "Meskerem", "Tikimt", "Hidar", "Tahsas", "Tir",    "Yekatit", "Meggabit",
    "Miyazya",  "Ginbot", "Sene",  "Hamle",  "Nehase", "Pagume"};
const vector<int> eth_months_count = {30, 30, 30, 30, 30, 30, 30,
                                      30, 30, 30, 30, 30, 5};
const string greg_months[] = {"January",   "February", "March",    "April",
                              "May",       "June",     "July",     "August",
                              "September", "October",  "November", "December"};
const vector<int> greg_month_count = {31, 28, 31, 30, 31, 30,
                                      31, 31, 30, 31, 30, 31};

const vector<int> greg_month_code = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};

int get_century_offset(int year) {
  // returns the century offset based on their century
  int century_num = ceil(float(year + 1) / 100) * 100;
  int min = 1800;
  int base = 2;
  for (int i = min; i < century_num; i += 100) {
    if (i % 400 != 0)
      base -= 1;
  }
  return base;
}

int calc_days_passed_greg(int month, int year) {
  /* calculates how many days passed since the ethiopian new year in gregorean
   * era and returns it*/
  const int day = 1;
  int days_passed = 0;

  if (month > 9) {
    int ethiopianNewYearDay = (year - 7) % 4 == 0 ? 12 : 11;
    days_passed += day - ethiopianNewYearDay;
    for (int i = 8; i < month - 1; i++) {
      days_passed += greg_month_count[i];
    }
    days_passed +=
        day + get_century_offset(year); // century transitioning handling

  } else {
    /*if month is above below and equal to september, add days from past
     * year too*/
    days_passed += calc_days_passed(13, year - 1); // past year addition

    vector<int> month_count = greg_month_count;
    month_count[1] += isGregLeapYear(year); // account february
    for (int i = 0; i < month - 1; i++) {
      days_passed += month_count[i];
    } // current year addition
  }
  return days_passed; // consider the offsets
}

int get_jul_exception_offset(int month, int year) {
  // handles the year 4 february exceptions
  return int((year < 4) || (month <= 8 && year == 4));
}
int calc_days_passed_jul(int month, int year) {
  // calculates and returns days passed since ethiopian new year in julian era

  const int day = 1;
  int days_passed = 0;

  if (month > 8) {
    /* if the date given is before the Ethiopian new year */
    int ethiopianNewYearDay = (year - 7) % 4 == 0 ? 30 : 29;
    days_passed += day - ethiopianNewYearDay;
    for (int i = 7; i < month - 1; i++) {
      days_passed += greg_month_count[i];
    }
    days_passed += day + get_jul_exception_offset(month, year);
  } else {
    /* to consider countin from past year since the date is below Ethiopian
     * new year */
    days_passed += calc_days_passed_jul(13, year - 1);

    vector<int> month_count = greg_month_count;
    month_count[1] += isJulianLeapYear(year); // account february
    for (int i = 0; i < month - 1; i++) {
      days_passed += month_count[i];
    } // counting current year days
  }
  return days_passed;
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
  if (year < 1752 || (year == 1752 && month <= 8)) {
    year += int(month > 8); /* checks the current ethiopian year
                               whether before or after new year*/
    return 365 + int((year - 8) % 4 == 3);
  }
  year += int(month > 9); // this also checks the current ethiopian year
  return 365 + int((year - 8) % 4 == 3);
}

void print_header(int year, int month, int eth_passed, int max_eth) {
  /* prints header for Gregorean year and Ethiopian year
   * also Gregorean months and Ethiopian months */

  cout << "Gregorean Year: " << setw(8) << left << year;
  cout << "\033[33m" << "Ethiopian Year: "; // give yellow color
  if ((month == 9 && year > 1752) || (month == 8 && year <= 1752)) {
    if (year - 8 <= 0) { // considering BC in Ethiopian year
      cout << abs(year - 8 - 1) << " BC - ";
    } else // considering AD in Ethiopian year
      cout << year - 8 << " - ";
    if (year - 7 <= 0) {
      cout << abs(year - 7 - 1) << " BC" << endl;
    } else
      cout << year - 7 << endl;

  } else { // if no year transition on the month
    int eq = year - 7 -
             1 * ((month < 9 && year > 1752) || (month < 8 && year >= 1752));
    if (eq > 0)
      cout << eq << endl;
    else
      cout << abs(eq - 1) << " BC" << endl;
  }

  cout << "\033[0m"; // resets the yellow color
  cout << setw(24) << left << greg_months[month - 1];
  cout << "\033[33m"; // re-inti yellow color for eth month
  /*calculate the Gregorean month duration considering special cases*/
  int days_greg =
      greg_month_count[month - 1] +
      (month == 2 && (isGregLeapYear(year) || isJulianLeapYear(year)));

  days_greg -= 11 * int(year == 1752 && month == 9);

  if (year == 8 && month == 8) {
    // manual adjustment for historical alignment
    eth_passed = 3;
    days_greg = 3;
  }

  int start = floor(eth_passed / 30); // determine the starting Ethiopian month

  vector<int> eth_months_count_cpy = eth_months_count;
  eth_months_count_cpy[12] = max_eth % 360;
  eth_months_count_cpy[start % 13] -= eth_passed % 30;

  if (eth_passed % 30 == 0) { // accounting "meskerem"
    if (start == 0) {         // counter Segmentation fault (core dumped) error
      cout << eth_months[0] << "-";
    } else {
      cout << eth_months[start - 1] << "-";
    }
  }
  if (eth_passed < 0)
    cout << eth_months[12] << "-"; // pagumen starting months
  while (days_greg > 1) {
    start %= 13; // to loop back the Ethiopian month index
    days_greg -= eth_months_count_cpy[start];
    if (days_greg > 1)
      cout << eth_months[start] << "-";
    else
      cout << eth_months[start] << '\t';

    start++;
  }
  cout << "\033[0m" << endl; // resets the color yelow for Eth month
}

vector<vector<int>> con_matrix(int month, int year) {
  /* returns a matrix of gregorean days using columns as
   * days of the week and mat[r][c] as the value */
  int century_code;
  if (year < 1752 || (month <= 9 && year == 1752)) {
    century_code = (18 - year / 100) % 7;
  } else {
    century_code = (6 - 2 * ((year / 100) % 4)) % 7;
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

  // this hald is for the special date sep, 1752
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

void print(int month, int year, int todayDay, int todayMonth) {
  /* this function prints the whole body and is responsible
   * for the call of every other function */

  int ethDay = calc_days_passed(month, year);
  int ethMax = ethMaxDays(month, year);
  print_header(year, month, ethDay, ethMax);

  vector<vector<int>> mat = con_matrix(month, year);

  cout << "|----------------------------------|" << endl;
  cout << "\033[31m" << "|" << "Sun |Mon |Tue |Wed |Thu |Fri |Sat |"
       << "\033[0m" << endl; // marks the color red
  cout << "|----------------------------------|" << endl;

  vector<string> holidays =
      year >= 1900 ? get_eth_holidays(month, year, ethDay) : vector<string>();
  // get holidays only when year is above 1900
  int holiday_counter = 0;
  for (int r = 0; r < mat.size(); r++) {

    cout << "|";
    Cell cell[7]; // intilializes 7 days of the week to print
    for (int c = 0; c < mat[r].size(); c++) {
      cell[c].gregVal = mat[r][c]; // fill the Gregorean days
      if (mat[r][c] != 0) {
        cell[c].set_eth_val(ethDay, ethMax);
        // fill the Ethiopian days
        ethDay++;
        if (cell[c].gregVal == todayDay && month == todayMonth)
          cout << "\033[48;5;24m" << setw(4) << right << cell[c].gregVal
               << "\033[0m"
               << "|"; // highlights the current day
        else {
          cout << setw(4) << right << cell[c].gregVal
               << "|"; // prints the gregorean half
        }
      } else
        cout << setw(5) << right << "|";
    }
    cout << endl;

    cout << "|";
    for (int c = 0; c < mat[r].size(); c++) {
      if (cell[c].ethVal != 0) {
        if (cell[c].gregVal == todayDay && month == todayMonth)
          cout << "\033[48;5;24;32m" << setw(4) << left << cell[c].ethVal
               << "\033[0m" << "|"; // highlights the current day
        else {
          cout << "\033[32m" << setw(4) << left << cell[c].ethVal << "\033[0m"
               << "|"; // prints the Ethiopian half
        }
      } else
        cout << setw(5) << right << "|";
    }
    if (holiday_counter < holidays.size()) {
      cout << setw(4) << right << " " << holidays[holiday_counter];
      holiday_counter++;
    }
    cout << endl;
    cout << "|----------------------------------|" << endl;
  }
}
