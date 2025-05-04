#include "data_for_tests.h"


TestData DataForTests::makeLinearGraphData() {
    GraphAdj adj = {
            {{1, 10}},
            {{0, 0} , {2, 5}},
            {{1, 0}, {3, 15}},
            {{2, 0}},
    };
    Graph graph = Graph(4, 3, adj, 0, 3);
    int max_flow = 5;
    return {graph, max_flow};
}

TestData DataForTests::makeMultiplePathsGraphData() {
    GraphAdj adj = {
            {{1, 10}, {2, 15}},
            {{0, 0}, {2, 10}, {3, 10}},
            {{0, 0}, {1, 0}, {3, 5}},
            {{1, 0}, {2, 0}},
    };
    Graph graph = Graph(4, 5, adj, 0, 3);
    int max_flow = 15;
    return {graph, max_flow};
}

TestData DataForTests::makeCycleGraphData() {
    GraphAdj adj = {
            {{1, 10}},
            {{0, 0}, {2, 5}, {3, 0}},
            {{1, 0}, {3, 10}},
            {{2, 0}, {1, 5}, {4, 10}},
            {{3, 0}}
    };
    Graph graph = Graph(5, 5, adj, 0, 4);
    int max_flow = 5;
    return {graph, max_flow};
}

TestData DataForTests::makeParallelPathsGraphData() {
    GraphAdj adj = {
            {{1, 10}, {2, 10}},
            {{0, 0}, {3, 10}},
            {{0, 0}, {3, 10}},
            {{1, 0}, {2, 0}, {4, 20}},
            {{3, 0}, }
    };
    Graph graph = Graph(5, 5, adj, 0, 4);
    int max_flow = 20;
    return {graph, max_flow};
}

TestData DataForTests::makeLimitOnSinkGraphData() {
    GraphAdj adj = {
            {{1, 15}, {2, 20}},
            {{0, 0}, {3, 10}},
            {{0, 0}, {3, 5}},
            {{1, 0}, {2, 0}, {4, 5}},
            {{3, 0}, }
    };
    Graph graph = Graph(5, 5, adj, 0, 4);
    int max_flow = 5;
    return {graph, max_flow};
}
