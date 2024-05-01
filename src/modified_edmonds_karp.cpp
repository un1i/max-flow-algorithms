#include "../include/modified_edmonds_karp.h"
#include <queue>
#include <algorithm>
#include <cmath>
#include <iostream>

bool bfs(size_t s, size_t t, int min_capacity, const std::vector<std::vector<size_t>>& adj,
         const std::vector<std::vector<int>>& capacity, std::vector<int>& previous);

int modified_edmonds_karp(const std::vector<std::vector<size_t>>& adj, std::vector<std::vector<int>> capacity,
                          size_t s, size_t t) {
    int flow = 0;
    int C = 0;
    for (const std::vector<int>& v : capacity) {
        C = std::max(C, *std::max_element(v.begin(), v.end()));
    }
    int I = static_cast<int>(std::pow(3, static_cast<int>(log(C) / log(3))));
    std::vector<int> previous(adj.size());
    while (I > 0) {
        while (bfs(s, t, I, adj, capacity, previous)) {
            int prev = previous[t];
            size_t cur = t;
            int min_flow = INT_MAX;
            while (cur != s) {
                min_flow = std::min(min_flow, capacity[prev][cur]);
                cur = prev;
                prev = previous[prev];
            }
            flow += min_flow;

            prev = previous[t];
            cur = t;
            while (cur != s) {
                capacity[prev][cur] -= min_flow;
                capacity[cur][prev] += min_flow;
                cur = prev;
                prev = previous[prev];
            }
        }
        I /= 3;
    }
    return flow;
}

bool bfs(size_t s, size_t t, int min_capacity, const std::vector<std::vector<size_t>>& adj,
         const std::vector<std::vector<int>>& capacity, std::vector<int>& previous) {
    std::fill(previous.begin(), previous.end(), -1);
    std::queue<size_t> q;
    previous[s] = -2;
    q.push(s);
    while (!q.empty()) {
        size_t cur = q.front();
        q.pop();
        for (size_t next: adj[cur]) {
            if (previous[next] == -1 && capacity[cur][next] >= min_capacity) {
                previous[next] = static_cast<int>(cur);
                if (next == t) {
                    return true;
                }
                q.push(next);
            }
        }
    }
    return false;
}
