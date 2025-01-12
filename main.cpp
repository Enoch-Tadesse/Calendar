#include "datelib.h"
#include <iostream>

using namespace std;

int main() {
  int month, year;
  std::cout << "Enter a month 1 - 12: ";
  cin >> month;
  cout << "Enter a year in gregorian 1 - 4599: ";
  cin >> year;

  print(month, year);
  cin.clear();
  cin.ignore();
  cout << "Press any key to exit" << endl;
  cin.get();

  return 0;
}
