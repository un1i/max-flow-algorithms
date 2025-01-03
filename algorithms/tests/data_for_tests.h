#include "graph.h"

#include <utility>


struct TestData {
    Graph graph;
    int max_flow;

    TestData(Graph graph, int max_flow) : graph{std::move(graph)}, max_flow{max_flow} {}
};

class DataForTests {
private:
    DataForTests() = default;
public:
    static TestData makeLinearGraphData();
    static TestData makeMultiplePathsGraphData();
    static TestData makeCycleGraphData();
    static TestData makeParallelPathsGraphData();
    static TestData makeLimitOnSinkGraphData();

};
