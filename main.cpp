#include "datelib.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
label:
  int year;
  std::cout << "Enter the calendar year between 1 and 5999: " << std::endl;
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

  return 0;
}
