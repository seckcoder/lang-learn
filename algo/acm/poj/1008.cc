#include <string>
#include <map>
#include <iostream>
#include <vector>


using namespace std;


map<string, int> MONTH_MAP;

static const char *TZ_DAYNAME_MAP[20] = {
  "imix",
  "ik",
  "akbal",
  "kan", 
  "chicchan",
  "cimi", 
  "manik",
  "lamat",
  "muluk", 
  "ok", 
  "chuen", 
  "eb",
  "ben",
  "ix",
  "mem",
  "cib", 
  "caban", 
  "eznab", 
  "canac", 
  "ahau"
};

void initMonthMap() {
  const char *months[19] = {
    "pop",
    "no", "zip", "zotz", "tzec",
    "xul", "yoxkin", "mol", "chen", "yax", "zac", "ceh", "mac", "kankin",
    "muan", "pax", "koyab", "cumhu", "uayet"};
  for(int i = 0; i < 19; i++) {
    MONTH_MAP[string(months[i])] = i;
  }
}

void SplitString(const string &s, char c,
                 vector<string> &str_vec) {
  string tmp;
  str_vec.clear();
  for(int i = 0; i < s.length(); i++) {
    if (s[i] == c) {
      str_vec.push_back(tmp);
      tmp.clear();
    } else {
      tmp.push_back(s[i]);
    }
  }
}

class Haab {
 public:
  int d; // >=0
  int m; // [0 - 18]
  int y; // >=0 
  Haab(const string &s) {
    vector<string> str_vec;
    SplitString(s, ' ', str_vec);
    d = atoi(str_vec[0].substr(0, str_vec[0].length() - 1).c_str());
    m = MONTH_MAP[str_vec[1]];
    y = atoi(str_vec[2].c_str());
  }
  Haab(int nd, const string &month_name, int ny) {
    d = nd;
    y = ny;
    m = MONTH_MAP[month_name];
  }
  Haab(int hd, int hm, int hy) {
    d = hd;
    m = hm;
    y = hy;
  }
  int getEpochDays() const {
    int days_from_year = y * 365;
    int days_from_month = m * 20;
    int days_from_day = d + 1;
    return days_from_year + days_from_month + days_from_day;
  }
};

class Tzolkin {
 public:
  int d; // from 0
  int y; // from 1
  int n; // from 1
  void fromEpochDays(int ndays) {
    // ndays >= 1
    y = (ndays-1) / 260;
    int ndays_in_ayear = (ndays-1) % 260;
    d = ndays_in_ayear % 20;
    n = ndays_in_ayear % 13 + 1;
  }
  friend ostream& operator<<(ostream &os, const Tzolkin &tz);
  const char *nameOfDay() const {
    return TZ_DAYNAME_MAP[d];
  }
};
ostream& operator<<(ostream &os, const Tzolkin &tz) {
  os << tz.n << " " << tz.nameOfDay() << " " << tz.y;
  return os;
}


int main(int argc, const char *argv[])
{
  int t;
  cin >> t;
  initMonthMap();
  vector<Tzolkin> tz_vec;
  for(int i = 1; i <= t; i++) {
    int nd;
    cin >> nd;
    string tmp;
    cin >> tmp;
    string month_name;
    cin >> month_name;
    int ny;
    cin >> ny;
    //cout << nd << " " << month_name << " " << ny << endl;
    Haab haab(nd, month_name, ny);
    //cout << haab.getEpochDays() << endl;
    Tzolkin tz;
    tz.fromEpochDays(haab.getEpochDays());
    tz_vec.push_back(tz);
  }
  cout << t << endl;
  for(int i = 0; i < t; i++) {
    cout << tz_vec[i] << endl;
  }
  return 0;
}
