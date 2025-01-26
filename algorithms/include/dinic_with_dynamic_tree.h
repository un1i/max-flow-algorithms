#ifndef MAXFLOW_DINIC_WITH_DYNAMIC_TREE_H
#define MAXFLOW_DINIC_WITH_DYNAMIC_TREE_H

#include "dinic.h"
#include "link_cut_tree.h"

#include <unordered_set>


using EdgeInTree = std::unordered_map<size_t, std::unordered_set<int>>;

class DinicWithDynamicTree : public Dinic {
public:
    explicit DinicWithDynamicTree(const Graph& graph);
    void run() override;
private:
    LinkCutTree link_cut;

    void addEdge(size_t cur, size_t next, const EdgeAvailableCapacity& available_capacity, EdgeInTree& edge_in_tree);
    void removeEdge(size_t cur, size_t prev, EdgeAvailableCapacity& available_capacity,
                    std::vector<int>& first_edge_ind, EdgeInTree& edge_in_tree);
    void decreaseCapacityInPath(Node* min_edge, EdgeAvailableCapacity& available_capacity,
                                std::vector<int>& first_edge_ind, EdgeInTree& edge_in_tree);
    void updateAvailableCapacity(EdgeInTree& edge_in_tree, EdgeAvailableCapacity& availableCapacity);
};

#endif //MAXFLOW_DINIC_WITH_DYNAMIC_TREE_H
