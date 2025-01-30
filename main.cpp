#include "datelib.h"
#include <iostream>

using namespace std;

int main() {
label:
  char type;
  std::cout << "Enter 'w' for whole year or 's' for specific month and year. "
            << std::endl;
  std::cin >> type;
  switch (type) {
  case 'w':
  case 'W':
    int year;
    std::cout << "Enter the calendar year between 1 and 5999 in gregorean: "
              << std::endl;
    std::cin >> year;
    if (year < 1 or year > 5999) {
      std::cerr << "You entered invalid year. Please try again." << std::endl;
      std::cin.clear();
      std::cin.ignore();
      goto label;
    }
    for (int month = 1; month <= 12; month++)
      print(month, year);
    std::cout << "Press any key to exit. " << std::endl;
    std::cin.clear();
    std::cin.ignore();
    cin.get();
    break;
  case 's':
  case 'S':
    int month;
    std::cout << "Enter the month between 1 - 12: ";
    std::cin >> month;
    if (month < 1 or month > 12) {
      std::cerr << "You entered invalid month. Please try again." << std::endl;
      std::cin.clear();
      std::cin.ignore();
      goto label;
    }
    std::cout << "Enter the calendar year: ";
    std::cin >> year;
    if (year < 1 or year > 5999) {
      std::cerr << "You entered invalid year. Please try again." << std::endl;
      std::cin.clear();
      std::cin.ignore();
      goto label;
    }
    print(month, year);
    std::cout << "Press any key to exit. " << std::endl;
    std::cin.clear();
    std::cin.ignore();
    cin.get();
    break;
  default:
    std::cerr << "You entered invalid type. Please try again." << std::endl;
    std::cin.clear();
    std::cin.ignore();
    goto label;
    break;
  }

  return 0;
}
