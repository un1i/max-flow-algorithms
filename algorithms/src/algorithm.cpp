#include "algorithm.h"

Algorithm::Algorithm(const Graph& graph) : graph{graph} {}

int Algorithm::getMaxFlow() {
    return max_flow;
}
