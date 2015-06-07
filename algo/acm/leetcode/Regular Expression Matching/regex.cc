#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <queue>
#include <cassert>
#include <stack>
using namespace std;

class Automaton;
class EpsilonNfa;
class Expression {
  public:
    virtual EpsilonNfa generateEpsilonNfa(Automaton* automaton) = 0;
};
typedef unsigned char uchar;
class CharRange {
  public:
    uchar begin;
    uchar end;
    CharRange()
      :begin(-1), end(-1) {}
    CharRange(uchar begin_, uchar end_)
      :begin(begin_), end(end_) {}
    bool operator==(const CharRange &c) const {
      return begin == c.begin && end == c.end;
    }
    bool contain(char c) const {
      return begin <= c && c <= end;
    }
};

void printCharRange(const CharRange &range);

class State;
class Transition;
class Transition {
  public:
    State* source;
    State* target;
    enum Type {
      Chars,   // char range transition
      Epsilon
    };
    Type type;
    CharRange range;
    void copyInfo(const Transition *transition) {
      type = transition->type;
      range = transition->range;
    }
    static bool sameClass(const Transition* const t1,
        const Transition* const t2) {
      if (t1->type != t2->type) return false;
      switch (t1->type) {
        case Transition::Epsilon:
          return true;
        case Transition::Chars:
          return (t1->range == t2->range);
        default:
          return true;
      }
    }
};
class State {
  public:
    bool isFinal;
    vector<Transition*> trans_out;
    vector<Transition*> trans_in;
    State()
      :isFinal(false) {}
};


class EpsilonNfa {
  public:
    State* start;
    State* end;
    EpsilonNfa()
      :start(0), end(0) {}
};

class StateRecord {
  public:
    State* curState;
    int nextTransition;
    StateRecord(State* curState_,
        int nextTransition_)
      :curState(curState_),
      nextTransition(nextTransition_) {}
};

class Automaton {
  public:
    vector<State*> states;
    vector<Transition*> transitions;
    State* startState;
    State* newState() {
      State *state = new State();
      states.push_back(state);
      return state;
    }
    Transition* newTransition(State* start,
        State* end) {
      Transition* transition = new Transition();
      transition->source = start;
      transition->target = end;
      start->trans_out.push_back(transition);
      end->trans_in.push_back(transition);
      transitions.push_back(transition);
      return transition;
    }
    Transition* newChar(State* start,
        State* end,
        const CharRange &range
        ) {
      Transition* transition = newTransition(
          start,
          end);
      transition->type = Transition::Chars;
      transition->range = range;
      return transition;
    }

    Transition* newEpsilon(State* start,
        State* end) {
      Transition* transition = newTransition(
          start, end);
      transition->type = Transition::Epsilon;
      return transition;
    }
    bool fullMatch(string input) {
      return dfsFullMatch(startState, input.c_str());
    }
    /* Simple dfs */
    bool dfsFullMatch(State* curState, const char *str) {
      if (curState->isFinal && *str == '\0') return true;
      if (*str == '\0') return false;
      for (int i = 0; i < curState->trans_out.size(); i++) {
        Transition* transition = curState->trans_out[i];
        switch (transition->type) {
          case Transition::Epsilon:
            if (dfsFullMatch(transition->target, str)) {
              return true;
            }
            break;
          case Transition::Chars:
            if (transition->range.contain(*str)) {
              if (dfsFullMatch(transition->target, str+1)) {
                return true;
              }
            }
            break;
        }
      }
      return false;
    }
};


class ParseException {};

class CharsetExpression: public Expression {
  public:
    std::vector<CharRange> ranges;
    virtual EpsilonNfa generateEpsilonNfa(
        Automaton* automaton) {
      EpsilonNfa nfa;
      nfa.start = automaton->newState();
      nfa.end = automaton->newState();
      for (int i = 0; i < ranges.size(); i++) {
        automaton->newChar(nfa.start, nfa.end, ranges[i]);
      }
      return nfa;
    }
};

