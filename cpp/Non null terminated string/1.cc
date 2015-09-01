
#include "../base.h"

int main() {
    string s("aa\0b",4);
    cout << s << " " << s.length() << endl;
    for (int i = 0; i < s.size(); i++) {
        cout << s[i] << endl;
    }
    return 0;
}

