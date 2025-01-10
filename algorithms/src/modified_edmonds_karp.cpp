#include "modified_edmonds_karp.h"

#include <cmath>


ModifiedEdmondsKarp::ModifiedEdmondsKarp(const Graph &graph) : EdmondsKarp(graph) {}

void ModifiedEdmondsKarp::run() {
    int flow = 0;
    int C = 0;
    for (const std::vector<EdgeAdj>& adj : graph.getAdj()) {
        for (const EdgeAdj& edge_adj : adj) {
            C = std::max(C, edge_adj.capacity);
        }
    }
    int I = static_cast<int>(std::pow(3, static_cast<int>(log(C) / log(3))));
    std::vector<int> previous(graph.getNumVertices());
    EdgeAvailableCapacity available_capacity = getAvailableCapacity();

    while (I > 0) {
        flow += findMaxFlow(previous, available_capacity, I);
        I /= 3;
    }
    max_flow = flow;
}