class LoopExpression: public Expression {
  public:
    Expression* expression;
    LoopExpression() {}
    virtual EpsilonNfa generateEpsilonNfa(
        Automaton* automaton) {
      EpsilonNfa exp_nfa = expression->generateEpsilonNfa(automaton);
      EpsilonNfa nfa;
      nfa.start = automaton->newState();
      nfa.end = automaton->newState();
      // prefer long
      automaton->newEpsilon(nfa.start,
          exp_nfa.start);
      automaton->newEpsilon(exp_nfa.end,
          nfa.start);
      automaton->newEpsilon(nfa.start,
          nfa.end);
      return nfa;
    }
};

class SequenceExpression: public Expression {
  public:
    Expression *left;
    Expression *right;
    virtual EpsilonNfa generateEpsilonNfa(Automaton* automaton) {
      EpsilonNfa left_nfa = left->generateEpsilonNfa(automaton);
      EpsilonNfa right_nfa = right->generateEpsilonNfa(automaton);
      EpsilonNfa nfa;
      nfa.start = automaton->newState();
      nfa.end = automaton->newState();
      automaton->newEpsilon(nfa.start,
          left_nfa.start);
      automaton->newEpsilon(
          left_nfa.end, right_nfa.start);
      automaton->newEpsilon(
          right_nfa.end, nfa.end);
      return nfa;
    }
};

CharsetExpression* parseCharsetExpression(char *&input) {
  CharsetExpression* exp;
  switch (*input) {
    case '\0':
      exp = 0;
      break;
    case '*':
      throw ParseException();
    case '.':
      exp = new CharsetExpression();
      exp->ranges.push_back(CharRange(0, 255));
      input++;
      break;
    default:
      exp = new CharsetExpression();
      exp->ranges.push_back(CharRange(*input, *input));
      input++;
      break;
  }
  return exp;
}
LoopExpression* parseLoop(char *&input) {
  LoopExpression *exp;
  switch (*input) {
    case '*':
      exp = new LoopExpression();
      input++;
      break;
    default:
      exp = 0;
      break;
  }
  return exp;
}
Expression* parseUnit(char *&input) {
  Expression* unit = parseCharsetExpression(input);
  if (!unit) return 0;
  LoopExpression* loop;
  while ((loop=parseLoop(input))) {
    loop->expression = unit;
    unit = loop;
  }
  return unit;
}

Expression* parseSequenceExpression(char *&input) {
  Expression* exp = parseUnit(input);
  while (true) {
    Expression* right = parseUnit(input);
    if (!right) break;
    SequenceExpression* seq_exp = new SequenceExpression;
    seq_exp->left = exp;
    seq_exp->right = right;
    exp = seq_exp;
  }
  return exp;
}

Expression* parseRegex(string regex) {
  char *input = new char[regex.length()+1];
  char *begin = input;
  strcpy(input, regex.c_str());
  Expression* exp = parseSequenceExpression(begin);
  delete input;
  return exp;
}

template <typename ReturnType, typename ObjectType, typename ParameterType=void*>
class IF1 {
  public:
    virtual ReturnType invoke(ObjectType* object, ParameterType parameter) = 0;
};


template <typename ReturnType, typename ParameterType=void*>
class AutomatonGenerator: public IF1<ReturnType, Expression, ParameterType> {
};
                          


Automaton* generateEpsilonNfa(Expression *exp) {
  Automaton *automaton = new Automaton();
  EpsilonNfa nfa = exp->generateEpsilonNfa(automaton);
  automaton->startState = nfa.start;
  nfa.end->isFinal = true;
  return automaton;
}


template <class T>
int vecIndexOf(const vector<T> &vec, T val) {
  for (int i = 0;  i < vec.size(); i++) {
    if (vec[i] == val) return i;
  }
  return -1;
}

