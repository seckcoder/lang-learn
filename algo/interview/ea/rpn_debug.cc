#include <iostream>
#include <exception>
#include <vector>
#include <queue>
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
    virtual void unparseInfix(ostream &out) = 0;
    virtual void free() {}
    virtual ~Exp() {}
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
    virtual void unparseInfix(ostream &out) {
      out << v;
    }
    virtual string type() const {
      return "Num";
    }
};

int getOpLevel(char op) {
  // we only take care of binary operators
  if (op == '+' || op == '-') return 0;
  else if (op == '*' || op == '/') return 1;
  return 0;
}

// Compare operator priority
// return -1 if op1<op2
// return 0 if op1 == op2
// return 1 if op1 > op2
int opCmp(char op1, char op2) {
  int level1 = getOpLevel(op1);
  int level2 = getOpLevel(op2);
  if (level1 < level2) return -1;
  else if (level1 > level2) return 1;
  else return 0;
}

class BiOp:public Exp {
  public:
    char op;
    Exp *p1;
    Exp *p2;
    void printBracketIfPossible(ostream &out, Exp *p) {
      if (p->type() == "BiOp") {
        char p_op = ((BiOp*)p)->op;
        // print bracket if op has higher priority
        if (opCmp(p_op, op) < 0) {
          out << "(";
          p->unparseInfix(out);
          out << ")";
        } else {
          p->unparseInfix(out);
        }
      } else {
        p->unparseInfix(out);
      }
    }
    virtual void unparseInfix(ostream &out) {
      printBracketIfPossible(out, p1);
      out << op;
      printBracketIfPossible(out, p2);
      //out << endl;
    }
    void free() {
      p1->free();
      p2->free();
      delete p1;
      delete p2;
    }
    virtual string type() const {
      return "BiOp";
    }
};

class UnOp : public BiOp {
  public:
    char op;
    Exp *p;
    virtual void unparseInfix(ostream &out) {
      out << op;
      // if the top level is a binary operator, we assume that
      // Unary operator has higher priority over all binary operators
      if (p->type() == "BiOp") {
        out << "(";
        p->unparseInfix(out);
        out << ")";
      } else {
        p->unparseInfix(out);
      }
    }
    virtual void free() {
      delete p;
    }
    virtual ~UnOp() {
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

/* Exp *parseOneRPN(const string &line, int &cur) { */
/*   if (cur >= line.length()) { */
/*     throw exception(); */
/*   } */
/*   Num *exp_num = new Num; */
/*   exp_num->parse(line, cur); */
/*   ignoreSpaces(line, cur); */
/*   if (cur >= line.length()) return (Exp*)exp_num; */
/*   if (isUnOp(line[cur])) { */
/*     UnOp *unop = new UnOp; */
/*     unop->p = exp_num; */
/*     unop->op = line[cur]; */
/*     cur += 1; */
/*     return (Exp*)unop; */
/*   } else { */
/*     Exp *exp2 = parseOneRPN(line, cur); */
/*     ignoreSpaces(line, cur); */
/*     if (cur >= line.length()) { */
/*       throw exception(); */
/*     } */
/*     if (isBiOp(line[cur])) { */
/*       BiOp *biop = new BiOp; */
/*       biop->p1 = exp_num; */
/*       biop->p2 = exp2; */
/*       biop->op = line[cur]; */
/*       cur += 1; */
/*       return (Exp*)biop; */
/*     } else { */
/*       throw exception(); */
/*     } */
/*     return NULL; // make compiler happy */
/*   } */
/* } */

Num *parseNum(const string &line, int &cur) {
  Num *pn = new Num;
  pn->parse(line, cur);
  return pn;
}

void freeExps(vector<Exp*> &exps) {
  for (int i = 0; i < exps.size(); i++) {
    exps[i]->free();
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
      } else if ( isUnOp(line[cur])) {
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
    if (exp_stack.size() > 1) {
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
  std::getline(std::cin, line, '\n');
  if (line.empty()) {
    cout << "INPUT IS EMPTY." << endl;
  } else {
    Exp* exp = parseRPN(line);
    if (exp) {
      exp->unparseInfix(std::cout);
      exp->free();
      delete exp;
    } else {
      cout << "WRONG INPUT!" << endl;
    }
  }
  return 0;
}
