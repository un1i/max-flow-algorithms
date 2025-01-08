#include "edmonds_karp.h"
#include "dinic.h"
#include "mpm.h"

#include <iostream>


int main(){
    GraphAdj adj = {
            {{1, 10}, {2, 5}},
            {{0, 0}, {2, 15}, {3, 10}},
            {{0, 0}, {1, 0}, {3, 10}, {4, 10}},
            {{1, 0}, {2, 0}, {4, 5}},
            {{2, 0}, {3, 0}},
    };
    Graph graph(5, adj, 0, 4);
    EdmondsKarp karp(graph);
    karp.run();
    std::cout << "Edmonds-Karp result: " << karp.getMaxFlow() << std::endl;

    Dinic dinic(graph);
    dinic.run();
    std::cout << "Dinic's result: " << dinic.getMaxFlow() << std::endl;

    MPM mpm(graph);
    mpm.run();
    std::cout << "MPM result: " << mpm.getMaxFlow() << std::endl;
}
