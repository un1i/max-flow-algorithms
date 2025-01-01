#include "edge_adj.h"

#include <vector>


using GraphAdj = std::vector<std::vector<EdgeAdj>>;

class Graph {
private:
    size_t source;
    size_t sink;
    size_t num_vertices;
    GraphAdj adj;

public:
    Graph(const GraphAdj& adj, size_t source, size_t sink) : adj{adj}, source{source},
    sink{sink}, num_vertices{adj.size()} {}
    size_t getSource() const;
    size_t getSink() const;
    size_t getNumVertices() const;
    const GraphAdj& getAdj() const;
};
