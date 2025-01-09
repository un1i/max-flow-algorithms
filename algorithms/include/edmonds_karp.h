#include "algorithm.h"


class EdmondsKarp : public Algorithm {
public:
    explicit EdmondsKarp(const Graph& graph);
    void run() override;
private:
    bool bfs(std::vector<int>& previous, const EdgeAvailableCapacity& available_capacity);
};
