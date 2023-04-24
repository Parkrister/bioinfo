#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
using namespace std;

vector<string> Composition(int k, string s){ // разбиваем строку на k-меры
    vector<string> res;
    for(int i = 0; i < s.length() - k + 1; i++){
        res.push_back(s.substr(i, k));
    }
    return res;
}

vector<string> Unic(vector<string> vs){ // находим уникальные k-1 меры
    vector<string> res;
    string pref, postf;
    for(string s : vs){
        pref = s.substr(0, s.size() -1 );
        postf = s.substr(1, s.size());
        for( string sf : {pref, postf} ){
            bool s_in_res = false;
            for(string ss : res)
                if(sf == ss){
                    s_in_res = true;
                    break;
                }
            if(!s_in_res)
                res.push_back(sf);
        }
    }
    return res;
}

map<string, vector<string>> De_Bruijn_Graph(vector<string> vs, vector<string> uvs){
    map<string, vector<string>> res;
    for(string e: uvs){
        for(string edge : vs){
            if(e == edge.substr(0, e.size()))
               res[e].push_back(edge.substr(1, e.size()));
        }
    }
    return res;
}

////


int main() {
    // put your code here
    int k;
    string s;
    cin >> k >> s;
    vector<string> vs = Composition(k, s);
    vector<string> uvs = Unic(vs);
    map<string, vector<string>> res = De_Bruijn_Graph(vs, uvs);

    for(string s : uvs){
        if(res[s].size()){
            cout << s << " -> ";
            int i = 0;
            for(; i < res[s].size() - 1; i++){
                cout << res[s][i] << ',';
            }
            cout << res[s][i];
            cout << '\n';
        }
    }
    

    return 0;
}