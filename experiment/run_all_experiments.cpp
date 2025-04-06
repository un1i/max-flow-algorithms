#include "experiment.h"

#include <vector>
#include <string>
#include <iostream>


int main() {
    std::vector<std::string> experiments_names = {
            "dense_graphs",
            "sparse_graphs",
            "complete_graphs",
            "grid_graphs",
            "complete_bipartite_graphs",
            "increase_num_edges_graphs",
    };
    for (const auto& name : experiments_names) {
        Experiment experiment(name);
        experiment.run();
        std::cout << name << " - write to file" << std::endl;
    }
}