void printCharRange(const CharRange &range) {
  if (range.begin == 0 && range.end == 255) {
    cout << "[ANY]";
  } else {
    cout << "[" << range.begin << " - " << range.end << "]";
  }
}
void printAutomaton(Automaton* automaton) {
  char intbuf[100] = {0};

  for (int i = 0; i < automaton->states.size(); i++) {
    State* state = automaton->states[i];
    if (automaton->startState == state) {
      cout << "[START]";
    }
    if (state->isFinal) {
      cout << "[FINISH]";
    }
    cout << "State<" << i << ">" << endl;
    for (int j = 0; j < state->trans_out.size(); j++) {
      Transition* transition = state->trans_out[j];
      cout << "    To State<" << vecIndexOf(automaton->states, transition->target) << "> : ";

      switch (transition->type) {
        case Transition::Chars:
          cout << "<Char : ";
          printCharRange(transition->range);
          cout << endl;
          break;
        case Transition::Epsilon:
          cout << "<Epsilon>" << endl;
          break;
      }
    }
  }
}


bool isEpsilonTrans(Transition* transition) {
  return transition->type == Transition::Epsilon;
}
void collectEpsilonStates(State* source,
    std::unordered_set<State*> &epsilon_states,
    vector<Transition*> &trans_out) {
  epsilon_states.insert(source);
  for (int i = 0; i < source->trans_out.size(); i++) {
    Transition* transition = source->trans_out[i];
    if (isEpsilonTrans(transition)) {
      State* target = transition->target;
      if (epsilon_states.find(target) == epsilon_states.end()) {
        collectEpsilonStates(target, epsilon_states, trans_out);
      }
    } else {
      trans_out.push_back(transition);
    }
  }
}

Automaton* epsilonNfa2Nfa(Automaton *enfa) {
  Automaton* nfa = new Automaton;
  State* nfa_start = nfa->newState();
  nfa->startState = nfa_start;
  unordered_map<State*,State*> enfa_nfa;
  enfa_nfa.insert(std::pair<State*,State*>(enfa->startState,nfa_start));
  std::queue<State*> enfa_states_que;
  enfa_states_que.push(enfa->startState);
  while (!enfa_states_que.empty()) {
    State* source = enfa_states_que.front();
    State* nfa_source = enfa_nfa[source];
    enfa_states_que.pop();
    unordered_set<State*> epsilon_states;
    vector<Transition*> trans_out;
    collectEpsilonStates(source, epsilon_states, trans_out);
    for (unordered_set<State*>::const_iterator it = epsilon_states.begin();
        it != epsilon_states.end();
        it++) {
      if ((*it)->isFinal) {
        // cout << "here" << endl;
        nfa_source->isFinal = true;
        break;
      }
    }
    for (int i = 0; i < trans_out.size(); i++) {
      Transition* transition = trans_out[i];
      State* target = transition->target;
      State* nfa_target = NULL;
      if (enfa_nfa.find(target) == enfa_nfa.end()) {
        enfa_states_que.push(target);
        nfa_target = nfa->newState();
        enfa_nfa.insert(std::pair<State*,State*>(target, nfa_target));
      } else {
        nfa_target = enfa_nfa[target];
      }
      Transition* nfa_transition = nfa->newTransition(nfa_source, nfa_target);
      nfa_transition->copyInfo(transition);
    }
  }
  return nfa;
}


void clusterTransitions(const vector<Transition*> &transitions,
    map<Transition*, vector<Transition*>> &cluster) {
  for (int i = 0; i < transitions.size(); i++) {
    bool class_found = false;
    for (auto it = cluster.begin();
        it != cluster.end();
        it++) {
      if (Transition::sameClass(
            it->first,
            transitions[i])) {
        class_found = true;
        it->second.push_back(transitions[i]);
        break;
      }
    }
    if (!class_found) {
      cluster[transitions[i]] = {transitions[i]};
    }
  }
}


void collectTransTargets(const vector<Transition*> &transitions, vector<State*> &targets) {
  for (int i = 0; i < transitions.size(); i++) {
    targets.push_back(transitions[i]->target);
  }
}

