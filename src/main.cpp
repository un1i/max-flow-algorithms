#include <iostream>
#include <fstream>
#include "../include/edmonds_karp.h"
#include "../include/dinic.h"

using namespace std;

int main(){
    fstream fin("input.txt");
    int n, m, s, t;
    fin >> n >> m >> s >> t;
    --s;
    --t;
    vector<vector<size_t>> adj;
    vector<vector<int>> capacity;
    adj.resize(n);
    capacity.resize(n);
    for (int i = 0; i < n; i++)
        capacity[i].resize(n);

    for(size_t i = 0; i < m; i++){
        int x, y, c;
        fin >> x >> y >> c;
        adj[--x].push_back(--y);
        adj[y].push_back(x);
        capacity[x][y] = c;
    }

    int max_flow = edmonds_karp(adj, capacity, s, t);
    cout << max_flow;
}