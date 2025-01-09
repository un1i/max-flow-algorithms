#include "mpm.h"

#include <climits>
#include <queue>


MPM::MPM(const Graph &graph) : Algorithm(graph) {}

void MPM::run() {
    int flow = 0;
    size_t num_vertices = graph.getNumVertices();
    std::vector<int> distance(num_vertices);
    std::vector<int> free_edge_in_ind(num_vertices);
    std::vector<int> free_edge_out_ind(num_vertices);
    std::vector<bool> del_vertices(num_vertices);
    std::vector<int> pin(num_vertices);
    std::vector<int> pout(num_vertices);
    EdgeAvailableCapacity available_capacity = getAvailableCapacity();
    const GraphAdj& adj = graph.getAdj();

    while(bfs(distance, available_capacity)) {
        std::fill(pin.begin(), pin.end(), 0);
        std::fill(pout.begin(), pout.end(), 0);
        std::fill(free_edge_in_ind.begin(), free_edge_in_ind.end(), 0);
        std::fill(free_edge_out_ind.begin(), free_edge_out_ind.end(), 0);
        std::fill(del_vertices.begin(), del_vertices.end(), false);

        for (int vertex_ind = 0; vertex_ind < num_vertices; vertex_ind++) {
            if (distance[vertex_ind] == -1) {
                del_vertices[vertex_ind] = true;
            }
            else {
                for (const EdgeAdj& edge_adj : adj[vertex_ind]) {
                    if (distance[vertex_ind] + 1 == distance[edge_adj.end]) {
                        pout[vertex_ind] += available_capacity[vertex_ind][edge_adj.end];
                        pin[edge_adj.end] += available_capacity[vertex_ind][edge_adj.end];
                    }
                }
            }
        }
        pin[graph.getSource()] = INT_MAX;
        pout[graph.getSink()] = INT_MAX;

        while (!del_vertices[graph.getSource()]) {
            VertexInfo min_vertex = findMinVertex(pin, pout, del_vertices);
            if (min_vertex.flow != 0) {
                sendFlowToSink(min_vertex, available_capacity, distance,
                                  free_edge_out_ind, del_vertices, pin, pout);
                sendFlowToSource(min_vertex, available_capacity, distance,
                                    free_edge_in_ind, del_vertices, pin, pout);
                flow += min_vertex.flow;
            }

            del_vertices[min_vertex.vertex_ind] = true;
            for (int i = free_edge_in_ind[min_vertex.vertex_ind]; i < adj[min_vertex.vertex_ind].size(); i++) {
                EdgeAdj edge_adj = adj[min_vertex.vertex_ind][i];
                if (!del_vertices[edge_adj.end] && distance[edge_adj.end] + 1 == distance[min_vertex.vertex_ind]) {
                    pout[edge_adj.end] -= available_capacity[edge_adj.end][min_vertex.vertex_ind];
                }
            }

            for (int i = free_edge_out_ind[min_vertex.vertex_ind]; i < adj[min_vertex.vertex_ind].size(); i++) {
                EdgeAdj edge_adj = adj[min_vertex.vertex_ind][i];
                if (!del_vertices[edge_adj.end] && distance[edge_adj.end] == distance[min_vertex.vertex_ind] + 1) {
                    pin[edge_adj.end] -= available_capacity[min_vertex.vertex_ind][edge_adj.end];
                }
            }
        }
    }
    max_flow = flow;
}

