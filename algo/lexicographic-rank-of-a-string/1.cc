#include <string>
using namespace std;

// no duplicates


int fact(int n) {
  if (n == 0) return 1;
  int ans = 1;
  for (int i = 1; i <= n; i++) {
    ans *= i;
  }
  return ans;
}


int rank_of_char(const string &str, int start, char c) {
  int rank = 0;
  for (int i = start; i < str.length(); i++) {
    if (str[i] > c) rank += 1;
  }
  return rank;
}


int lex_rank_rec(const string &str, int start) {

  if (start >= str.length()) return 0;
  char first_char = str[start];
  int rest_rank = lex_rank_rec(str, start+1);
  
  return fact(str.length()-1) * rank_of_char(str, start+1, first_char) + rest_rank;
}

int lex_rank(const string &str) {
  return lex_rank_rec(str, 0) + 1;
}

// O(256 * n)


#define M 256
void decrement_char_rank(int char_rank[M], char cur_char) {
  for (char c = 0; c < cur_char; c++) {
    char_rank[c] -= 1;
  }
}

void calc_char_rank(const string &str, int char_rank[M]) {
  for (int i = 0; i < str.length(); i++) {
    char_rank[str[i]] += 1;
  }

  for (int c = 1; c < M; c++) {
    char_rank[c] += char_rank[c-1];
  }
}

int lex_rank_iter(const string &str) {
  int n = str.length();
  int char_rank[M] = {0};
  calc_char_rank(str, char_rank);
  int fact_acc = fact(n);
  int rank = 0;
  for (int i = 0; i < n; i++) {
    fact_acc /= (n-i);
    // rank += fact(n-i-1) * char_rank[str[i]]
    // Here, we use fact_acc so that we can construct the fact quickly.
    rank += fact_acc * char_rank[str[i]];
    // after we remove the char, we need to decrement the char rank
    // of chars < str[i]
    decrement_char_rank(char_rank, str[i]);
  }
  return rank;
}


// return the permutation count formed by all chars
int perm_count(int char_count[]) {
  int total_char_num = 0;
  int uniq_char_num = 0;
  int repetive_char_num = 0;
  for (int c = 0; c < M; c++) {
    total_char_num += char_count[c];
    if (char_count[c] == 1) {
      uniq_char_num += 1;
    }
    if (char_count[c] > 1) {
      repetive_char_num += 1;
    }
  }
  // k! * (m+1) * (m+2) * ... * n
  // Suppose the str is aabbccdef
  // Then the permutation count of it is:
  //
  // permutation of [aa, bb, cc]. Suppose the number of
  // these repetive chars is k.
  //
  // These repetive chars form 
  //
  // [a,a,b,b,c,c]. So we have 7 empty spots.
  // insert d,e,f one by one in empty spot. Suppose there are x uniq chars
  // 
  // So it's k! * (n-x+1) * (n-x+2) * ... n = k! * n! / x!
  return fact(repetive_char_num) * fact(total_char_num) / fact(uniq_char_num);
}

int lex_rank_rec_uniq(const string &str) {
  int char_count[M] = {0};
  
  // enumerate through every c smaller than str[i]
  int rank = 0;

  for (int i = 0; i <str.length(); i++) {
    for (int c = 0; c < str[i]; c++) {
      if (char_count[c] > 0) {
        // if rest str contain the char
        
        char_count[c] -= 1;
        // Permutation count of rest string without c is what we need.
        rank += perm_count(char_count);
        char_count[c] += 1;
      }
    }
    char_count[str[i]] -= 1;
  }
  return rank;
}



