#include <string>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int *f;

void enter() {
    cin.sync(); cin.clear();
}

void gen_ff(const string& target) {
    int t_len = (int)target.length();
    memset(f, 0, sizeof(int) * t_len);

    for(int len = 2; len <= t_len; len++) { //len -> length of substring
        string part = target.substr(0, len);
        //cout << "Substring " << len << ':' << part << '\n';

        int maxi = 0;

        for(int i = 1; i < len; i++) { //i -> length of prefix & postfix
            if(part.substr(0, i) == part.substr(len - i, i) && (i > maxi)) {
                maxi = i;
            }
        }

        f[len - 1] = maxi;
    }
}

int find_index(const string& text, const string& target) {
    int start_idx = 0, start_i = 0;
    int text_len = (int)text.length();
    int target_len = (int)target.length();

    int result = -1;
    int idx = start_idx;
    int i = start_i;

    while(idx != text_len) {
        //cout << "idx: " << idx << " -> i: " << i << '\n';
        if(text[idx] == target[i]) { //if 1 character matches
            idx++;
            i++;
        } else { //if not match
            if(i > 0) {
                start_idx += (i - f[i - 1]);
                start_i = f[i - 1];
            } else {
                start_idx++;
                start_i = 0;
            }
            idx = start_idx;
            i = start_i;
        }

        if(i == target_len) { //found the whole match!
            result = idx - target_len;
            break;
        }
    }
    return result;
}

int main() {
    string text;
    getline(cin, text); enter();

    string target;
    getline(cin, target); enter();

    int t_len = (int)target.length();
    f = new int[t_len];
    gen_ff(target);

    cout << find_index(text, target);
}
