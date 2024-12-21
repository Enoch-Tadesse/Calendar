#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

vector<int> greg_month_count = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int isLeapYear(int);
int calc_days_passed(int, int);
unordered_map<int, int> century_code = {
    {1800, 3}, {1900, 2}, {2000, 1}, {2100, 1}};

int generateId(int, int);
int specialId = 91752;
int id;

int main() {
  int month, year;
  cin >> month >> year;
  ::id = generateId(month, year);
  cout << calc_days_passed(month, year);

  return 0;
}

int isLeapYear(int year) {
  if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
    return 1;
  }
  return 0;
}

int isJulianLeapYear(int year) {
  if (year % 4 == 0)
    return 1;
  return 0;
}
int calc_days_passed(int month, int year) {
  int day = century_code[ceil(float(year) / 100) * 100];
  cout << day << endl;
  int days_passed = 0;
  greg_month_count[1] += isLeapYear(year);
  int ethiopianNewYearDay;
  if (month < 9) {
    ethiopianNewYearDay = (year - 8) % 4 == 0 ? 12 : 11;
  } else {
    ethiopianNewYearDay = (year - 7) % 4 == 0 ? 12 : 11;
  }
  if (month >= 9) {
    days_passed += day - ethiopianNewYearDay;
    for (int i = 8; i < month - 1; i++) {
      days_passed += greg_month_count[i];
    }
    days_passed += day;
  } else {
    for (int i = 8; i < 12; i++) {
      days_passed += greg_month_count[i];
    }
    days_passed += greg_month_count[8] - ethiopianNewYearDay + day;
    for (int i = 0; i < month - 1; i++) {
      days_passed += greg_month_count[i];
    }
    days_passed += day;
  }
  return days_passed;
}

int generateId(int month, int year) {
  int digits = year == 0 ? 1 : int(log10(year) + 1);
  return month * pow(10, digits) + year;
}
