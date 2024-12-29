#include "../include/splay_tree.h"
#include <stack>

void SplayTree::rotate_left(Node *v) {
    Node* parent = v->parent;
    Node* right = v->right;
    if (parent) {
        if (parent->left == v) {
            parent->left = right;
        }
        else {
            parent->right = right;
        }
    }
    SplayTree::Node* tmp = right->left;
    right->left = v;
    v->right = tmp;

    v->parent = right;
    right->parent = parent;
    if (v->right) {
        v->right->parent = v;
    }
}

void SplayTree::rotate_right(Node *v) {
    Node* parent = v->parent;
    SplayTree::Node* left = v->left;
    if (parent) {
        if (parent->left == v) {
            parent->left = left;
        }
        else {
            parent->right = left;
        }
    }
    SplayTree::Node* tmp = left->right;
    left->right = v;
    v->left = tmp;

    v->parent = left;
    left->parent = parent;
    if (v->left) {
        v->left->parent = v;
    }
}

void SplayTree::splay(Node* v) {
    while (v->parent) {
        if (v->parent->left == v) {
            if (!v->parent->parent) {
                rotate_right(v->parent);
                std::swap(v->path_parent, v->right->path_parent);
            }
            else if (v->parent->parent->left == v->parent) {
                rotate_right(v->parent->parent);
                rotate_right(v->parent);
                std::swap(v->path_parent, v->right->right->path_parent);
            }
            else {
                rotate_right(v->parent);
                rotate_left(v->parent);
                std::swap(v->path_parent, v->left->path_parent);
            }
        }
        else {
            if (!v->parent->parent) {
                rotate_left(v->parent);
                std::swap(v->path_parent, v->left->path_parent);
            }
            else if (v->parent->parent->right == v->parent) {
                rotate_left(v->parent->parent);
                rotate_left(v->parent);
                std::swap(v->path_parent, v->left->left->path_parent);
            }
            else {
                rotate_left(v->parent);
                rotate_right(v->parent);
                std::swap(v->path_parent, v->right->path_parent);
            }
        }
    }
}

SplayTree::Node* SplayTree::find_node(int x) {
    Node* prev = nullptr;
    Node* cur = root;
    while (cur) {
        prev = cur;
        if (x > cur->val) {
            cur = cur->right;
        }
        else if (x < cur->val) {
            cur = cur->left;
        }
        else {
            break;
        }
    }
    if (cur) {
        return cur;
    }
    return prev;
}

int SplayTree::find(int x) {
    Node* node = find_node(x);
    if (node && node->val == x) {
        splay(x, root);
        return node->val;
    }
    return 0;
}

SplayTree::Node* SplayTree::merge(Node* tree1, Node* tree2) {
    if (tree1) {
        Node *max_tree1 = tree1;
        while (max_tree1->right) {
            max_tree1 = max_tree1->right;
        }
        splay(max_tree1);
        tree1->right = tree2;
        return tree1;
    }
    return tree2;
}

std::pair<SplayTree::Node*, SplayTree::Node*> SplayTree::split(int x) {
    Node* node = find_node(x);
    if (node) {
        splay(x, root);
        if (root->val > x) {
            return {root->left, root};
        }
        return {root, root->right};
    }
    return {nullptr, nullptr};
}

void SplayTree::add(int x) {
    std::pair<Node*, Node*> trees = split(x);
    if (trees.first == nullptr && trees.second == nullptr) {
        root = new Node(x);
    }
    else {
        root = new Node(x, trees.first, trees.second);
    }
}

void SplayTree::remove(int x) {
    Node* node = find_node(x);
    if (node && node->val == x) {
        splay(x, root);
        Node* tmp = root;
        root = merge(root->left, root->right);
        delete tmp;
    }
}
