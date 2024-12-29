#include "../include/link_cut_tree.h"

void LinkCutTree::expose(Node* v) {
    splay(v);
    if (v->right) {
        std::swap(v->right->parent, v->right->path_parent);
        v->right = nullptr;
    }
    while (v->path_parent) {
        Node* u = v->path_parent;
        splay(u);
        if (u->right) {
            std::swap(u->right->parent, u->right->path_parent);
            u->right = nullptr;
        }
        u->right = v;
        v->path_parent = nullptr;
        v = u;
    }
}

void LinkCutTree::cut(Node* u, Node* v) {
    splay(v);
    if (v->left == u) {
        v->left = nullptr;
        u->parent = nullptr;
        std::swap(u->path_parent, v->path_parent);
    }
    else {
        v->path_parent = nullptr;
    }
}

void LinkCutTree::link(Node* u, Node* v) {
    splay(v);
    v->path_parent = u;
}

int LinkCutTree::get_root(int ind) {
    Node* v = nodes[ind];
    expose(v);
    while (v->left != nullptr) {
        v = v->left;
    }
    return v->id;
}

void LinkCutTree::remove_root(int ind) {
    Node* v = nodes[ind];
    expose(v);
    if (v->left) {
        while (v->left->left) {
            v = v->left;
        }
        cut(v->left, v);
    }
    else {
        cut(v, v->right);
    }

}
