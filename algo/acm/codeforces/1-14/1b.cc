#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::cin;
using std::string;
using std::stringstream;


template <class T>
int walkWhen(const string &s, int start, const T &uop) {
  for(int i = start; i < s.length(); i++) {
    if (!uop(s[i])) {
      return i;
    }
  }
  return s.length();
}

namespace UnaryOp {
class IsDigit {
 public:
  bool operator()(char c) const {
    if (c <= '9' && c >= '0') {
      return true;
    } else {
      return false;
    }
  }
};

class IsLetter {
 public:
  bool operator()(char c) const {
    if ((c <= 'Z' && c >= 'A') ||
        (c <= 'z' && c >= 'a')) {
      return true;
    } else {
      return false;
    }
  }
};
};



bool isRCCoord(const string &coord) {
  if (coord[0] == 'R') {
    int cur = walkWhen(coord, 1, UnaryOp::IsDigit());
    if (cur >= coord.length() || cur == 1) {
      return false;
    }
    if (coord[cur] == 'C') {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

string colNumToColStr(int num) {
  string res;
  while (num != 0) {
    //char c = 'A' + num % 27 - 1;
    char c = (num-1)%26 + 'A';
    res.push_back(c);
    num = (num-1) / 26;
  }
  std::reverse(res.begin(), res.end());
  return res;
}

int colStrToColNum(const string &str) {
  int res = 0;
  for(int i = 0; i < str.length(); i++) {
    res = res * 26 + str[i] - 'A' + 1;
  }
  return res;
}

void toRcCoord(const string &coord, int &row, int &col) {
  int c_pos = coord.find('C', 1);
  row = atoi(coord.substr(1, c_pos-1).c_str());
  col = atoi(coord.substr(c_pos+1, coord.length()-(c_pos+1)).c_str());
}

void toExcelCoord(const string &coord, int &row, string &col) {
  int pos = walkWhen(coord, 0, UnaryOp::IsLetter());
  col = coord.substr(0, pos);
  row = atoi(coord.substr(pos, coord.length() - pos).c_str());
}


int main(int argc, const char *argv[])
{
  int test_num;
  cin >> test_num;
  for(int i = 1; i <= test_num; i++) {
    string coord;
    cin >> coord;
    if (isRCCoord(coord)) {
      int row;
      int col;
      toRcCoord(coord, row, col);
      //cout << row << " " << col << endl;
      stringstream str_stream;
      str_stream << colNumToColStr(col) << row;
      cout << str_stream.str() << endl;
    } else {
      int row;
      string col;
      toExcelCoord(coord, row, col);
      stringstream str_stream;
      str_stream << "R" << row << "C" << colStrToColNum(col) << endl;
      cout << str_stream.str() << endl;
    }
  }
  return 0;
}
