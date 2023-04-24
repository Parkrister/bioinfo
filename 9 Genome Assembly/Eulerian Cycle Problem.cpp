#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <sstream>
using namespace std;

struct edge {
    int v; // next v
    bool visit;
};

map<int, vector<edge>> graph;
size_t edgeNum = 0;

void replace(string& s, char c1, char c2) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == c1)
            s[i] = c2;
    }
}

vector<int> Cycle(int v0) {
    vector<int> cycle;
    cycle.push_back(v0);

    int v1;
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

int newV(vector<int> cycle) { // найти в цикле индекс вершины с непосещенными ребрами
    for (int i = 0; i < cycle.size(); i++)
        for (auto vv : graph[cycle[i]])
            if (!vv.visit)
                return i;
    return -1;
}

vector<int> Eulerian_Cycle() {
    int v0;
    for (auto e : graph) { // выбираем первую вершину в графе
        v0 = e.first;
        break;
    }
    vector<int> cycle = Cycle(v0); // создать первый цикл  
    while (cycle.size() != edgeNum + 1) {
        int iv0 = newV(cycle);
        vector<int> cycle2 = Cycle(cycle[iv0]);
        cycle.insert(cycle.begin() + iv0, cycle2.begin(), cycle2.end() - 1);
        //...//   
    }
    return cycle;
}


int main() {
    // вершина -> вектор смежных вершин
    int x;
    int v;
    string s;

    while (cin >> x) {
        v = x;
        //E.push_back(v);
        cin >> s; // arrow
        getline(cin, s);
        replace(s, ',', ' ');
        stringstream ss(s);
        while (ss >> x) {
            edgeNum++;
            graph[v].push_back({ x, false });
        }
    }

    vector<int> cycle = Eulerian_Cycle();

    int i;
    for (i = 0; i < cycle.size() - 1; i++)
        cout << cycle[i] << "->";
    cout << cycle[i];

    /*
    for(auto s : E){
        if(graph[s].size()){
            cout << s << " -> ";
            int i = 0;
            for(; i < graph[s].size() - 1; i++){
                cout << graph[s][i].v << ',';
            }
            cout << graph[s][i].v;
            cout << '\n';
        }
    }
    */

    return 0;
}