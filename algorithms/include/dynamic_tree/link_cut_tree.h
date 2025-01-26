#ifndef MAXFLOW_LINK_CUT_TREE_H
#define MAXFLOW_LINK_CUT_TREE_H

#include "node.h"

#include <vector>


class LinkCutTree {
private:
    std::vector<Node> nodes;

    Node* cutout(Node* vertex);
    Node* leftest(Node* vertex);
    Node* expose(Node* vertex);
    Node* cleanUp(Node* vertex);
    Node* liftUpToRoot(Node* vertex);
    Node* findLeftestMin(size_t min_value,  Node* vertex);
public:
    Node* lastExposed;
    explicit LinkCutTree(size_t size);
    ~LinkCutTree();

    void clearTrees();
    void removeCapacityInPath(int capacity, size_t ind);
    void link(size_t root_ind, size_t vertex_ind);
    void cut(size_t vertex_ind, size_t parent_ind);
    void setCapacity(size_t vertex_ind, int capacity);
    int getEdgeCapacity(size_t vertex_ind);
    Node* prevInPath(size_t ind);
    Node* getMinEdge(size_t ind);
    Node* findRoot(size_t ind);
};

#endif //MAXFLOW_LINK_CUT_TREE_H
