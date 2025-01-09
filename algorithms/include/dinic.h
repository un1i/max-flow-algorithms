#ifndef MAXFLOW_DINIC_H
#define MAXFLOW_DINIC_H

#include "algorithm.h"

class Dinic : public Algorithm {
public:
    explicit Dinic(const Graph& graph);
    void run() override;
private:
    bool bfs(std::vector<int>& distance, const EdgeAvailableCapacity& available_capacity);
    int dfs(size_t cur_vertex, int min_cap, const std::vector<int>& distance,
            EdgeAvailableCapacity& available_capacity, std::vector<int>& first_edge_ind);
};

#endif //MAXFLOW_DINIC_H
