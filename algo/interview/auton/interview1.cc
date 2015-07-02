

void dfs(bool graph[][M], vector<char> &ordered_vtx) {
}

void topsort(bool graph[][M], vector<char> &ordered_vtx) {
  dfs(graph, ordered_vtx);
}

vector<char> ordering(const vector<string> &input_strs) {

  bool graph[M][M];
  memset(graph, false, sizeof(graph));

  for (int i = 0; i < input_strs.size(); i++) {
    std::pair<char, char> two_chars = findTwoDifferent(prev_str, cur_str);
    graph[two_chars.first][two_chars.second] = true;
  }

  vector<char> ordered_vtx;
  topsort(graph, ordered_vtx);
}




// que1: all chars in it unique?
// python
//

def permute(self, str):

