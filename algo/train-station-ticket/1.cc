/*
有n个火车站，每个火车站有a1, a2, …, an张火车票可以卖，票的价格是该火车站剩余的火车票数，问怎样卖票可以让前m张票的总收入最高,并打印总收入。比如说m = 4, n = 2， a1 = 2, a2 = 5, 则总收入为14 = 5 + 4 + 3 + 2.    这题 我想到的解法 1 是用类似merige sort 的方法 每次取最大的值 然后更新。 所以可以利用一个maxHeap 来做 （getMax， 然后将max—， 如果大于0 再次放入heap里）。 你觉得有没有更快的方法
*/


#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
using namespace std;

// sum l + (l+1) + ... + h
inline int sum(int l, int h) {
  // we can implement this in O(1)
  
  return (h-l+1) * (l+h) / 2;
}


// Method 2:
// It's really hard to explain the following O(n) algorithm in word.
// I will give an example of the algorithm below.
int calc_max_income(vector<int> &tickets, int m) {
  // sort in reverse order
  std::sort(tickets.begin(), tickets.end(), std::greater<int>());

  // push 0 to the end.
  // Just to make the code simpler.
  tickets.push_back(0);

  int income_acc = 0;
  for (int i = 1; i < tickets.size() && m > 0; i++) {
    int tickets_sold = (tickets[i-1] - tickets[i]) * i;
    if (tickets_sold >= m) {
      int num_rounds = m / i;
      income_acc += (num_rounds * i) * sum(tickets[i-1]-num_rounds+1, tickets[i-1]);
      income_acc += (tickets[i-1]-num_rounds) * (m % i);
      break;
    } else {
      m -= tickets_sold;
      income_acc += sum(tickets[i]+1, tickets[i-1]) * i;
    }
  }
  return income_acc;
}


// Example: [10,7,5,3], m = 20
// 
// 10, 7, 5, 3, 0
// -> tickets_sold = (10 - 7) * 1 = 3 < 20
// After selling these tickets, we have
// 7, 7, 5, 3, 0. m = 17 And the income is (10 + 9 + 8) * 1 = 27
//
// -> tickets_sold = (7 - 5) * 2 = 4 < 17
// After selling these tickets, we have
//
// 5,5,5,3,0. m = 13. And the income is 27 + (7 + 6) * 2 = 53
//
// -> tickets_sold = (5 - 3) * 3 = 6 < 13
//
// After selling these tickets, we have
//
// 3,3,3,3,0. m = 7. And the income is 53 + (5 + 4) * 3 = 80
//
// -> tickets_sold = (3 - 0) * 4 = 12 > 7. 
//
// Therefore, we can't sell all those tickets.
// This reaches the code : 34 - 39
// As a result, we will sell
// 
// 7 / 4 = 1. Means we have to sell all these station with 3 tickets.
// After selling these tickets, we have
//
// 2,2,2,2,0. m = 3. And the income is 80 + (3) * 4 = 92
//
// Then, we will see three stations with 2 tickets.
// After selling these tickets, we have
//
// 2,1,1,1,0. m = 0. And the income is 92 + (2) * 3 = 98

int main() {

  vector<int> tickets = {3,7,5,10};
  cout << calc_max_income(tickets, 20) << endl;
  return 0;
}
