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


const std::filesystem::path Experiment::INPUT_DIR =
        std::filesystem::path(__FILE__).parent_path().parent_path() / "graphs";
const std::filesystem::path Experiment::OUTPUT_DIR =
        std::filesystem::path(__FILE__).parent_path().parent_path() / "results";

Experiment::Experiment(const std::string& name) : name(name) {}

void Experiment::run() {
    std::ifstream file(INPUT_DIR / name);
    size_t num_graphs;
    file >> num_graphs;
    for (size_t i = 0; i < num_graphs; i++) {
        auto graph = readGraphFromFile(file);
        std::cout << i + 1 << "graph calculated" << std::endl;
        variable_param.push_back(graph.getNumVertices());
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
        algs[i]->run();
        auto start = std::chrono::steady_clock::now();
        algs[i]->run();
        auto finish = std::chrono::steady_clock::now();
        results[i].push_back(std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count());
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
    return {n, adj, 0, n - 1};
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
