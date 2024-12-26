#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "datelib.h"
#include <cmath>


using namespace std;



struct Cell{

  string gregVal= "     |";
  string ethVal = "     |";

  void set_greg_val(int num){ 
      int i = 4;
      while (num > 0){
        gregVal[i] = char(num%10 + '0');
      i-=1;
      num /= 10;
      } 
  }
  void set_eth_val(int num){
    if (num == 0) num = 30;
    int i = int(log10(num));
      while (num > 0){
        ethVal[i] = char(num%10 + '0');
        i-=1;
        num /= 10;
      }
  }

};

void print(vector<vector<int>>&, int, int);
vector<vector<int>> con_matirx(int, int);

int main() {
  int month, year;
  cin >> month >> year;
  vector<vector<int>> mat = con_matirx(month, year);
  int ethDay = calc_days_passed(month, year);
  int ethMax = ethMaxDays(month, year);
  print(mat, ethDay, ethMax);

  return 0;
}

void print(vector<vector<int>> &mat, int ethDay, int ethMax){

  cout << "|-----------------------------------------|" << endl;
  cout << "|Sun  |Mon  |Tue  |Wed  |Thu  |Fri  |Sat  |" << endl;
  cout << "|-----------------------------------------|" << endl;

  for (int r = 0; r < mat.size(); r++){
    cout << "|";
    Cell cell[7];
    for (int c = 0; c < mat[r].size() ; c++){
      cell[c].set_greg_val(mat[r][c]);
      int temp = ethDay-int(ethDay/ethMax);
      if (mat[r][c]!=0) {cell[c].set_eth_val((temp)%30); ethDay++;}
      
      cout << cell[c].gregVal;
      // ethDay ++;
    }
    cout << endl;


    cout << "|";
    for (int c = 0; c < mat[r].size(); c++){
      cout << cell[c].ethVal;
    }
    cout << endl;
    cout << "|-----------------------------------------|" << endl;
  }

}

vector<vector<int>> con_matirx(int month, int year) {
  int century_code;
  if (year<1752 ||  (month<=9 && year == 1752)){
    century_code = (18 - year / 100) % 7;
  }else{
    century_code = greg_century_code[year / 100 * 100];
  }
  // int century_code =
      // ((18 - year / 100) % 7) * (month <= 9 && year <= 1752) +
      // (greg_century_code[year / 100 * 100]) * !(month <= 9 && year <= 1752);
  int year_code = ((year % 100) + (year % 100) / 4) % 7;
  int leap_year_code = get_leap_year_code(month, year);
  int start_day = (year_code + greg_month_code[month - 1] + century_code + 1 -
                   leap_year_code + 1 * (year < 4)) %
                  7;
  int rows;
  int cols = 7;
  int days = greg_month_count[month - 1] +
             (isGregLeapYear(year) + leap_year_code * (year <= 1752)) *
                 (month - 1 == 1);

  int remaining_days = days - (7 - start_day);
  rows = ceil((float)(remaining_days) / 7.0) + 1;
  int offset = start_day;

  vector<int> single_row(cols, 0);
  if (!(month==9 && year == 1752)) {
    vector<vector<int>> mat(rows, single_row);
    for (int i = 0; i < days; i++) {
      mat[(offset + i) / cols][(offset + i) % cols] = i + 1;
    }
    return mat;
  }
  int fillValues = 0;
  rows = ceil((float)(remaining_days - 11) / 7.0) + 1;
  vector<vector<int>> mat(rows, single_row);

  for (int i = 0; i < days; i++) {
    if (fillValues < greg_month_count[month - 1]) {
      mat[(offset + i) / cols][(offset + i) % cols] = fillValues + 1;
      fillValues += 1 + 11 * (i == 1);
    } else {
      break;
    }
  }
  return mat;
}