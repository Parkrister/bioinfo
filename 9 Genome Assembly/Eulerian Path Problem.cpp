#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;

struct edge {
    int v; // next v
    bool visit;
};

struct deg {
    int in;
    int out;
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

vector<int> First_Cycle(int v0, int v1) {
    vector<int> cycle;
    cycle.push_back(v1);

    int i;
    for (i = 0; graph[v1][i].v != v0; i++);
    graph[v1][i].visit = true;
    cycle.push_back(v0);

    int endv = v1;

    for (i = 0; i < graph[v0].size() && graph[v0][i].visit; i++);
    graph[v0][i].visit = true;

    v1 = graph[v0][i].v;

    while (v1 != endv) {
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

vector<int> Eulerian_Cycle(int v0, int v1) {
    vector<int> cycle = First_Cycle(v0, v1); // создать первый цикл c вершинами vin, vout 
    rotate(cycle.begin(), cycle.begin() + 1, cycle.end()); // переместить v0 в начало
    cycle[cycle.size() - 1] = cycle[0];
    while (cycle.size() != edgeNum + 1) {
        int iv0 = newV(cycle);
        vector<int> cycle2 = Cycle(cycle[iv0]);
        cycle.insert(cycle.begin() + iv0, cycle2.begin(), cycle2.end() - 1);
    }
    return cycle;
}


int main() {
    // вершина -> вектор смежных вершин
    int x;
    int v;
    string s;

    map<int, deg> degrees; // степени вершин

    while (cin >> x) {
        v = x;
        cin >> s; // arrow
        getline(cin, s);
        replace(s, ',', ' ');
        stringstream ss(s);
        while (ss >> x) {
            edgeNum++;
            graph[v].push_back({ x, false });
            degrees[x].in++; degrees[v].out++;
        }
    }

    vector<int> vv; // начальные вершина для эйлерова пути
    for (auto d : degrees) {
        if (d.second.in != d.second.out)
            vv.push_back(d.first);
    }

    int vin, vout;
    if (degrees[vv[0]].out < degrees[vv[0]].in) { //находим вершину, у которой out < in 
        vout = vv[1];
        vin = vv[0];
    }
    else {
        vout = vv[0];
        vin = vv[1];
    }

    graph[vin].push_back({ vout, false }); // добавляем в граф ребро
    edgeNum++;

    vector<int> cycle = Eulerian_Cycle(vout, vin); //начинаем с вершины у которой out < in

    cycle.pop_back();//убираем последний шаг из цикла
    int i;
    for (i = 0; i < cycle.size() - 1; i++)
        cout << cycle[i] << "->";
    cout << cycle[i];

    return 0;
}