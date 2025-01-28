#ifndef MAXFLOW_NODE_H
#define MAXFLOW_NODE_H

#include <cstdio>


class SplayTree;

class Node {
    friend class SplayTree;
    friend class LinkCutTree;
public:
    explicit Node(size_t id);
    void removeCapacity(int value);
    void updateNodeParams();
    void push();
    size_t getSize() const;
    int getMin() const;
    size_t getId() const;
    int getCapacity() const;
    int getSubtreeCapacity() const;
private:
    size_t id;
    int edge_capacity;
    int subtree_capacity;
    size_t size_of_subtree;
    int subtree_min_capacity;
    int remove_capacity_value;

    Node* left;
    Node* right;
    Node* parent;
    Node* path_parent;

    SplayTree* tree_ptr;
};

#endif //MAXFLOW_NODE_H
