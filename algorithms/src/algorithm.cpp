#include "algorithm.h"

Algorithm::Algorithm(const Graph& graph) : graph{graph} {}

int Algorithm::getMaxFlow() {
    return max_flow;
}

EdgeAvailableCapacity Algorithm::getAvailableCapacity() {
    EdgeAvailableCapacity available_capacity;
    for (int begin_edge = 0; begin_edge < graph.getNumVertices(); begin_edge++) {
        for (const EdgeAdj& edge_adj : graph.getAdj()[begin_edge]) {
            available_capacity[begin_edge][edge_adj.end] = edge_adj.capacity;
        }
    }
    return available_capacity;
}
