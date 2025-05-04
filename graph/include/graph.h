#ifndef MAXFLOW_GRAPH_H
#define MAXFLOW_GRAPH_H

#include "edge_adj.h"

#include <utility>
#include <vector>


using GraphAdj = std::vector<std::vector<EdgeAdj>>;

class Graph {
private:
    size_t source;
    size_t sink;
    size_t num_vertices;
    size_t num_edges;
    GraphAdj adj;

public:
    Graph() : adj{}, source{0}, sink{0}, num_vertices{0}, num_edges{0} {}
    Graph(size_t num_vertices, size_t num_edges, GraphAdj  adj, size_t source, size_t sink) :
    num_vertices{num_vertices}, num_edges{num_edges}, adj{std::move(adj)}, source{source}, sink{sink} {}
    size_t getSource() const;
    size_t getSink() const;
    size_t getNumVertices() const;
    size_t getNumEdges() const;
    const GraphAdj& getAdj() const;
};

#endif //MAXFLOW_GRAPH_H
