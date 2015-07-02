


#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <map>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

enum ContentType {CONTENT_USER = 0, CONTENT_TOPIC, CONTENT_QUESTION,
  CONTENT_BOARD, CONTENT_OTHER};


template <class T>
void debugVec(const vector<T> &vec) {
  for (int i = 0; i < vec.size(); i++) {
    cout << vec[i] << " ";
  }
  cout << endl;
}



inline bool isDigit(char c) {
  return c >= '0' && c <= '9';
}

void split(const string &line, char delimiter, vector<string> &res_strs) {
  stringstream stream(line);
  string one_word;
  while (getline(stream, one_word, delimiter)) {
    if (!one_word.empty()) res_strs.push_back(one_word);
  }
}

inline char toLower(char c) {
  if (c >= 'A' && c <= 'Z') {
    return (c - 'A') + 'a';
  }
  return c;
}
// convert line to lower case
void toLower(string &line) {
  for (int i = 0; i < line.length(); i++) {
    line[i] = toLower(line[i]);
  }
}

inline ContentType recognizeContentType(const string &type_s) {
  if (type_s == "user") {
    return CONTENT_USER;
  } else if (type_s == "topic") {
    return CONTENT_TOPIC;
  } else if (type_s == "question") {
    return CONTENT_QUESTION;
  } else if (type_s == "board") {
    return CONTENT_BOARD;
  } else {
    return CONTENT_OTHER;
  }
}

class Content {
  public:
    ContentType type;
    //string type;
    string id;
    float score;
    vector<string> tokens;
    int time;
    void parse(istream &is) {
      string type_s;
      is >> type_s >> id >> score;
      type = recognizeContentType(type_s);
      tokens.clear();
      string data_str;
      std::getline(is, data_str);
      toLower(data_str);
      split(data_str, ' ', tokens);
    }
    void copyCompareInfo(const Content &c) {
      type = c.type;
      id = c.id;
      score = c.score;
      time = c.time;
    }
};


class Boost {
  public:
    ContentType type;
    string id;
    float boost;
    void parse(istream &is) {
      is >> std::ws;
      std::getline(is, id, ':');
      type = recognizeContentType(id);
      is >> boost;
    }
};


class Node {
  public:
    typedef map<char, Node *> BranchMap;
    bool empty() const {
      // no ids and no branches
      return ids.empty() && branches.empty();
    }
    void insert(const string &data, const string &id) {
      insertRec(data, 0, id);
    }
    void insertRec(const string &data, int cur, const string &id) {
      ids.insert(id);
      if (cur >= data.length()) {
        return;
      }
      if (data == "uneonclofpu") {
        cout << "bravo" << endl;
      }

      BranchMap::iterator it = branches.find(data[cur]);
      if (it == branches.end()) {
        Node *pn = new Node();
        branches.insert(std::pair<char, Node*>(data[cur], pn));
        pn->insertRec(data, cur+1, id);
      } else {
        it->second->insertRec(data, cur+1, id);
      }
    }
    void remove(const string &data, const string &id) {
      removeRec(data, 0, id);
    }
    void removeRec(const string &data, int cur, const string &id) {
      ids.erase(id);
      if (cur >= data.length()) {
        return ;
      }
      Node *pn = branches.find(data[cur])->second;
      pn->removeRec(data, cur+1, id);
      // delete when empty
      if (pn->empty()) {
        delete pn;
      }
    }
    // given a query return a matching node
    Node *query(const string &query) const {
      return queryRec(query, 0);
    }
    Node *queryRec(const string &query, int cur) const {
      BranchMap::const_iterator const_it = branches.find(query[cur]);
      if (const_it == branches.end()) {
        return NULL;
      }
      Node *pn = const_it->second;
      if (cur == query.length() - 1) {
        // if cur is last character, return the matching node.
        return pn;
      } else {
        return pn->queryRec(query, cur+1);
      }
    }
    
    set<string> ids;

  private:
    BranchMap branches;
};


