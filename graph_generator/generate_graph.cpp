#include <set>
#include <random>


std::pair<std::vector<std::vector<size_t>>, std::vector<std::vector<int>>> generate_graph(int n, int m, int max_weight){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> random_vertex(0, n - 1);

    std::set<std::pair<size_t, size_t>> edges;
    std::vector<std::vector<size_t>> adj(n);
    std::vector<std::vector<int>> capacity(n);
    for (auto& vec : capacity) {
        vec.resize(n);
    }

    int i = 0;
    while (i < m){
        int x = random_vertex(mt);
        int y = random_vertex(mt);
        if (x==y || edges.count({x, y}) || edges.count({y, x}))
            continue;
        edges.insert({x, y});
        ++i;
    }

    std::uniform_int_distribution<int> random_weight(1, max_weight);
    for(auto edge: edges){
        int c = random_weight(mt);
        adj[edge.first].emplace_back(edge.second);
        adj[edge.second].emplace_back(edge.first);
        capacity[edge.first][edge.second] = c;
    }
    return {adj, capacity};
}