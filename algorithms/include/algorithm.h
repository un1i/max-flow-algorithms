#ifndef MAXFLOW_ALGORITHM_H
#define MAXFLOW_ALGORITHM_H

#include "graph.h"

#include <vector>
#include <unordered_map>


using EdgeAvailableCapacity = std::unordered_map<size_t, std::unordered_map<size_t, int>>;

class Algorithm {
protected:
    const Graph& graph;
    int max_flow{};
    EdgeAvailableCapacity getAvailableCapacity();
public:
    explicit Algorithm(const Graph& graph);
    virtual void run() = 0;
    virtual int getMaxFlow();
};

#endif //MAXFLOW_ALGORITHM_H
