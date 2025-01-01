#include "graph.h"

size_t Graph::getSource() const {
    return source;
}

size_t Graph::getSink() const {
    return sink;
}

size_t Graph::getNumVertices() const {
    return num_vertices;
}

const GraphAdj& Graph::getAdj() const {
    return adj;
}