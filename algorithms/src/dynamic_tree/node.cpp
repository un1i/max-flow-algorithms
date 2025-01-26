#include <algorithm>
#include "node.h"

Node::Node(size_t id) : id{id}, edge_capacity{0}, subtree_capacity{0},
size_of_subtree{1}, subtree_min_capacity{0}, remove_capacity_value{0},
left{nullptr}, right{nullptr}, parent{nullptr}, path_parent{nullptr}, tree_ptr{nullptr} {}

void Node::recursiveDelete() {
    if (left) {
        left->recursiveDelete();
    }
    if (right) {
        right->recursiveDelete();
    }
    delete this;
}

void Node::removeCapacity(int value) {
    remove_capacity_value += value;
}

void Node::updateNodeParams() {
    size_of_subtree = 1;
    subtree_capacity = edge_capacity;
    subtree_min_capacity = edge_capacity;
    if (left) {
        size_of_subtree += left->getSize();
        subtree_capacity = left->getSubtreeCapacity();
        subtree_min_capacity = std::min(subtree_min_capacity, left->getMin());
    }
    if (right) {
        size_of_subtree += right->getSize();
        subtree_capacity = right->getSubtreeCapacity();
        subtree_min_capacity = std::min(subtree_min_capacity, right->getMin());
    }
}

void Node::push() {
    edge_capacity -= remove_capacity_value;
    if (left) {
        left->removeCapacity(remove_capacity_value);
    }
    if (right) {
        right->removeCapacity(remove_capacity_value);
    }
    remove_capacity_value = 0;
    updateNodeParams();
}

size_t Node::getSize() const {
    return size_of_subtree;
}

int Node::getMin() const {
    return subtree_min_capacity - remove_capacity_value;
}

size_t Node::getId() const {
    return id;
}

int Node::getCapacity() const {
    return edge_capacity;
}

int Node::getSubtreeCapacity() const {
    return subtree_capacity - remove_capacity_value * static_cast<int>(size_of_subtree);
}
