#include "dinic.h"

#include <queue>


Dinic::Dinic(const Graph &graph) : Algorithm(graph) {}

void Dinic::run() {
    int flow = 0;
    std::vector<int> distance(graph.getNumVertices());
    std::vector<int> free_edge_ind(graph.getNumVertices());
    EdgeAvailableCapacity available_capacity = getAvailableCapacity();

    while (bfs(distance, available_capacity)) {
        std::fill(free_edge_ind.begin(), free_edge_ind.end(), 0);
        int cur_flow;
        do {
            cur_flow = dfs(graph.getSource(), -1, distance, available_capacity, free_edge_ind);
            flow += cur_flow;
        } while (cur_flow != 0);
    }
    max_flow = flow;
}

bool Dinic::bfs(std::vector<int> &distance, const EdgeAvailableCapacity &available_capacity) {
    std::fill(distance.begin(), distance.end(), -1);
    distance[graph.getSource()] = 0;

    std::queue<size_t> q;
    q.push(graph.getSource());
    while (!q.empty()) {
        size_t edge_begin = q.front();
        q.pop();

        for (const EdgeAdj& edge_adj : graph.getAdj()[edge_begin]) {
            if (distance[edge_adj.end] == -1 &&
            available_capacity.at(edge_begin).at(edge_adj.end)) {
                distance[edge_adj.end] = distance[edge_begin] + 1;
                if (edge_adj.end == graph.getSink()) {
                    return true;
                }
                q.push(edge_adj.end);
            }
        }
    }
    return false;
}

int Dinic::dfs(size_t cur_vertex, int min_cap, const std::vector<int>& distance, EdgeAvailableCapacity &available_capacity,
               std::vector<int> &first_edge_ind) {
    if (cur_vertex == graph.getSink() || min_cap == 0) {
        return min_cap;
    }

    for (int i = first_edge_ind[cur_vertex]; i < graph.getAdj().at(cur_vertex).size(); i++) {
        int next_vertex = graph.getAdj().at(cur_vertex).at(i).end;
        if (distance[cur_vertex] + 1 == distance[next_vertex] && available_capacity[cur_vertex][next_vertex]) {
            int cur_cap = min_cap;
            if (cur_cap == -1) {
                cur_cap = available_capacity[cur_vertex][next_vertex];
            }
            else {
                cur_cap = std::min(cur_cap, available_capacity[cur_vertex][next_vertex]);
            }
            int flow = dfs(next_vertex, cur_cap, distance, available_capacity, first_edge_ind);
            if (flow) {
                available_capacity[cur_vertex][next_vertex] -= flow;
                available_capacity[next_vertex][cur_vertex] += flow;
                return flow;
            }
        }
        first_edge_ind[cur_vertex]++;
    }
    return 0;
}
