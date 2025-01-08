#ifndef MAXFLOW_MPM_H
#define MAXFLOW_MPM_H

#include "algorithm.h"


class MPM : public Algorithm {
public:
    explicit MPM(const Graph& graph);
    void run() override;
private:
    struct VertexInfo {
        int vertex_ind;
        int flow;
    };

    bool bfs(std::vector<int>& distance, const EdgeAvailableCapacity& available_capacity);
    VertexInfo findMinVertex(const std::vector<int>& pin, const std::vector<int>& pout,
                                const std::vector<bool>& del_vertices);
    void sendFlowToSink(VertexInfo vertex, EdgeAvailableCapacity& available_capacity,
                        const std::vector<int>& distance, std::vector<int>& free_edge_ind,
                        std::vector<bool>& del_vertices, std::vector<int>& pin, std::vector<int>& pout);
    void sendFlowToSource(VertexInfo vertex, EdgeAvailableCapacity& available_capacity,
                        const std::vector<int>& distance, std::vector<int>& free_edge_ind,
                        std::vector<bool>& del_vertices, std::vector<int>& pin, std::vector<int>& pout);
    EdgeAvailableCapacity getAvailableCapacity();
};

#endif //MAXFLOW_MPM_H
