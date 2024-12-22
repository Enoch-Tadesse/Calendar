#include <iostream>
#include <vector>

using namespace std;

vector<int> greg_month_count = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int calc_days_passed(int, int);
int isLeapYear(int);

int main() {
  int month, year;
  cin >> month >> year;

  cout << calc_days_passed(month, year) << endl;

  return 0;
}

int calc_days_passed(int month, int year) {
  const int day = 1;
  int days_passed = 0;
  vector<int> month_count = greg_month_count;
  month_count[1] += isLeapYear(year);

  int ethiopianNewYearDay;
  if (month <= 8) {
    ethiopianNewYearDay = (year - 8) % 4 == 0 ? 29 : 28;
  } else {
    ethiopianNewYearDay = (year - 7) % 4 == 0 ? 29 : 28;
  }

  cout << " " << ethiopianNewYearDay << endl;
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
    days_passed += day - 30;
  }
  return days_passed;
}

int isLeapYear(int year) {
  return year % 4 == 0;
  return 0;
}
