#include "link_cut_tree.h"
#include "splay_tree.h"

#include <stack>


LinkCutTree::LinkCutTree(size_t size) {
    lastExposed = nullptr;
    nodes.resize(size, Node(0));
    for (size_t i = 0; i < size; i++) {
        new SplayTree(&nodes[i]);
        nodes[i].id = i;
    }
}

LinkCutTree::~LinkCutTree() {
    for (size_t i = 0; i < nodes.size(); i++) {
        if (!nodes[i].parent) {
            SplayTree* buff = nodes[i].tree_ptr;
            buff->clearRoot();
            delete buff;
        }
    }
}

void LinkCutTree::clearTrees() {
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].parent) {
            nodes[i] = Node(i);
            nodes[i].tree_ptr = new SplayTree(&nodes[i]);
        }
        else {
            SplayTree* buff = nodes[i].tree_ptr;
            nodes[i] = Node(i);
            nodes[i].tree_ptr = buff;
        }
    }
}

void LinkCutTree::link(size_t root_ind, size_t vertex_ind) {
    Node* vertex = &nodes[vertex_ind];
    Node* root = &nodes[root_ind];
    root->path_parent = vertex;
    expose(root);
}

void LinkCutTree::cut(size_t vertex_ind, size_t parent_ind) {
    Node* vertex = &nodes[vertex_ind];
    Node* parent = &nodes[parent_ind];
    expose(parent);
    vertex->path_parent = nullptr;
}

Node* LinkCutTree::findRoot(size_t ind) {
    Node* vertex = &nodes[ind];
    if (vertex != lastExposed) {
        expose(vertex);
    }
    return leftest(liftUpToRoot(vertex));
}

Node* LinkCutTree::cleanUp(Node *vertex) {
    std::stack<Node*> stack;
    while (vertex) {
        stack.push(vertex);
        vertex = vertex->parent;
    }
    Node* root = stack.top();
    while (!stack.empty()) {
        stack.top()->push();
        stack.pop();
    }
    return root;
}

Node* LinkCutTree::liftUpToRoot(Node *vertex) {
    if (!vertex) {
        return nullptr;
    }
    if (!vertex->parent) {
        return vertex;
    }
    Node* root = cleanUp(vertex);
    root->tree_ptr->splay(vertex);
    return vertex;
}

Node* LinkCutTree::leftest(Node *vertex) {
    return vertex->tree_ptr->find(0);
}

Node* LinkCutTree::cutout(Node *vertex) {
    liftUpToRoot(vertex);
    auto splitted_trees = SplayTree::split(vertex->tree_ptr,
                                           (vertex->left ? vertex->left->getSize() : 0) + 1);
    SplayTree* right = splitted_trees.second;
    if (right->getRoot()) {
        right->find(0)->path_parent = vertex;
    }
    else {
        delete right;
    }
    return vertex;
}

Node* LinkCutTree::expose(Node *vertex) {
    lastExposed = vertex;
    Node* next;
    vertex = leftest(liftUpToRoot(cutout(vertex)));
    while (vertex->path_parent) {
        next = cutout(vertex->path_parent);
        vertex->path_parent = nullptr;
        SplayTree::merge(liftUpToRoot(next)->tree_ptr, liftUpToRoot(vertex)->tree_ptr);
        vertex = leftest(liftUpToRoot(vertex));
    }
    return vertex;
}

Node* LinkCutTree::getMinEdge(size_t ind) {
    Node* vertex = &nodes[ind];
    liftUpToRoot(vertex);
    int min_value = vertex->getMin();
    return findLeftestMin(min_value, vertex);
}

Node* LinkCutTree::findLeftestMin(size_t min_value, Node *vertex) {
    vertex->push();
    if (vertex->left && vertex->left->getMin() == min_value) {
        return findLeftestMin(min_value, vertex->left);
    }

    if (vertex->edge_capacity == min_value) {
        return vertex;
    }
    return findLeftestMin(min_value, vertex->right);
}

void LinkCutTree::setCapacity(size_t vertex_ind, int capacity) {
    Node* vertex = &nodes[vertex_ind];
    liftUpToRoot(vertex);
    vertex->edge_capacity = capacity;
    vertex->updateNodeParams();
}

void LinkCutTree::removeCapacityInPath(int capacity, size_t ind) {
    nodes[ind].removeCapacity(capacity);
}

int LinkCutTree::getEdgeCapacity(size_t vertex_ind) {
    Node* vertex = &nodes[vertex_ind];
    liftUpToRoot(vertex);
    vertex->push();
    return vertex->edge_capacity;
}

Node* LinkCutTree::prevInPath(size_t ind) {
    Node* source = &nodes[ind];
    expose(findRoot(ind));
    return leftest(liftUpToRoot(source));
}
