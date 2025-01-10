#ifndef MAXFLOW_EDMONDS_KARP_H
#define MAXFLOW_EDMONDS_KARP_H

#include "algorithm.h"


class EdmondsKarp : public Algorithm {
public:
    explicit EdmondsKarp(const Graph& graph);
    void run() override;
protected:
    int findMaxFlow(std::vector<int>& previous, EdgeAvailableCapacity& available_capacity, int min_capacity = 1);
    bool bfs(std::vector<int>& previous, const EdgeAvailableCapacity& available_capacity, int min_capacity);
};

#endif //MAXFLOW_EDMONDS_KARP_H