class Trie {
  public:
    Trie() : _timer(0) {}
    Node root;
    typedef map<string, Content> ContentMap;
    ContentMap content_map;
    void add(const Content &content) {
      if (content_map.find(content.id) != content_map.end()) return;
      content_map[content.id] = content;
      content_map[content.id].time = _timer;
      _timer += 1;
      for (int i = 0; i < content.tokens.size(); i++) {
        cout << "adding ...  " << content.tokens[i] << " " << endl;
        root.insert(content.tokens[i], content.id);
      }
    }
    void del(const string &id) {
      if (content_map.find(id) == content_map.end()) return;
      Content &content = content_map[id];
      for (int i = 0; i < content.tokens.size(); i++) {
        root.remove(content.tokens[i], content.id);
      }
      content_map.erase(id);
    }
    // given a query, return the node that match the query
    Node *query(const string &query) const {
      assert(!query.empty());
      return root.query(query);
    }

    // given tokens, return ids that match the query tokens
    void query(const vector<string> &tokens, vector<string> &query_ids) const {
      vector<Node *> nodes;

      // get all matching nodes for given query
      for (int i = 0; i < tokens.size(); i++) {
        Node *pn = query(tokens[i]);
        if (!pn) return; // can't find node for the token, directly break
        nodes.push_back(pn);
      }
      assert(!nodes.empty());

      query_ids.clear();
      Node *pn0 = nodes[0];
      for (set<string>::const_iterator const_it0 = pn0->ids.begin();
          const_it0 != pn0->ids.end();
          const_it0++) {
        bool match_for_all = true;
        for (int i = 1; i < nodes.size(); i++) {
          Node *pni = nodes[i];
          if (pni->ids.find(*const_it0) == pni->ids.end()) {
            // no match for pni
            match_for_all = false;
            break;
          }
        }
        if (match_for_all) query_ids.push_back(*const_it0);
      }

      sortQueryIds(query_ids, compContentMapIter);
    }

    static bool compContentMapIter(
        const ContentMap::const_iterator it1,
        const ContentMap::const_iterator it2) {
      const Content &content1 = it1->second;
      const Content &content2 = it2->second;
      return compContent(content1, content2);
    }

    static bool compContent(
        const Content &content1,
        const Content &content2) {
      if (content1.score > content2.score) return true;
      else if (content1.score < content2.score) return false;
      else if (content1.time > content2.time) return true;
      else if (content1.time < content2.time) return false;
      else return true;
    }

    // sort query ids according to content map info
    template <class Compare>
    void sortQueryIds(vector<string> &query_ids, Compare comp) const {
      vector<ContentMap::const_iterator> query_infos(query_ids.size());
      for (int i = 0; i < query_ids.size(); i++) {
        query_infos[i] = content_map.find(query_ids[i]);
      }
      std::sort(query_infos.begin(), query_infos.end(), comp);
      for (int i = 0; i < query_infos.size(); i++) {
        query_ids[i] = query_infos[i]->second.id;
      }
    }

    template <class Compare>
    void sortQueryIdsBoosted(const vector<Boost> &boosts,
        vector<string> &query_ids,
        Compare comp) const {
      vector<Content> query_infos(query_ids.size());
      for (int i = 0; i < query_ids.size(); i++) {
        query_infos[i].copyCompareInfo(content_map.find(query_ids[i])->second);
        //query_infos[i] = content_map.find(query_ids[i])->second;
        Content &content = query_infos[i];
        for (int j = 0; j < boosts.size(); j++) {
          switch (boosts[j].type) {
            case CONTENT_OTHER:
              if (content.id == boosts[j].id) {
                content.score *= boosts[j].boost;
              }
              break;
            default:
              if (content.type == boosts[j].type) {
                content.score *= boosts[j].boost;
              }
              break;
          }
        }
      }
      std::sort(query_infos.begin(), query_infos.end(), comp);
      for (int i = 0; i < query_infos.size(); i++) {
        query_ids[i] = query_infos[i].id;
      }
    }
    void wquery(const vector<string> &tokens,
        const vector<Boost> &boosts, vector<string> &res_ids) const {
      query(tokens, res_ids);
      sortQueryIdsBoosted(boosts, res_ids, compContent);
    }

  private:
    int _timer;
};


class CommandBase {
  public:
    virtual void parse(istream &is) = 0;
};

class CommandAdd : public CommandBase {
  public:
    Content content;
    void parse(istream &is) {
      content.parse(is);
    }
};

