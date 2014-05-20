#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class DNA {
 public:
  string dna;
  unsigned int inv_pairs;
  void calcInvPairs() {
    string tmp_s = dna;
    inv_pairs = _calc_inv_pairs(tmp_s, 0, dna.length() - 1);
    //cout << tmp_s << endl;
  }
  int _calc_inv_pairs(string &s, int p, int r) {
    if (p < r) {
      int q = (p + r) >> 1;
      int left = _calc_inv_pairs(s, p, q);
      int right = _calc_inv_pairs(s, q+1, r);
      int cross = 0;
      int i, j;
      string tmp(r-p+1, 'a');
      int k = 0;
      for(i = p, j = q+1; i <= q && j <= r;) {
        if (s[i] > s[j]) {
          tmp[k] = s[i];
          k+=1;
          cross += (r - j + 1);
          i += 1;
        } else {
          tmp[k] = s[j];
          k+=1;
          j += 1;
        }
      }
      while (i <= q) {
        tmp[k] = s[i];
        k+=1;
        i+=1;
      }
      while (j <= r) {
        tmp[k] = s[j];
        k+=1;
        j+=1;
      }
      for(int i = p; i <= r; i++) {
        s[i] = tmp[i-p];
      }
      return left + right + cross;
    } else {
      return 0;
    }
  }
};

ostream &operator<<(ostream &os, const DNA &dna) {
  os << dna.dna;
  return os;
}

bool DNACmp(const DNA &dna1, const DNA &dna2) {
  return dna1.inv_pairs < dna2.inv_pairs;
}


template <class T>
void printVec(const vector<T> &vec) {
  for(int i = 0; i < vec.size(); i++) {
    cout << vec[i] << endl;
  }
}

void DNASort(vector<DNA> &dna_vec) {
  for(int i = 0 ; i < dna_vec.size(); i++) {
    dna_vec[i].calcInvPairs();
    //cout << dna_vec[i].inv_pairs << endl;
  }
  sort(dna_vec.begin(), dna_vec.end(), DNACmp);
  printVec(dna_vec);
}

int main(int argc, const char *argv[])
{
  int n, m;
  cin >> n >> m;
  vector<DNA> dna_vec(m);
  for(int i = 0; i < m; i++) {
    cin >> dna_vec[i].dna;
    //cout << dna_vec[i].dna << " " << dna_vec[i].dna.length() << endl;
  }
  DNASort(dna_vec);
  return 0;
}
