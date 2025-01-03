#include "edmonds_karp.h"

#include <iostream>


int main(){
    GraphAdj adj = {
            {{1, 10}, {2, 5}},
            {{2, 15}, {3, 10}},
            {{3, 10}, {4, 10}},
            {{4, 5}},
            {},
    };
    Graph graph(5, adj, 0, 4);
    EdmondsKarp karp(graph);
    karp.run();
    std::cout << karp.getMaxFlow();
}
