#pragma once
#include <unordered_map>
#include <vector>

extern std::unordered_map<int, int> century_code;

extern std::vector<int> greg_month_count;


extern std::unordered_map<int, int> greg_century_code;

extern std::vector<int> greg_month_code;

int calc_days_passed_greg(int, int);
int calc_days_passed_jul(int, int);

int get_leap_year_code(int, int);
int isJulianLeapYear(int);
int isGregLeapYear(int);

int calc_days_passed(int , int );
int ethMaxDays(int,int);
