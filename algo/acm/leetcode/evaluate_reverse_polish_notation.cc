// http://oj.leetcode.com/problems/evaluate-reverse-polish-notation/

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using std::string;
using std::vector;
using std::cout;
using std::endl;
string op[] = {"+","-","*","/"};

bool is_operator(const std::string &str) {
  for(int i = 0; i < 4; i++) {
    if (op[i] == str) return true;
  }
  return false;
}

class Solution {
public:
    int evalRPN(vector<string> &tokens) {
      assert(!tokens.empty());
      string top = tokens.back();
      tokens.pop_back();
      if (is_operator(top)) {
        int v2 = evalRPN(tokens);
        int v1 = evalRPN(tokens);
        return eval_op(top, v1, v2);
      } else {
        return atoi(top.c_str());
      }
    }
    int eval_op(const string &op, int v1, int v2) {
      //cout << op << v1 << " " << v2 << endl;
      // v1 op v2
      switch (op[0]) {
        case '+':
          return v1 + v2;
        case '-':
          return v1 - v2;
        case '*':
          return v1 * v2;
        case '/':
          return v1 / v2;
        default:
          return 0;
      }
    }
};


int main(int argc, const char *argv[])
{
  Solution sol;
  vector<string> tokens;
  tokens.push_back(string("3"));
  tokens.push_back(string("-4"));
  tokens.push_back(string("+"));
  cout << sol.evalRPN(tokens) << endl;
  return 0;
}
