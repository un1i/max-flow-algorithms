#include "graph.h"

#include <vector>

class Algorithm {
protected:
    const Graph& graph;
    int max_flow{};
public:
    explicit Algorithm(const Graph& graph);
    virtual void run() = 0;
    virtual int getMaxFlow();
};