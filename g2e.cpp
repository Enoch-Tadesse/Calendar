#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

vector<int> greg_month_count = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int isLeapYear(int);
int calc_days_passed(int, int);
unordered_map<int, int> century_code = {
    {1800, 2}, {1900, 1}, {2000, 0}, {2100, 0}};

int main() {
  int month, year;
  cin >> month >> year;
  cout << calc_days_passed(month, year);

  return 0;
}

int isLeapYear(int year) {
  if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
    return 1;
  }
  return 0;
}

int calc_days_passed(int month, int year) {
  const int day = 1;
  int days_passed = 0;
  vector<int> month_count = greg_month_count;
  month_count[1] += isLeapYear(year);

  int ethiopianNewYearDay;
  if (month <= 9) {
    ethiopianNewYearDay = (year - 8) % 4 == 0 ? 12 : 11;
  } else {
    ethiopianNewYearDay = (year - 7) % 4 == 0 ? 12 : 11;
  }

  cout << " " << ethiopianNewYearDay << endl;
  if (month > 9) {
    days_passed += day - ethiopianNewYearDay + month_count[8];
    for (int i = 9; i < month - 1; i++) {
      days_passed += month_count[i];
    }
    days_passed += day;
  } else {
    for (int i = 8; i < 12; i++) {
      days_passed += month_count[i];
    }
    days_passed += greg_month_count[8] - ethiopianNewYearDay + day;
    for (int i = 0; i < month - 1; i++) {
      days_passed += month_count[i];
    }
    days_passed += day - 30;
  }
  int century_id = ceil(float(year) / 100) * 100;
  int offset = century_code[century_id];
  offset += (month < 9 && year <= 1901 && year - 1 == century_id);
  return days_passed + offset;
}
