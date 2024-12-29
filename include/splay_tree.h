#ifndef MAX_FLOW_SPLAY_TREE_H
#define MAX_FLOW_SPLAY_TREE_H
#include <utility>


class SplayTree {
protected:
    struct Node {
        int val;
        int id;
        Node* path_parent;
        Node* parent;
        Node* left;
        Node* right;
        explicit Node(int x, Node* left = nullptr, Node* right = nullptr) : val{x}, left{left}, right{right},
        path_parent{nullptr} {}
    };

    void rotate_left(Node* v);
    void rotate_right(Node* v);
    void splay(Node* v);
    Node* find_node(int x);
    Node* merge(Node* tree1, Node* tree2);
    std::pair<SplayTree::Node*, SplayTree::Node*> split(int x);

public:
    int find(int x);
    void add(int x);
    void remove(int x);
};
#endif //MAX_FLOW_SPLAY_TREE_H
