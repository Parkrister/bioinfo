#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include "stdlib.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    // put your code here
    int k;
    string s;
    cin >> k >> s;
    vector<string> res;
    for(int i = 0; i < s.length() - k + 1; i++){
        res.push_back(s.substr(i, k));
    }
    for(auto s : res){
        cout << s << '\n';
    }
    return 0;
}