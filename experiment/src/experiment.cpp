#include "experiment.h"
#include "algorithm.h"
#include "edmonds_karp.h"
#include "dinic.h"
#include "mpm.h"
#include "modified_edmonds_karp.h"
#include "dinic_with_dynamic_tree.h"

#include <fstream>
#include <memory>
#include <iostream>
#include <cmath>

const size_t Experiment::num_warmup_iterations = 2;
const size_t Experiment::num_measurements = 5;
const std::filesystem::path Experiment::INPUT_DIR =
        std::filesystem::path(__FILE__).parent_path().parent_path() / "graphs";
const std::filesystem::path Experiment::OUTPUT_DIR =
        std::filesystem::path(__FILE__).parent_path().parent_path() / "results";

Experiment::Experiment(const std::string& name, bool is_change_vertices) :
name(name), is_change_vertices(is_change_vertices) {}

void Experiment::run() {
    std::ifstream file(INPUT_DIR / name);
    size_t num_graphs;
    file >> num_graphs;
    for (size_t i = 0; i < num_graphs; i++) {
        auto graph = readGraphFromFile(file);
        variable_param.push_back(is_change_vertices ? graph.getNumVertices() : graph.getNumEdges());
        measureExecTime(graph);
    }
    writeResultsToFile();
}

void Experiment::measureExecTime(const Graph& graph) {
    std::vector<std::shared_ptr<Algorithm>> algs = {
            std::make_shared<EdmondsKarp>(graph),
            std::make_shared<Dinic>(graph),
            std::make_shared<MPM>(graph),
            std::make_shared<ModifiedEdmondsKarp>(graph),
            std::make_shared<DinicWithDynamicTree>(graph),
    };
    if (results.size() != algs.size()) {
        results.resize(algs.size());
    }
    for (size_t i = 0; i < algs.size(); i++) {
        for (size_t _ = 0; _ < num_warmup_iterations; _++) {
            algs[i]->run();
        }
        std::chrono::duration<double, std::milli> total_time = std::chrono::duration<double, std::milli>::zero();
        for (size_t _ = 0; _ < num_measurements; _++) {
            auto start = std::chrono::steady_clock::now();
            algs[i]->run();
            auto finish = std::chrono::steady_clock::now();
            total_time += finish - start;
        }
        results[i].push_back(std::lround(total_time.count() / num_measurements));
    }
}

Graph Experiment::readGraphFromFile(std::ifstream &fin) {
    size_t n, m;
    fin >> n >> m;
    GraphAdj adj(n);
    int begin, end, capacity;
    for (size_t i = 0; i < m; i++) {
        fin >> begin >> end >> capacity;
        adj[begin].emplace_back(end, capacity);
        adj[end].emplace_back(begin, 0);
    }
    return {n, m, adj, 0, n - 1};
}

void Experiment::writeResultsToFile() {
    std::string filename = name + "_result";
    std::ofstream file(OUTPUT_DIR / filename);
    for (size_t param : variable_param) {
        file << param << ' ';
    }
    file << std::endl;
    for (auto& res : results) {
        for (long long value : res) {
            file << value << ' ';
        }
        file << std::endl;
    }
}
