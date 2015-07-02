
// 
// abc
// def
// Global state.

// 


// interested in frontend/backend?
//


// javascript.


// what you think is a big challenge?


// hacker rank link. codepair

// alphabetic ordering

// Don't quite get it. Where does the t come from?
//
// What about r in gyro? Why?
// The order is surely to be right? Is it possible to have a case where
// we can't get a right order?


// Basic idea:
//
// We will use graph to solve this problem. Basic idea is 
// to maintain a graph which denotes the ordering and do a topological sort on it.
//
// Everytime, we compare the current string with the previous string just next to
// it. If we find a different character, we know this is key character that decides
// the order between these two strings.
//
// At that time, we will get the two different characters and construct an edge
// from these two characters. After the completion of the graph, we do a top sort
// on it.
//


// will all chars be ASCII chars? So <= 255
//
#include "graph.h"

static int time_stamp = 0;

template<class OnFinished>
void DFS(Graph &g, OnFinished &on_finished) {
  for (int i = 0; i < g.v.size(); i++) {
    g.v[i].color = COLOR_WHITE;
    g.v[i].pi = -1;
  }
  time_stamp = 0;
  for (int u = 0; u < g.v.size(); u++) {
    if (g.v[u].color == COLOR_WHITE) {
      DFSVisit(g, u, on_finished);
    }
  }
}

template<class OnFinished>
void DFSVisit(Graph &g, int u, OnFinished &on_finished) {
  time_stamp += 1;
  g.v[u].d = time_stamp;
  g.v[u].color = COLOR_GRAY;
  for (int i = 0; i < g.e[u].size(); i++) {
    int v = g.e[u][i];
    if (g.v[v].color == COLOR_WHITE) {
      g.v[v].pi = u;
      DFSVisit(g, v, on_finished);
    }
  }
  on_finished(u);
  g.v[u].color = COLOR_BLACK;
  time_stamp += 1;
  g.v[u].f = time_stamp;
}


class OnFinishedOp {
 public:
  OnFinishedOp(vector<int> &vec):sorted_vtx(vec){
    sorted_vtx.clear();
  }
  void operator()(int u) {
    sorted_vtx.push_back(u);
  }
 private:
  vector<int> &sorted_vtx;
};

void TopSort(Graph &g,
             vector<int> &sorted_vtx) {
  OnFinishedOp on_finished(sorted_vtx);
  DFS(g, on_finished);
  std::reverse(sorted_vtx.begin(),
               sorted_vtx.end());

}


// just copy the following code
// --------- 

class OnFinishedOp {
 public:
  OnFinishedOp(vector<int> &vec):sorted_vtx(vec){
    sorted_vtx.clear();
  }
  void operator()(int u) {
    sorted_vtx.push_back(u);
  }
 private:
  vector<int> &sorted_vtx;
};



void dfs

#define M 255
void topsort(bool graph[][M],
    vector<char> &sorted_vtx) {
  OnFinishedOp on_finished(sorted_vtx);
  dfs(graph, on_finished);
}

vector<char> ordering(const vector<string> &input_strs) {
  bool graph[M][M];

  // reset the graph
  memset(graph, false, sizeof(graph));
  // construct a graph from input_strs

  // Following code will construct a graph
  for (int i = 1; i < input_strs.size(); i++) {
    string prev_str = input_strs[0];
    string cur_str = input_strs[1];
    std::pair<char, char> two_chars = findTwoDifferent(prev_str, cur_str);
    // add one edge
    // 快点..........
    graph[two_chars.first][two_chars.second] = true;
  }
  // for input string, we compare it with previous string and find
  // two chars that are differnt. Can we can construct an edge from
  // these two chars, which denotes an ordering between these two chars.
  //
  // Based on this, we can construct a graph. And then do a top sort.
  // Top sort generally construct a relative ordering based on the graph.
  //
  // Its basic idea is depth-first-search. After the depth first search,
  // it will construct a relationship. For every depth-firtst search,
  // on finished, we can add the current finished vertex to the vector.
  // This is a topological sorted vector. If you go to Introduction to algorithm,
  // the chapter on topogical sort is based on depth first search.
  // After the end of top sort, we get an ordering of the characters.
  // 
  // If a character is in front of another character, I mean in the graph ordering,
  // wethere is an order between these two chars.
  //
  // Yes, you are right.
  // No, we can also get a > b > d > f > c > e
  //
  // Large file, billions of words.
  //
  // Use mapreduce.
  //
  // We can first get the ordering with this method for a small trunk of file.
  // 
  // After that, I will merge the order in reduce or "another round of of mapreduce
  // procedure."
  //
  //
  // The input to the map step is a vector of strings.
  // The output of the map is the ordering of these vector of strings.
  //
  // This will generate a large number of files with ordering.
  // No, No, no. It will not.
  //
  // In reduce, I merge all characters generated in map step.
  // The input to the reduce procedure, is a list of list of characters. 
  // 
  // Then we can merge the list of list of characters into a new list of characters, which
  // is ordered.
  //
  // No we will not generate 100 reduce procedures. 
  //
  // After the map step, we only generate a vector of characters. This is very small
  // compared with the input file.
  //
  // So in the reduce procedure, I can merge the much smaller vector of characters.
  //
  // What do you mean by multiple merge?
  // 
  // The input to a reduce procedure is already an ordered chars.
  //
  // Yes, you are right.


  topsort(graph, vector<char> &sorted_vtx);
}




// --------

// Third round
//
//
// 
//

// Twitter Advertisement.
//
// Machine learning and statistics. System engineering.

// Internships.


// Main challenge facing in the project.

// Internships.

// What you find most interesting/challenging in twitter?
//
// Maybe more specific?
// Is he a data scientist? Seems he hasn't mentioned it. I think he is just
// a data engineer.
//
// Backend projects.
//
// What you wish to be different.
//
// 



