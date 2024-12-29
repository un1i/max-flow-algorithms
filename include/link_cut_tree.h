#ifndef MAX_FLOW_LINK_CUT_TREE_H
#define MAX_FLOW_LINK_CUT_TREE_H

#include "../include/splay_tree.h"

#include <vector>

class LinkCutTree: protected  SplayTree{
private:
    std::vector<Node*> nodes;
public:
    void expose(Node* v);
    void cut(Node* u, Node* v);
    void link(Node* u, Node* v);
    int get_root(int ind);
    void remove_root(int ind);

};

#endif //MAX_FLOW_LINK_CUT_TREE_H
