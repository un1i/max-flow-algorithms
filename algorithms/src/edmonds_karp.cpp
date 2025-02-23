#include "edmonds_karp.h"

#include <queue>
#include <climits>


EdmondsKarp::EdmondsKarp(const Graph &graph) : Algorithm(graph) {}

void EdmondsKarp::run() {
    std::vector<int> previous(graph.getNumVertices());
    EdgeAvailableCapacity available_capacity = getAvailableCapacity();
    max_flow = findMaxFlow(previous, available_capacity);
}

int EdmondsKarp::findMaxFlow(std::vector<int>& previous,
                             EdgeAvailableCapacity& available_capacity,
                             int min_capacity) {
    int flow = 0;
    while(bfs(previous, available_capacity, min_capacity)) {
        size_t source = graph.getSource();
        size_t sink = graph.getSink();
        size_t prev = previous[sink];
        size_t cur = sink;
        int min_flow = INT_MAX;

        while (cur != source) {
            min_flow = std::min(min_flow, available_capacity[prev][cur]);
            cur = prev;
            prev = previous[prev];
        }

        flow += min_flow;
        prev = previous[sink];
        cur = sink;
        while (cur != source) {
            available_capacity[prev][cur] -= min_flow;
            available_capacity[cur][prev] += min_flow;
            cur = prev;
            prev = previous[prev];
        }
    }
    return flow;
}

bool EdmondsKarp::bfs(std::vector<int>& previous,
                      const EdgeAvailableCapacity& available_capacity,
                      int min_capacity) {
    size_t source = graph.getSource();
    size_t sink = graph.getSink();
    std::fill(previous.begin(), previous.end(), -1);
    std::queue<size_t> q;
    q.push(source);
    previous[source] = -2;

    while (!q.empty()) {
        size_t edge_begin = q.front();
        q.pop();

        for (const EdgeAdj& edge_adj : graph.getAdj()[edge_begin]) {
            if (previous[edge_adj.end] == -1 &&
            available_capacity.at(edge_begin).at(edge_adj.end) >= min_capacity) {
                previous[edge_adj.end] = edge_begin;
                if (edge_adj.end == sink) {
                    return true;
                }
                q.push(edge_adj.end);
            }
        }
    }
    return false;
}
