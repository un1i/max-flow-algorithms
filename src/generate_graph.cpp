#include <set>
#include <random>
#include <fstream>


int main(int arg, char** argv){
    int n = std::stoi(argv[1]);
    int m = std::stoi(argv[2]);
    int max_weight = std::stoi(argv[3]);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> random_vertex(1, n);

    std::set<std::pair<size_t, size_t>> edges;

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
    std::ofstream file("input.txt");
    file << n << ' ' << m << ' ' << 1 << ' ' << n << '\n';
    for(auto edge: edges){
        size_t c = random_weight(mt);
        file << edge.first << ' ' << edge.second << ' ' << c << '\n';
    }
}