#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
using namespace std;

string String_Spelled(vector<string> vs){
    string res;
    for(string s : vs){
        res += s[s.size() -1];
    }
    res.insert(0, vs[0].substr(0, vs[0].size() - 1));
    return res;
}

int main() {
    // put your code here
    vector<string> vs;
    string s;
    while(cin >> s)
        vs.push_back(s);
    s = String_Spelled(vs);
    cout << s;
    return 0;
}