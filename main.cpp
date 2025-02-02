#include "datelib.h"
#include <ctime>
#include <iostream>

void handle_error() {
  // handles error input and display error messages
  std::cout << "Invalid Usage!" << std::endl;
  std::cout << "Usage: ecal [<1,12> optional] [<1,4599> optional]" << std::endl;
  exit(1);
}
int main(int argc, char *argv[]) {
  int month, year;

  // get current datetime
  std::time_t today = std::time(0);
  std::tm *now = std::localtime(&today);
  int todayDay = now->tm_mday;
  int todayMonth = now->tm_mon + 1;
  int todayYear = now->tm_year + 1900;

  if (argc == 3) { // if called with month and year
    month = atoi(argv[1]);
    year = atoi(argv[2]);
    if (month < 1 || month > 12 || year < 1 || year > 4599) {
      handle_error();
    }
    std::cout << todayYear << std::endl;
    todayYear == year ? print(month, year, todayDay, todayMonth)
                      : print(month, year);
  } else if (argc == 2) { // if called with only year
    year = atoi(argv[1]);
    if (year < 1 || year > 4599) {
      handle_error();
    }
    for (int i = 1; i <= 12; i++)
      year == todayYear ? print(i, year, todayDay, todayMonth) : print(i, year);
  } else if (argc == 1) { // if called without argument
    print(todayMonth, todayYear, todayDay, todayMonth);
  } else { // more than 3 arguments
    handle_error();
  }
}
