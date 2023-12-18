#include "../include/mpm.h"
#include "../include/dinic.h"
#include <climits>
#include <queue>

std::pair<int, int> find_min_vertex(const std::vector<int>& pin, const std::vector<int>& pout,
                                    const std::vector<bool>& del_vertexes) {
    int min_vertex = -1;
    int min_val = INT_MAX;

    for (int i = 0; i < pin.size(); i++) {
        int cur_min = std::min(pin[i], pout[i]);
        if (!del_vertexes[i] && cur_min < min_val) {
            min_val = cur_min;
            min_vertex = i;
        }
    }
    return {min_vertex, min_val};
}

void send_flow_to_sink(int vertex, int flow, size_t sink, const std::vector<std::vector<size_t>>& adj,
                       std::vector<std::vector<int>>& capacity, const std::vector<int>& distance,
                       std::vector<int>& free_edge_ind, std::vector<bool>& del_vertexes,
                       std::vector<int>& pin, std::vector<int>& pout) {
    std::queue<std::pair<int, int>> q;
    q.emplace(vertex, flow);
    while (!q.empty()) {
        std::pair<int, int> tmp = q.front();
        q.pop();
        int cur_vertex = tmp.first;
        int cur_flow = tmp.second;
        if (cur_vertex == sink) {
            continue;
        }
        for (int i = free_edge_ind[cur_vertex]; i < adj[cur_vertex].size(); i++) {
            size_t next_v = adj[cur_vertex][i];
            if (distance[cur_vertex] + 1 != distance[next_v] || del_vertexes[next_v] || capacity[cur_vertex][next_v] == 0) {
                free_edge_ind[cur_vertex]++;
            }
            else {
                if (capacity[cur_vertex][next_v] < cur_flow) {
                    int flow_edge = capacity[cur_vertex][next_v];
                    capacity[next_v][cur_vertex] += flow_edge;
                    capacity[cur_vertex][next_v] = 0;
                    cur_flow -= flow_edge;
                    q.emplace(next_v, flow_edge);
                    pout[cur_vertex] -= flow_edge;
                    pin[next_v] -= flow_edge;
                    free_edge_ind[cur_vertex]++;
                }
                else {
                    capacity[cur_vertex][next_v] -= cur_flow;
                    capacity[next_v][cur_vertex] += cur_flow;
                    pout[cur_vertex] -= cur_flow;
                    pin[next_v] -= cur_flow;
                    q.emplace(next_v, cur_flow);
                    break;
                }
            }
        }
    }

}

void send_flow_to_source(int vertex, int flow, size_t source, const std::vector<std::vector<size_t>>& adj,
                         std::vector<std::vector<int>>& capacity, const std::vector<int>& distance,
                         std::vector<int>& free_edge_ind, std::vector<bool>& del_vertexes,
                         std::vector<int>& pin, std::vector<int>& pout) {
    std::queue<std::pair<int, int>> q;
    q.emplace(vertex, flow);
    while (!q.empty()) {
        std::pair<int, int> tmp = q.front();
        q.pop();
        int cur_vertex = tmp.first;
        int cur_flow = tmp.second;

        if (cur_vertex == source) {
            continue;
        }
        for (int i = free_edge_ind[cur_vertex]; i < adj[cur_vertex].size(); i++) {
            size_t next_v = adj[cur_vertex][i];
            if (distance[next_v] + 1 != distance[cur_vertex] || del_vertexes[next_v] || capacity[next_v][cur_vertex] == 0) {
                free_edge_ind[cur_vertex]++;
            }
            else {
                if (capacity[next_v][cur_vertex] < cur_flow) {
                    int flow_edge = capacity[next_v][cur_vertex];
                    capacity[cur_vertex][next_v] += flow_edge;
                    capacity[next_v][cur_vertex] = 0;
                    cur_flow -= flow_edge;
                    q.emplace(next_v, flow_edge);
                    pout[next_v] -= flow_edge;
                    pin[cur_vertex] -= flow_edge;
                    free_edge_ind[cur_vertex]++;
                }
                else {
                    capacity[cur_vertex][next_v] += cur_flow;
                    capacity[next_v][cur_vertex] -= cur_flow;
                    pout[next_v] -= cur_flow;
                    pin[cur_vertex] -= cur_flow;
                    q.emplace(next_v, cur_flow);
                    break;
                }
            }
        }
    }

}

int mpm(const std::vector<std::vector<size_t>>& adj, std::vector<std::vector<int>> capacity, size_t source, size_t sink) {
    int max_flow = 0;
    std::vector<int> distance;
    distance.resize(capacity.size());
    std::vector<int> free_edge_in_ind(capacity.size());
    std::vector<int> free_edge_out_ind(capacity.size());
    std::vector<bool> del_vertexes(capacity.size());
    std::vector<int> pin(capacity.size());
    std::vector<int> pout(capacity.size());

    while(bfs(adj, distance, capacity, source, sink)) {
        fill(pin.begin(), pin.end(), 0);
        fill(pout.begin(), pout.end(), 0);
        fill(free_edge_in_ind.begin(), free_edge_in_ind.end(), 0);
        fill(free_edge_out_ind.begin(), free_edge_out_ind.end(), 0);
        fill(del_vertexes.begin(), del_vertexes.end(), false);

        for (int i = 0; i < adj.size(); i++) {
            if (-1 < distance[i]) {
                for (const size_t &j: adj[i]) {
                    if (distance[i] + 1 == distance[j]) {
                        pout[i] += capacity[i][j];
                        pin[j] += capacity[i][j];
                    }
                }
            }
            else {
                del_vertexes[i] = true;
            }
        }
        pin[source] = INT_MAX;
        pout[sink] = INT_MAX;

        while (!del_vertexes[source]) {
            std::pair<int, int> tmp = find_min_vertex(pin, pout, del_vertexes);
            int min_vertex = tmp.first;
            int flow = tmp.second;
            if (flow != 0) {
                send_flow_to_sink(min_vertex, flow, sink, adj, capacity, distance,
                                  free_edge_out_ind, del_vertexes, pin, pout);
                send_flow_to_source(min_vertex, flow, source, adj, capacity, distance,
                                    free_edge_in_ind, del_vertexes, pin, pout);
                max_flow += flow;
            }

            del_vertexes[min_vertex] = true;
            for (int i = free_edge_in_ind[min_vertex]; i < adj[min_vertex].size(); i++) {
                size_t next_v = adj[min_vertex][i];
                if (!del_vertexes[next_v] && distance[next_v] + 1 == distance[min_vertex]) {
                    pout[next_v] -= capacity[next_v][min_vertex];
                }
            }

            for (int i = free_edge_out_ind[min_vertex]; i < adj[min_vertex].size(); i++) {
                size_t next_v = adj[min_vertex][i];
                if (!del_vertexes[next_v] && distance[next_v] == distance[min_vertex] + 1) {
                    pin[next_v] -= capacity[min_vertex][next_v];
                }
            }
        }
    }
    return max_flow;
}
