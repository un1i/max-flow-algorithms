#include "../include/edmonds_karp.h"
#include <queue>
#include <climits>

bool bfs(size_t s, size_t t, const std::vector<std::vector<size_t>>& adj, const std::vector<std::vector<int>>& capacity, std::vector<int>& previous);

int edmonds_karp(const std::vector<std::vector<size_t>>& adj, std::vector<std::vector<int>> capacity, size_t s, size_t t){
	int flow = 0;
	std::vector<int> previous;
	previous.resize(adj.size());

	while (bfs(s, t, adj, capacity, previous)) {
		size_t prev = previous[t];
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

	return flow;
}

bool bfs(size_t s, size_t t, const std::vector<std::vector<size_t>>& adj, const std::vector<std::vector<int>>& capacity, std::vector<int>& previous){
	std::fill(previous.begin(), previous.end(), -1);
	std::queue<size_t> q;
	q.push(s);
	previous[s] = -2;

	while (!q.empty()) {
		size_t cur = q.front();
		q.pop();
	
		for (size_t next : adj[cur]) {
			if (previous[next] == -1 && capacity[cur][next]) {
				previous[next] = cur;
				if (next == t)
					return true;
				q.push(next);
			}
		}

	}
	return false;
}


