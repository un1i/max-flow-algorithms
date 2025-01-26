#include "splay_tree.h"

SplayTree::SplayTree(Node *_root) {
    root = _root;
    if (root) {
        root->tree_ptr = this;
    }
}

SplayTree::~SplayTree() {
    if (root) {
        root->recursiveDelete();
    }
}

void SplayTree::setParent(Node *vertex, Node *parent) {
    if (vertex) {
        vertex->parent = parent;
        vertex->tree_ptr = this;
    }
}

Node* SplayTree::getRoot() {
    return root;
}

void SplayTree::clearRoot() {
    root = nullptr;
}

void SplayTree::keepParent(Node *vertex) {
    setParent(vertex->left, vertex);
    setParent(vertex->right, vertex);
    vertex->updateNodeParams();
}

void SplayTree::rotate(Node *parent, Node *vertex) {
    Node* grand_parent = parent->parent;
    if (grand_parent) {
        grand_parent->push();
    }
    parent->push();
    vertex->push();

    if (grand_parent) {
        if (grand_parent->left == parent) {
            grand_parent->left = vertex;
        }
        else {
            grand_parent->right = vertex;
        }
    }

    if (parent->left == vertex) {
        parent->left = vertex->right;
        vertex->right = parent;
    }
    else {
        parent->right = vertex->left;
        vertex->left = parent;
    }

    keepParent(parent);
    keepParent(vertex);
    setParent(vertex, grand_parent);
}

void SplayTree::splay(Node *vertex) {
    while (vertex->parent) {
        Node* parent = vertex->parent;
        Node* grand_parent = parent->parent;
        if (!grand_parent) {
            rotate(parent, vertex);
            break;
        }

        bool is_zig_zig = ((grand_parent->left == parent) == (parent->left == vertex));
        if (is_zig_zig) {
            rotate(grand_parent, parent);
            rotate(parent, vertex);
        }
        else {
            rotate(parent, vertex);
            rotate(grand_parent, vertex);
        }
    }
    root = vertex;
    root->tree_ptr = this;
}

Node* SplayTree::find(size_t position) {
    size_t tree_size = 0;
    if (root) {
        tree_size = root->getSize();
    }

    if (position < tree_size) {
        return find(position, root);
    }
    return nullptr;
}

Node* SplayTree::find(size_t position, Node *vertex) {
    vertex->push();
    size_t left_ind = 0;
    if (vertex->left) {
        left_ind = vertex->left->getSize();
    }
    if (position == left_ind) {
        splay(vertex);
        return vertex;
    }

    if (position < left_ind) {
        return find(position, vertex->left);
    }
    return find(position - left_ind - 1, vertex->right);
}

std::pair<SplayTree*, SplayTree*> SplayTree::split(SplayTree *tree, size_t position) {
    SplayTree* left = nullptr;
    SplayTree* right = nullptr;
    if (tree) {
        right = tree->split(position);
        left = tree;
    }
    return {left, right};
}

SplayTree* SplayTree::split(size_t position) {
    size_t tree_size = 0;
    if (root) {
        tree_size = root->getSize();
    }

    if (position > tree_size) {
        return nullptr;
    }

    if (position == tree_size) {
        return new SplayTree(nullptr);
    }

    Node* new_root = find(position, root);
    auto* right_tree = new SplayTree(new_root);
    root = new_root->left;
    new_root->left = nullptr;
    setParent(root, nullptr);

    if (right_tree->root) {
        right_tree->root->tree_ptr = this;
        right_tree->root->push();
    }
    if (root) {
        root->push();
    }
    return right_tree;
}

SplayTree* SplayTree::merge(SplayTree *left, SplayTree *right) {
    if (!left) {
        return right;
    }
    left->merge(right);
    return left;
}

void SplayTree::merge(SplayTree *added_tree) {
    if (!added_tree->root) {
        delete added_tree;
        return;
    }

    if (!root) {
        root = added_tree->root;
        added_tree->root = nullptr;
        delete added_tree;
        return;
    }
    find(root->getSize() - 1);
    added_tree->find(0);
    root->push();
    root->right = added_tree->root;
    added_tree->root = nullptr;
    delete added_tree;
    keepParent(root);
}

void SplayTree::insert(int value, size_t position) {
    size_t tree_size = 0;
    if (position > tree_size) {
        return;
    }

    SplayTree* right = split(position);
    Node* new_root = new Node(value);
    new_root->left = root;
    if (right) {
        new_root->right = right->root;
    }
    root = new_root;
    keepParent(root);
    root->updateNodeParams();
    if (right) {
        right->root = nullptr;
    }
}
