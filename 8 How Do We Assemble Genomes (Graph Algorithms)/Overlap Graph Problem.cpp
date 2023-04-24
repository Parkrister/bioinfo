#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;


int main() {
    // put your code here
    vector<string> vs;
    string s;
    while(cin >> s)
        vs.push_back(s);
    map<string, vector<string>> res;
    
    for(string e: vs){ // обходим каждую вершину графа
        for(string edge : vs)
            if( e != edge && (e.substr(1, e.length()) == edge.substr(0, edge.length() - 1)) )
                res[e].push_back(edge);
    }
    for(string s : vs){
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