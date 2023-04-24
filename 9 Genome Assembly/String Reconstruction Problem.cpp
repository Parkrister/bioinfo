#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;

struct edge {
    string v; // next v
    bool visit;
};

struct deg {
    int in;
    int out;
};

map<string, vector<edge>> graph;
size_t edgeNum = 0;

//--------------------------------------------------------//
string String_Spelled(vector<string> vs) {
    string res;
    for (string s : vs) {
        res += s[s.size() - 1];
    }
    res.insert(0, vs[0].substr(0, vs[0].size() - 1));
    return res;
}

//----------------Eulerian Cycle---------------------------//
vector<string> Cycle(string v0) {
    vector<string> cycle;
    cycle.push_back(v0);

    string v1;
    int i;
    for (i = 0; i < graph[v0].size() && graph[v0][i].visit; i++);
    graph[v0][i].visit = true;
    v1 = graph[v0][i].v;

    while (v1 != v0) {
        for (i = 0; i < graph[v1].size() && graph[v1][i].visit; i++);
        cycle.push_back(v1);
        graph[v1][i].visit = true;
        v1 = graph[v1][i].v;
    }
    cycle.push_back(v1);
    return cycle;
}

int newV(vector<string> cycle) { // найти в цикле индекс вершины с непосещенными ребрами
    for (int i = 0; i < cycle.size(); i++)
        for (auto vv : graph[cycle[i]])
            if (!vv.visit)
                return i;
    return -1;
}

vector<string> Eulerian_Cycle(string v0) {
    vector<string> cycle = Cycle(v0); // создать первый цикл  
    while (cycle.size() != edgeNum + 1) {
        int iv0 = newV(cycle);
        vector<string> cycle2 = Cycle(cycle[iv0]);
        cycle.insert(cycle.begin() + iv0, cycle2.begin(), cycle2.end() - 1);
    }
    return cycle;
}

vector<string> Unic(vector<string> vs) { // находим уникальные k-1 меры
    vector<string> res;
    string pref, postf;
    for (string s : vs) {
        pref = s.substr(0, s.size() - 1);
        postf = s.substr(1, s.size());
        for (string sf : {pref, postf}) {
            bool s_in_res = false;
            for (string ss : res)
                if (sf == ss) {
                    s_in_res = true;
                    break;
                }
            if (!s_in_res)
                res.push_back(sf);
        }
    }
    return res;
}

map<string, vector<edge>> De_Bruijn_Graph(vector<string> vs, vector<string> uvs, map<string, deg>& degrees) {
    map<string, vector<edge>> res;
    for (string e : uvs) {
        for (string edge : vs) {
            if (e == edge.substr(0, e.size())) {
                res[e].push_back({ edge.substr(1, e.size()), false });
                edgeNum++;
                degrees[e].out++; degrees[edge.substr(1, e.size())].in++;
            }
        }
    }
    return res;
}

//----------------String Reconstruction-------------------//
string String_Reconstruction(int k, vector<string> vs) {
    string str;
    map<string, deg> degrees = {};
    graph = De_Bruijn_Graph(vs, Unic(vs), degrees);
    
    vector<string> vv; // начальные вершина для эйлерова пути
    for (auto d : degrees) {
        if (d.second.in != d.second.out)
            vv.push_back(d.first);
    }

    string vin, vout;
    if (degrees[vv[0]].out < degrees[vv[0]].in) {
        vout = vv[1];
        vin = vv[0];
    }
    else {
        vout = vv[0];
        vin = vv[1];
    }
    
    graph[vin].push_back({ vout, false }); // добавляем в граф ребро
    edgeNum++;

    vector<string> cycle = Eulerian_Cycle(vout);
    cycle.pop_back();
    str = String_Spelled(cycle);
    return str;
}


//---------------------Main----------------------------//
int main() {
    // put your code here
    //int k = 4;
    //vector<string> vs = { "CTTA" , "ACCA", "TACC", "GGCT", "GCTT", "TTAC" };
    int k;
    vector<string> vs;
    cin >> k;
    string s;
    while (cin >> s)
        vs.push_back(s);

    string res = String_Reconstruction(k, vs);
    cout << res;

    return 0;
}