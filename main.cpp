#include "datelib.h"
#include <iostream>

using namespace std;

int main() {
  int month, year;
  cout << "Enter gregorean month between 1 - 12: ";
  cin >> month;
  cout << "Enter gregorean year between 1 - 2300: ";
  cin >> year;

  print(month, year);
  cout << "Press Enter to exit" << endl;
  cin.ignore();
  cin.get();
  return 0;
}
