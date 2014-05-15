// http://oj.leetcode.com/problems/reverse-words-in-a-string/

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

#define WORDSNUM 1000

// copy src[start,end) to dest, append '\0' to dest
void copy_to_word(char* dest, char *src, int start, int end) {
  int i, j;
  for(i = start, j = 0; i < end; i++, j++) {
    dest[j] = src[i];
  }
  dest[j] = '\0';
}

// return the first pos that's non space
int until_non_space(char* str, int i) {
  while (str[i] == ' ') {
    i+=1;
  }
  return i;
}

// return the first pos that's space
int until_space(char* str, int i) {
  while (str[i] != ' ' && str[i] != '\0') {
    i+=1;
  }
  return i;
}

char** get_words(char* str, int *pnum) {
  int len = strlen(str);
  char** words = (char**)malloc(WORDSNUM*sizeof(char*));
  int word_count = 0;
  int s_i = 0;
  while(s_i < len) {
    // ignore leading spaces
    s_i = until_non_space(str, s_i);
    if (s_i < len) {
      int s_j = until_space(str, s_i);
      int word_len = s_j - s_i + 1;
      char* a_word = (char*)malloc(word_len*sizeof(char*));
      copy_to_word(a_word, str, s_i, s_j);
      words[word_count] = a_word;
      word_count += 1;
      s_i = s_j;
      //printf("%s %d %d %d\n", a_word, s_i, s_j, len);
    }
  }
  *pnum = word_count;
  return words;
}

void reverse_arr(char** words, int num_words) {
  for(int i = 0; i < num_words/2; i++) {
    char* tmp = words[num_words-i-1];
    words[num_words-i-1] = words[i];
    words[i] = tmp;
  }
}

void concat_words(char** words, int num_words, char* dest) {
  dest[0] = '\0';
  for(int i = 0; i < num_words; i++) {
    strcat(dest, words[i]);
    if (i < num_words-1) {
      strcat(dest, " ");
    }
  }
}

void free_words(char **words, int num_words){
  for(int i = 0; i < num_words; i++) {
    free(words[i]);
  }
  free(words);
}

void print_words(char **words, int num_words) {
  for(int i = 0; i < num_words; i++) {
    printf("%s\n", words[i]);
  }
}

void c_solution(char *str) {
  int num_words = 0;
  int len = strlen(str);
  char** words = get_words(str, &num_words);
  //print_words(words, num_words);
  reverse_arr(words, num_words);
  char new_str[len];
  concat_words(words, num_words, new_str);
  int new_len = strlen(new_str);
  memcpy(str, new_str, (new_len+1)*sizeof(char));
  free_words(words, num_words);
}

class Solution {
public:
    void reverseWords(string &s) {
      char* c_s = new char[s.length() + 1];
      memcpy(c_s, s.c_str(), (s.length() + 1) * sizeof(char));
      c_solution(c_s);
      s = c_s;
      delete c_s;
    }
};


int main(int argc, const char *argv[])
{
  Solution sol;
  string words(" the sky is blue ");
  sol.reverseWords(words);
  cout << words;
  return 0;
}
