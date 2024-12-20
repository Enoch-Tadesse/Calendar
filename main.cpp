#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> greg_month_count = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

unordered_map<int, int> greg_century_code = {{1700, 4}, {1800, 2}, {1900, 0},
                                             {2000, 6}, {2100, 4}, {2200, 2},
                                             {2300, 0}};

vector<int> greg_month_code = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
int generateId(int, int);
int get_leap_year_code(int, int);
int isJulianLeapYear(int);
int isGregLeapYear(int);
vector<vector<int>> con_matirx(int, int, int, int, int, int);

int main() {
  int month, year;
  cin >> month >> year;
  int id = generateId(month, year);
  int specialId = 91752;
  vector<vector<int>> some;
  int century_code = ((18 - year / 100) % 7) * (id <= specialId) +
                     (greg_century_code[year / 100 * 100]) * (id > specialId);
  int year_code = ((year % 100) + (year % 100) / 4) % 7;
  int leap_year_code = get_leap_year_code(month, year);
  int start_day = (year_code + greg_month_code[month - 1] + century_code + 1 -
                   leap_year_code + 1 * (year < 4)) %
                  7;
  cout << "Year: " << year_code << endl;
  cout << "LYC: " << leap_year_code << endl;
  cout << "start_day: " << start_day << endl;
  cout << "century_code: " << century_code << endl;
  some = con_matirx(start_day, month, year, leap_year_code, id, specialId);

  for (int i = 0; i < some.size(); i++) {
    for (int j = 0; j < some[i].size(); j++) {
      cout << some[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
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
  if (((year % 4 == 0 && year % 400 != 100) || year % 400 == 0) &&
      (year > 1752))
    return 1;
  else
    return 0;
}

int isJulianLeapYear(int year) {
  // checks if the date is a Julian Leap Year
  if (year % 4 == 0 && year != 4 && year < 1752)
    return 1;
  return 0;
}

vector<vector<int>> con_matirx(int start_day, int month, int year,
                               int leap_year_code, int id, int specialId) {
  cout << start_day << endl;
  int rows;
  int cols = 7;
  int days = greg_month_count[month - 1] +
             (isGregLeapYear(year) + leap_year_code * (year < 1752)) *
                 (month - 1 == 1);
  int remaining_days = days - (7 - start_day);
  rows = ceil((float)(remaining_days) / 7.0) + 1;
  int offset = start_day;
  vector<int> single_row(cols, 0);
  if (id != specialId) {
    vector<vector<int>> num(rows, single_row);
    for (int i = 0; i < days; i++) {
      num[(offset + i) / cols][(offset + i) % cols] = i + 1;
    }
    return num;
  }
  int values = 0;
  rows = ceil((float)(remaining_days - 11) / 7.0) + 1;
  vector<vector<int>> num(rows, single_row);

  for (int i = 0; i < days; i++) {
    if (values < greg_month_count[month - 1]) {
      num[(offset + i) / cols][(offset + i) % cols] = values + 1;
      values += 1 + 11 * (i == 1);
    } else {
      break;
    }
  }
  return num;
}

int generateId(int month, int year) {
  // generates a unique id for all dates
  int digits = (year == 0) ? 1 : int(log10(year) + 1);
  return month * pow(10, digits) + year;
}
