#include <vector>

int dinic(const std::vector<std::vector<size_t>>& adj, std::vector<std::vector<int>> capacity, size_t source, size_t sink);

bool bfs(const std::vector<std::vector<size_t>>& adj,
         std::vector<int>& distance,
         const std::vector<std::vector<int>>& capacity,
         size_t source, size_t sink);
