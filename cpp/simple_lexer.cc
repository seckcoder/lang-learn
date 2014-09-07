#include <string>
#include <vector>
#include <iostream>

using namespace std;

enum Type {TYPE_NUM, TYPE_STR};

class Token {
 public:
  Token() {}
  Token(Type hty): ty(hty) {}
  bool isNumeric() const {
    return ty == TYPE_NUM;
  }
 protected:
  Type ty;
};

class Numeric: public Token {
 public:
  Numeric():Token(TYPE_NUM) { }
  int value;
};

class Alpha: public Token {
 public:
  Alpha():Token(TYPE_STR) {}
  string value;
};

class Lexer {
 public:
  int cur;
  string text;
  void init(const string &ht) {
    text = ht;
    cur = 0;
  }
  bool nextToken(vector<Token *> &toks) {
    skipDelimiter();
    if (cur >= text.size()) {
      // everything finished
      return true;
    }
    int int_v;
    string str_v;
    bool is_str = false;
    while (cur < text.size() && !isDelimiter(text[cur])) {
      if (!is_str && isNumeric(text[cur])) {
        int_v = int_v * 10 + toInteger(text[cur]);
      } else {
        is_str = true;
        str_v.append(1, text[cur]);
      }
      cur++;
    }
    Token *ptok;
    if (is_str) {
      ptok = new Alpha;
      ((Alpha*)(ptok))->value = str_v;
    } else {
      ptok = new Numeric;
      ((Numeric*)(ptok))->value = int_v;
    }
    toks.push_back(ptok);
    return false;
  }
  void skipDelimiter() {
    while (isDelimiter(text[cur])) cur++;
  }
  static bool toInteger(char c) {
    return c - '0';
  }
  static bool isNumeric(char c) {
    return (c >= '0' && c <= '9');
  }
  static bool isDelimiter(char c) {
    switch (c) {
      case ' ':
      case '\n':
      case '\r':
      case '\t':
        return true;
      default:
        return false;
    }
  }
};

bool parse(const string &line) {
  vector<Token *> toks;
  Lexer lex;
  lex.init(line);
  while (!lex.nextToken(toks)) {}
  return (toks.size() == 2 &&
          toks[0]->isNumeric() &&
          toks[1]->isNumeric());
}

int main(int argc, const char *argv[])
{
  string str;
  while (std::getline(std::cin, str)) {
    if (parse(str)) {
      cout << "Two integers" << endl;
    } else {
      cout << "Not Two Integers" << endl;
    }
  }
  return 0;
}