class CommandQuery: public CommandBase {
  public:
    int num_res;
    vector<string> tokens;
    virtual void parse(istream &is) {
      tokens.clear();
      is >> num_res;
      string query;
      std::getline(is, query);
      toLower(query);
      split(query, ' ', tokens);
    }
};

class CommandDel: public CommandBase {
  public:
    string id;
    virtual void parse(istream &is) {
      is >> id;
    }
};


class CommandWQuery: public CommandBase {
  public:
    vector<Boost> boosts;
    int num_res;
    vector<string> tokens;
    virtual void parse(istream &is) {
      int num_boost;
      is >> num_res >> num_boost;
      if (num_boost > 0) {
        boosts.resize(num_boost);
        for (int i = 0; i < num_boost; i++) {
          boosts[i].parse(is);
        }
      }
      string query;
      std::getline(is, query);
      toLower(query);
      split(query, ' ', tokens);
    }
};


void execute(
    const CommandAdd &cmd_add, Trie &trie) {
  if (cmd_add.content.tokens.size() > 0) trie.add(cmd_add.content);
}
void execute(
    const CommandDel &cmd_del, Trie &trie) {
  trie.del(cmd_del.id);
}
void execute(
    const CommandQuery &cmd_query, const Trie &trie) {
  vector<string> ids;
  if (cmd_query.tokens.size() > 0) {
    trie.query(cmd_query.tokens, ids);
  }
  /* if (ids.size() > 0 && cmd_query.num_res > 0) { */
  /*   printf("%s", ids[0].c_str()); */
  /*   for (int i = 1; i < ids.size() && i < cmd_query.num_res; i++) { */
  /*     printf(" %s", ids[i].c_str()); */
  /*   } */
  /* } */
  /* printf("\n"); */
}

void execute(
    const CommandWQuery &cmd_wquery, const Trie &trie) {
  vector<string> ids;
  if (cmd_wquery.tokens.size() > 0) {
      trie.wquery(cmd_wquery.tokens, cmd_wquery.boosts, ids);
  }
  /* if (ids.size() > 0 && cmd_wquery.num_res > 0) { */
  /*   printf("%s", ids[0].c_str()); */
  /*   for (int i = 1; i < ids.size() && i < cmd_wquery.num_res; i++) { */
  /*     printf(" %s", ids[i].c_str()); */
  /*   } */
  /* } */
  /* printf("\n"); */
}

ostream& operator<<(ostream &os, const CommandAdd &cmd) {
  os << "add " << cmd.content.type << " " << cmd.content.id <<
    " " << cmd.content.score << " ";
  for (int i = 0; i < cmd.content.tokens.size(); i++) {
    os << cmd.content.tokens[i] << " ";
  }
  return os;
}
ostream& operator<<(ostream &os, const CommandDel &cmd) {
  os << "del " << cmd.id << endl;
  return os;
}
ostream& operator<<(ostream &os, const CommandQuery &cmd) {
  os << "query ";
  for (int i = 0; i < cmd.tokens.size(); i++) {
    os << cmd.tokens[i] << " ";
  }
  os << endl;
  return os;
}
ostream& operator<<(ostream &os, const CommandWQuery &cmd) {
  os << "wquery ";
  for (int i = 0; i < cmd.tokens.size(); i++) {
    os << cmd.tokens[i] << " ";
  }
  os << endl;
  return os;
}
int main() {
  int cmd_num;
  Trie trie;
  // cin >> cmd_num;
  ifstream ifs("small_sample.txt", std::ifstream::in);
  ifs >> cmd_num;
  for (int i = 1; i <= cmd_num; i++) {
    string type;
    ifs >> type;
    cout << type << endl;
    if (type == "ADD") {
      CommandAdd cmd;
      cmd.parse(ifs);
      cout << i << " " << cmd << endl;
      execute(cmd, trie);
    } else if (type == "DEL") {
      CommandDel cmd;
      cmd.parse(ifs);
      cout << i << " " << cmd << endl;
      execute(cmd, trie);
    } else if (type == "QUERY") {
      CommandQuery cmd;
      cmd.parse(ifs);
      cout << i << " " << cmd << endl;
      execute(cmd, trie);
    } else if (type == "WQUERY") {
      CommandWQuery cmd;
      cmd.parse(ifs);
      cout << i << " " << cmd << endl;
      execute(cmd, trie);
    }
  }
  ifs.close();
  return 0;
}