Automaton* nfa2Dfa(Automaton* nfa) {
  Automaton* dfa = new Automaton;
  std::queue<State*> dfa_states_que;
  State* dfa_start = dfa->newState();
  dfa->startState = dfa_start;
  dfa_states_que.push(dfa_start);
  std::unordered_map<State*, vector<State*>> dfa_nfa;
  dfa_nfa[dfa_start] = {nfa->startState};
  if (nfa->startState->isFinal) dfa_start->isFinal = true;

  while (!dfa_states_que.empty()) {
    State* dfa_source = dfa_states_que.front();
    dfa_states_que.pop();
    vector<Transition*> nfa_trans_out;
    for (int i = 0; i < dfa_nfa[dfa_source].size(); i++) {
      State* nfa_state = dfa_nfa[dfa_source][i];

      nfa_trans_out.insert(nfa_trans_out.end(),
          nfa_state->trans_out.begin(),
          nfa_state->trans_out.end());
    }
    std::map<Transition*, vector<Transition*>> nfa_trans_clustered;
    clusterTransitions(nfa_trans_out, nfa_trans_clustered);

    for (auto cluster_it = nfa_trans_clustered.begin();
        cluster_it != nfa_trans_clustered.end();
        cluster_it++) {
      Transition *transition = cluster_it->first;
      vector<State*> targets;
      collectTransTargets(cluster_it->second, targets);
      std::sort(targets.begin(), targets.end());
      State* dfa_target = 0;
      for (auto dfa_nfa_it = dfa_nfa.begin(); dfa_nfa_it != dfa_nfa.end();
          dfa_nfa_it++) {
        if (dfa_nfa_it->second.size() == targets.size()) {
          bool equal_states = true;
          for (int i = 0; i < dfa_nfa_it->second.size(); i++) {
            if (dfa_nfa_it->second[i] != targets[i]) {
              equal_states = false;
              break;
            }
          }
          if (equal_states) {
            dfa_target = dfa_nfa_it->first;
            break;
          }
        }
      }
      if (!dfa_target) {
        dfa_target = dfa->newState();
        dfa_nfa[dfa_target] = targets;
        dfa_states_que.push(dfa_target);
      }
      for (int i = 0; i < targets.size(); i++) {
        if (targets[i]->isFinal) {
          dfa_target->isFinal = true;
          break;
        }
      }
      Transition *dfa_trans = dfa->newTransition(dfa_source, dfa_target);
      dfa_trans->copyInfo(transition);
    }
  }
  return dfa;
}

class Solution {
  public:
    bool isMatch(string s, string p) {
      Expression* expression = parseRegex(p);
      Automaton* enfa = generateEpsilonNfa(expression);
      Automaton* nfa = epsilonNfa2Nfa(enfa);
      Automaton* dfa = nfa2Dfa(nfa);
      return dfa->fullMatch(s);
    }
};

void test() {
  Expression* expression = parseRegex(".*c");
  Automaton* enfa = generateEpsilonNfa(expression);
  cout << "epsilon nfa------------------" << endl;
  printAutomaton(enfa);
  Automaton* nfa = epsilonNfa2Nfa(enfa);
  cout << "nfa--------------------------" << endl;
  printAutomaton(nfa);
  Automaton* dfa = nfa2Dfa(nfa);
  cout << "dfa--------------------------" << endl;
  printAutomaton(dfa);
  cout << "Match ... " << endl;
  cout << dfa->fullMatch("bc") << endl;
}

int main() {
  Solution sol;
  assert(sol.isMatch("aa", "a") == false);
  assert(sol.isMatch("aa", "aa") == true);
  assert(sol.isMatch("aaa", "aa") == false);
  assert(sol.isMatch("aa", "a*") == true);
  assert(sol.isMatch("aa", ".*") == true);
  assert(sol.isMatch("ab", ".*") == true);
  assert(sol.isMatch("bc", ".*c") == true);
  assert(sol.isMatch("aab", "c*a*b") == true);
  assert(sol.isMatch("abbc", "ab*bbc") == true);
  assert(sol.isMatch("abcbcd", "a.*c.*d") == true);
  assert(sol.isMatch("a", "ab*") == true);

  // test();

  return 0;
}
