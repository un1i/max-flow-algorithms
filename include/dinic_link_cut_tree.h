#ifndef MAX_FLOW_DINIC_LINK_CUT_TREE_H
#define MAX_FLOW_DINIC_LINK_CUT_TREE_H
#include <vector>

int dinic_link_cut_tree(const std::vector<std::vector<size_t>>& adj,
                        std::vector<std::vector<int>> capacity, size_t source, size_t sink);

#endif //MAX_FLOW_DINIC_LINK_CUT_TREE_H
