#include "algorithm.h"

#include <unordered_map>


using EdgeAvailableCapacity = std::unordered_map<size_t, std::unordered_map<size_t, int>>;

class EdmondsKarp : public Algorithm {
public:
    explicit EdmondsKarp(const Graph& graph);
    void run() override;
private:
    bool bfs(std::vector<int>& previous, const EdgeAvailableCapacity& available_capacity);
    EdgeAvailableCapacity getAvailableCapacity();
};
