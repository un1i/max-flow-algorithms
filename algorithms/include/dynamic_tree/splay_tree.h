#ifndef MAXFLOW_SPLAY_TREE_H
#define MAXFLOW_SPLAY_TREE_H

#include "node.h"

#include <utility>


class SplayTree {
private:
    Node* find(size_t position, Node* vertex);
    void insert(int value, size_t position);
//    void remove(size_t position);
    void keepParent(Node* vertex);
    void setParent(Node* vertex, Node* parent);
    void rotate(Node* parent, Node* vertex);
    void merge(SplayTree* added_tree);
    SplayTree* split(size_t position);

    Node* root;

public:
    explicit SplayTree(Node* root);
    ~SplayTree();
    Node* find(size_t position);
    void splay(Node* vertex);
    Node* getRoot();
    void clearRoot();

    static std::pair<SplayTree*, SplayTree*> split(SplayTree* tree, size_t position);
    static SplayTree* merge(SplayTree* left, SplayTree* right);
};

#endif //MAXFLOW_SPLAY_TREE_H
