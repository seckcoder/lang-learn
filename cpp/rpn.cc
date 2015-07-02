
/*
 * rpn.cc
 *
 * Requirement: It requires g++ or clang++ with c++11 enabled
 * Build:
 *  clang++ -std=c++11 -stdlib=libc++ rpn.cc -o rpn
 *  then run "./rpn"
 *
 *
 */

#include <iostream>
#include <exception>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// RPN:
// Exp := Num
//      | expr expr BiOP
//      | expr UnOp


// Exp := Num
//      | BiOp Exp Exp
//      | UnOp Exp


class Exp {
  public:
    virtual void unparseInfix(ostream &out) const = 0;
    virtual ~Exp() {
    }
    virtual string type() const {
      return "Exp";
    }
};


inline bool isDigit(char c) {
  return c >= '0' && c <= '9';
}

inline int toDigit(char c) {
  return c - '0';
}

class Num: public Exp {
  public:
    int v;
    void parse(const string &line, int &cur) {
      v = 0;
      while (isDigit(line[cur])) {
        v = v * 10 + toDigit(line[cur]);
        cur += 1;
      }
    }
    virtual ~Num() {
    }
    virtual void unparseInfix(ostream &out) const {
      out << v;
    }
    virtual string type() const {
      return "Num";
    }
};


typedef std::unordered_map<char,int> PriorityMap;
static const PriorityMap OP_PRIORITY = {
  {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2},
  {'_', 3}
};

// Compare operator priority
// return -1 if op1<op2
// return 0 if op1 == op2
// return 1 if op1 > op2
int opCmp(char op1, char op2) {
  PriorityMap::const_iterator it1 = OP_PRIORITY.find(op1);
  PriorityMap::const_iterator it2 = OP_PRIORITY.find(op2);
  if (it1 == OP_PRIORITY.end() || it2 == OP_PRIORITY.end()) {
    // default equal
    return 0;
  } else if (it1->second < it2->second) {
    return -1;
  } else if (it1->second > it2->second) {
    return 1;
  } else {
    return 0;
  }
}


class Op: public Exp {
  public:
    char op;
    virtual void unparseSubExp(ostream &out, const Exp *exp) const {
      const Op *exp_op = dynamic_cast<const Op*>(exp);
      if (exp_op && (opCmp(exp_op->op, op) < 0)) {
        // is an op exp and has smaller priority
        out << "(";
        exp->unparseInfix(out);
        out << ")";
      } else {
        exp->unparseInfix(out);
      }
    }
};

class BiOp:public Op {
  public:
    virtual void unparseInfix(ostream &out) const {
      unparseSubExp(out, p1);
      out << op;
      unparseSubExp(out, p2);
    }

    virtual ~BiOp() {
      delete p1;
      delete p2;
    }

    virtual string type() const {
      return "BiOp";
    }
    Exp *p1;
    Exp *p2;
};

class UnOp : public Op {
  public:
    char op;
    Exp *p;
    virtual void unparseInfix(ostream &out) const {
      out << op;
      unparseSubExp(out, p);
    }
    virtual ~UnOp() {
      delete p;
    }
    virtual string type() const {
      return "UnOp";
    }
};

void ignoreSpaces(const string &line, int &cur) {
  while (cur < line.length() && line[cur] == ' ') {
    cur += 1;
  }
}

inline bool isBiOp(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}
inline bool isUnOp(char c) {
  return c == '_';
}

Num *parseNum(const string &line, int &cur) {
  Num *pn = new Num;
  pn->parse(line, cur);
  return pn;
}

void freeExps(vector<Exp*> &exps) {
  for (int i = 0; i < exps.size(); i++) {
    delete exps[i];
  }
}

/* parse rpn and return the expression parsed */
Exp *parseRPN(const string &line) {
  vector<Exp*> exp_stack;
  int cur = 0;
  try {
    while (cur < line.length()) {
      if (isDigit(line[cur])) {
        Num *pn = parseNum(line, cur);
        exp_stack.push_back(pn);
      } else if (isBiOp(line[cur])) {
        if (exp_stack.size() < 2) {
          throw exception();
        }
        BiOp *biop = new BiOp;
        biop->op = line[cur];
        biop->p2 = exp_stack.back();
        exp_stack.pop_back();
        biop->p1 = exp_stack.back();
        exp_stack.pop_back();
        exp_stack.push_back((Exp*)biop);
        cur += 1;
      } else if (isUnOp(line[cur])) {
        if (exp_stack.empty()) {
          throw exception();
        }
        UnOp *unop = new UnOp;
        unop->op = line[cur];
        unop->p = exp_stack.back();
        exp_stack.pop_back();
        exp_stack.push_back((Exp*)unop);
        cur += 1;
      } else {
        // simply ignore other characters...
        // Maybe we should throw an exception for illegal characters
        cur += 1;
      }
    } 
    if (exp_stack.size() != 1) {
      throw exception();
    }
    return exp_stack.back();
  } catch (exception &e) {
    // Simple error handling
    freeExps(exp_stack);
    return NULL;
  }
}

int main() {
  string line;
  cout << "Input your expression here..." << endl;
  while (std::getline(std::cin, line, '\n') && !std::cin.eof()) {
    Exp* exp = parseRPN(line);
    if (exp) {
      exp->unparseInfix(std::cout);
      std::cout << endl;
      delete exp;
    } else {
      cout << "WRONG INPUT!" << endl;
    }
  }
  return 0;
}
