#include "../include/dinic.h"
#include <queue>

bool bfs(const std::vector<std::vector<size_t>>& adj,
         std::vector<int>& distance,
         const std::vector<std::vector<int>>& capacity,
         size_t source, size_t sink);

int dfs(const std::vector<std::vector<size_t>>& adj,
        const std::vector<int>& distance,
        std::vector<std::vector<int>>& capacity,
        std::vector<int>& first_edge_ind,
        size_t source, size_t sink, int min_cap);

int dinic(const std::vector<std::vector<size_t>>& adj, std::vector<std::vector<int>> capacity, size_t source, size_t sink){
    int max_flow = 0;
    std::vector<int> distance(capacity.size());
    std::vector<int> free_edge_ind(capacity.size());

    while (bfs(adj, distance, capacity, source, sink)){
        std::fill(free_edge_ind.begin(), free_edge_ind.end(), 0);
        int flow;
        do{
            flow = dfs(adj, distance, capacity, free_edge_ind, source, sink, -1);
            max_flow += flow;
        } while (flow != 0);
    }
    return max_flow;
}

bool bfs(const std::vector<std::vector<size_t>>& adj,
         std::vector<int>& distance,
         const std::vector<std::vector<int>>& capacity,
         size_t source, size_t sink){
    std::fill(distance.begin(), distance.end(), -1);
    distance[source] = 0;

    std::queue<size_t> q;
    q.push(source);
    while (!q.empty()){
        size_t cur = q.front();
        q.pop();

        for (size_t next: adj[cur]){
            if (distance[next] == -1 && capacity[cur][next]){
                distance[next] = distance[cur] + 1;
                if (next == sink){
                    return true;
                }
                q.push(next);
            }
        }

    }
    return false;
}

int dfs(const std::vector<std::vector<size_t>>& adj,
        const std::vector<int>& distance,
        std::vector<std::vector<int>>& capacity,
        std::vector<int>& first_edge_ind,
        size_t cur, size_t sink, int min_cap){

    if (cur == sink || min_cap == 0) {
        return min_cap;
    }

    for(int i = first_edge_ind[cur]; i < adj[cur].size(); i++){
        size_t next = adj[cur][i];
        if (distance[cur] + 1 == distance[next] && capacity[cur][next]){
            int cur_cap = min_cap;
            if (cur_cap == -1){
                cur_cap = capacity[cur][next];
            }
            else{
                cur_cap = std::min(cur_cap, capacity[cur][next]);
            }
            int flow = dfs(adj, distance, capacity, first_edge_ind, next, sink, cur_cap);
            if (flow != 0){
                capacity[cur][next] -= flow;
                capacity[next][cur] += flow;
                return flow;
            }
        }
        first_edge_ind[cur]++;
    }
    return 0;
}
