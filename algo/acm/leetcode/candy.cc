#include <vector>
#include <algorithm>

#include <iostream>
using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    int candy(vector<int> &ratings) {
      vector<int> candies(ratings.size(), 0);
      candy_rec(ratings, candies, 0, 1);
      return sum(candies, 0, ratings.size()-1);
    }
    int sum(const vector<int> &candies, int start, int end) {
      int ret = 0;
      for(int i = start; i <= end; i++) {
        //cout << candies[i] << endl;
        ret += candies[i];
      }
      return ret;
    }
    void candy_rec(const vector<int> &ratings,
                   vector<int> &candies,
                   int start,
                   int start_smallest) {
      if (start >= ratings.size()) {
          return;
      } else if (start == ratings.size() - 1) {
        candies[start] = start_smallest;
        return;
      } else if (ratings[start] < ratings[start+1]) {
        candies[start] = start_smallest;
        candy_rec(ratings, candies, start+1, start_smallest+1);
      }  else if (ratings[start] == ratings[start+1]) {
        candies[start] = start_smallest;
        candy_rec(ratings, candies, start+1, 1);
      } else if (ratings[start] > ratings[start+1]) {
        candy_rec(ratings, candies, start+1, 1);
        candies[start] = std::max(start_smallest, candies[start+1]+1);
      }
    } 
};



int main(int argc, const char *argv[])
{
  Solution sol;
  int c_ratings[] = {4,2,3,4,1};
  vector<int> ratings(c_ratings, c_ratings+5);
  cout << sol.candy(ratings) << endl;;
  return 0;
}
