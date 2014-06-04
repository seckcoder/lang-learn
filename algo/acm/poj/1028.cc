
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <set>
#include <cstdio>
#include <climits>
#include <functional>


using namespace std;

#define int64 long long int


vector<string> forward;
vector<string> back;
string current;

void cmdBack() {
  if (back.empty()) {
    printf("Ignored\n");
  } else {
    forward.push_back(current);
    current = back.back();
    back.pop_back();
    printf("%s\n", current.c_str());
  }
}

void cmdForward() {
  if (forward.empty()) {
    printf("Ignored\n");
  } else {
    back.push_back(current);
    current = forward.back();
    forward.pop_back();
    printf("%s\n", current.c_str());
  }
}

void cmdVisit(const string &url) {
  back.push_back(current);
  current = url;
  forward.clear();
  printf("%s\n", current.c_str());
}

int main(int argc, const char *argv[])
{
  //freopen("test.in", "r", stdin);
  current = "http://www.acm.org/";
  string cmd;
  cin >> cmd;
  while (cmd != "QUIT") {
    if (cmd == "BACK") {
      cmdBack();
    } else if (cmd == "FORWARD") {
      cmdForward();
    } else if (cmd == "VISIT") {
      string new_url;
      cin >> new_url;
      cmdVisit(new_url);
    }
    cin >> cmd;
  }
  return 0;
}
