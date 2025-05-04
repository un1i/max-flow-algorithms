#ifndef MAXFLOW_EXPERIMENT_H
#define MAXFLOW_EXPERIMENT_H

#include "graph.h"

#include <string>
#include <filesystem>

class Experiment {
private:
    const static std::filesystem::path INPUT_DIR;
    const static std::filesystem::path OUTPUT_DIR;
    std::string name;
    bool is_change_vertices;
    std::vector<size_t> variable_param;
    std::vector<std::vector<long long>> results;

    Graph readGraphFromFile(std::ifstream& fin);
    void measureExecTime(const Graph& graph);
    void writeResultsToFile();
public:
    explicit Experiment(const std::string& name, bool is_change_vertices);
    void run();
};

#endif //MAXFLOW_EXPERIMENT_H