bool MPM::bfs(std::vector<int> &distance, const EdgeAvailableCapacity &available_capacity) {
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

MPM::VertexInfo MPM::findMinVertex(const std::vector<int>& pin, const std::vector<int>& pout,
                            const std::vector<bool>& del_vertices) {
    int vertex_ind = -1;
    int min_flow = INT_MAX;

    for (int i = 0; i < graph.getNumVertices(); i++) {
        int cur_min = std::min(pin[i], pout[i]);
        if (!del_vertices[i] && cur_min < min_flow) {
            min_flow = cur_min;
            vertex_ind = i;
        }
    }
    return {vertex_ind, min_flow};
}

void MPM::sendFlowToSink(VertexInfo vertex, EdgeAvailableCapacity& available_capacity,
                    const std::vector<int>& distance, std::vector<int>& free_edge_ind,
                    std::vector<bool>& del_vertices, std::vector<int>& pin, std::vector<int>& pout) {
    GraphAdj adj = graph.getAdj();
    std::queue<VertexInfo> q;
    q.push(vertex);
    while (!q.empty()) {
        VertexInfo cur = q.front();
        q.pop();
        if (cur.vertex_ind == graph.getSink()) {
            continue;
        }
        for (int i = free_edge_ind[cur.vertex_ind]; i < adj[cur.vertex_ind].size(); i++) {
            EdgeAdj edge_adj = adj[cur.vertex_ind][i];
            if (distance[cur.vertex_ind] + 1 != distance[edge_adj.end] || del_vertices[edge_adj.end] ||
            available_capacity[cur.vertex_ind][edge_adj.end] == 0) {
                free_edge_ind[cur.vertex_ind]++;
            }
            else {
                if (available_capacity[cur.vertex_ind][edge_adj.end]< cur.flow) {
                    int flow_edge = available_capacity[cur.vertex_ind][edge_adj.end];
                    available_capacity[edge_adj.end][cur.vertex_ind] += flow_edge;
                    available_capacity[cur.vertex_ind][edge_adj.end] = 0;
                    cur.flow -= flow_edge;
                    q.push({edge_adj.end, flow_edge});
                    pout[cur.vertex_ind] -= flow_edge;
                    pin[edge_adj.end] -= flow_edge;
                    free_edge_ind[cur.vertex_ind]++;
                }
                else {
                    available_capacity[cur.vertex_ind][edge_adj.end] -= cur.flow;
                    available_capacity[edge_adj.end][cur.vertex_ind] += cur.flow;
                    pout[cur.vertex_ind] -= cur.flow;
                    pin[edge_adj.end] -= cur.flow;
                    q.push({edge_adj.end, cur.flow});
                    break;
                }
            }
        }
    }
}

void MPM::sendFlowToSource(MPM::VertexInfo vertex, EdgeAvailableCapacity &available_capacity,
                           const std::vector<int> &distance, std::vector<int> &free_edge_ind,
                           std::vector<bool> &del_vertices, std::vector<int> &pin, std::vector<int> &pout) {
    GraphAdj adj = graph.getAdj();
    std::queue<VertexInfo> q;
    q.push(vertex);
    while (!q.empty()) {
        VertexInfo cur = q.front();
        q.pop();
        if (cur.vertex_ind == graph.getSource()) {
            continue;
        }
        for (int i = free_edge_ind[cur.vertex_ind]; i < adj[cur.vertex_ind].size(); i++) {
            EdgeAdj edge_adj = adj[cur.vertex_ind][i];
            if (distance[cur.vertex_ind] != distance[edge_adj.end] + 1 || del_vertices[edge_adj.end] ||
                available_capacity[edge_adj.end][cur.vertex_ind] == 0) {
                free_edge_ind[cur.vertex_ind]++;
            }
            else {
                if (available_capacity[edge_adj.end][cur.vertex_ind] < cur.flow) {
                    int flow_edge = available_capacity[edge_adj.end][cur.vertex_ind];
                    available_capacity[cur.vertex_ind][edge_adj.end] += flow_edge;
                    available_capacity[edge_adj.end][cur.vertex_ind] = 0;
                    cur.flow -= flow_edge;
                    q.push({edge_adj.end, flow_edge});
                    pout[edge_adj.end] -= flow_edge;
                    pin[cur.vertex_ind] -= flow_edge;
                    free_edge_ind[cur.vertex_ind]++;
                }
                else {
                    available_capacity[cur.vertex_ind][edge_adj.end] += cur.flow;
                    available_capacity[edge_adj.end][cur.vertex_ind] -= cur.flow;
                    pout[edge_adj.end] -= cur.flow;
                    pin[cur.vertex_ind] -= cur.flow;
                    q.push({edge_adj.end, cur.flow});
                    break;
                }
            }
        }
    }
}
