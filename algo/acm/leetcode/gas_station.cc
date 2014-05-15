#include <vector>
#include <iostream>
using namespace std;

class Solution {
 public:
  vector<int> gas;
  vector<int> cost;
  bool failed;
  int rec(int start) {
    if (start >= gas.size()) {
      return -1;
    } else if (gas[start] - cost[start] < 0) {
      return rec(start+1);
    } else {
      //cout << start << " " << get_next(start) << endl;
      this->failed = false;
      int new_start = rec1(start, get_next(start), gas[start] - cost[start]);
      if (new_start == start && !failed) {
        return start;
      } else if (new_start <= start) {
        return -1;
      } else {
        return rec(new_start);
      }
    }
  }
  int rec1(int start, int next, int accum) {
    //cout << "rec1 " << next << " " << accum << endl;
    //cout << start << " " << next << " " << accum << endl;
    if (accum < 0) {
      this->failed = true;
      return next;
    } else if (next == start) {
      return next;
    } else {
      return rec1(start, get_next(next), accum + gas[next] - cost[next]);
    }
  }
  int get_next(int cur) {
    if (cur+1 >= gas.size()) {
      return 0;
    } else {
      return cur+1;
    }
  }
  int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    this->gas = gas;
    this->cost = cost;
    return rec(0);
  }
};


int main(int argc, const char *argv[])
{
  Solution sol;
  /*int c_gas[] = {2, 0, 2};
    int c_cost[] = {1, 2, 1};
    int n = 3;*/
  int c_gas[] = {2, 4};
  int c_cost[] = {3, 4};
  int n = 2;
  /*int c_gas[] = {5,0,9,4,3,3,9,9,1,2};
  int c_cost[] = {6,7,5,9,5,8,7,1,10,5};
  int n = 10;*/
  vector<int> gas(c_gas, c_gas+n);
  vector<int> cost(c_cost, c_cost+n);
  cout << sol.canCompleteCircuit(gas, cost) << endl;
  return 0;
}
