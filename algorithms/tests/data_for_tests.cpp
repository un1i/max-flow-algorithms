#include "data_for_tests.h"


TestData DataForTests::makeLinearGraphData() {
    GraphAdj adj = {
            {{1, 10}},
            {{2, 5}},
            {{3, 15}},
            {},
    };
    Graph graph = Graph(4, adj, 0, 3);
    int max_flow = 5;
    return {graph, max_flow};
}

TestData DataForTests::makeMultiplePathsGraphData() {
    GraphAdj adj = {
            {{1, 10}, {2, 15}},
            {{2, 10}, {3, 10}},
            {{3, 5}},
            {},
    };
    Graph graph = Graph(4, adj, 0, 3);
    int max_flow = 15;
    return {graph, max_flow};
}

TestData DataForTests::makeCycleGraphData() {
    GraphAdj adj = {
            {{1, 10}},
            {{2, 5}},
            {{3, 10}},
            {{1, 5}, {4, 10}},
            {}
    };
    Graph graph = Graph(5, adj, 0, 4);
    int max_flow = 5;
    return {graph, max_flow};
}

TestData DataForTests::makeParallelPathsGraphData() {
    GraphAdj adj = {
            {{1, 10}, {2, 10}},
            {{3, 10}},
            {{3, 10}},
            {{4, 20}},
            {}
    };
    Graph graph = Graph(5, adj, 0, 4);
    int max_flow = 20;
    return {graph, max_flow};
}

TestData DataForTests::makeLimitOnSinkGraphData() {
    GraphAdj adj = {
            {{1, 15}, {2, 20}},
            {{3, 10}},
            {{3, 5}},
            {{4, 5}},
            {}
    };
    Graph graph = Graph(5, adj, 0, 4);
    int max_flow = 5;
    return {graph, max_flow};
}