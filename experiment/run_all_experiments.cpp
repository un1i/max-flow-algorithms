#include "experiment.h"

#include <vector>
#include <string>


int main() {
    std::vector<std::pair<std::string, bool>> experiment_params = {
            {"dense_graphs", true},
            {"sparse_graphs", true},
            {"complete_graphs", true},
            {"grid_graphs", true},
            {"complete_bipartite_graphs", true},
            {"increase_num_edges_graphs", false},
    };
    for (const auto& [name, is_change_vertices] : experiment_params) {
        Experiment experiment(name, is_change_vertices);
        experiment.run();
    }
}
