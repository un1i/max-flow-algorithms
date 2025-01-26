#include "dinic_with_dynamic_tree.h"

#include <climits>


DinicWithDynamicTree::DinicWithDynamicTree(const Graph &graph) : Dinic(graph),
link_cut(graph.getNumVertices()) {}

void DinicWithDynamicTree::run() {
    int flow = 0;
    std::vector<int> distance(graph.getNumVertices());
    std::vector<int> free_edge_ind(graph.getNumVertices());

    EdgeAvailableCapacity available_capacity = getAvailableCapacity();
    EdgeInTree edge_in_tree;

    while (bfs(distance, available_capacity)) {
        link_cut.clearTrees();
        edge_in_tree.clear();
        std::fill(free_edge_ind.begin(), free_edge_ind.end(), 0);
        auto adj = graph.getAdj();
        size_t vertex;
        size_t next;
        size_t prev;
        while (true) {
            if ((vertex = link_cut.findRoot(graph.getSource())->getId()) != graph.getSink()) {
                while (free_edge_ind[vertex] < adj[vertex].size() &&
                distance[vertex] + 1 != distance[adj[vertex][free_edge_ind[vertex]].end]) {
                    free_edge_ind[vertex]++;
                }
                if (free_edge_ind[vertex] != graph.getAdj()[vertex].size()) {
                    next = graph.getAdj().at(vertex)[free_edge_ind[vertex]].end;
                    addEdge(vertex, next, available_capacity, edge_in_tree);
                }
                else {
                    if (vertex == graph.getSource()) {
                        break;
                    }
                    else {
                        prev = link_cut.prevInPath(graph.getSource())->getId();
                        removeEdge(vertex, prev, available_capacity, free_edge_ind, edge_in_tree);
                    }
                }
            }
            else {
                Node* min_edge = link_cut.getMinEdge(graph.getSource());
                flow += min_edge->getCapacity();
                decreaseCapacityInPath(min_edge, available_capacity, free_edge_ind, edge_in_tree);
            }
        }
        updateAvailableCapacity(edge_in_tree, available_capacity);
    }
    max_flow = flow;
}

void DinicWithDynamicTree::addEdge(size_t cur, size_t next, const EdgeAvailableCapacity &available_capacity,
                                   EdgeInTree& edge_in_tree) {
    link_cut.setCapacity(cur, available_capacity.at(cur).at(next));
    link_cut.link(cur, next);
    link_cut.findRoot(graph.getSource());
    link_cut.setCapacity(link_cut.findRoot(graph.getSource())->getId(), INT_MAX);
    edge_in_tree[cur].insert(next);
}

void DinicWithDynamicTree::removeEdge(size_t cur, size_t prev, EdgeAvailableCapacity &available_capacity,
                                      std::vector<int> &first_edge_ind, EdgeInTree& edge_in_tree) {
    link_cut.cut(prev, cur);
    int edge_capacity = link_cut.getEdgeCapacity(prev);
    available_capacity[cur][prev] += available_capacity[prev][cur] - edge_capacity;
    available_capacity[prev][cur] = edge_capacity;
    link_cut.setCapacity(prev, INT_MAX);
    first_edge_ind[prev]++;
    edge_in_tree[prev].erase(cur);
}

void DinicWithDynamicTree::decreaseCapacityInPath(Node *min_edge, EdgeAvailableCapacity &available_capacity,
                                                  std::vector<int> &first_edge_ind, EdgeInTree& edge_in_tree) {
    size_t min_vertex;
    link_cut.removeCapacityInPath(min_edge->getCapacity(), graph.getSource());
    while (link_cut.getEdgeCapacity((min_edge = link_cut.getMinEdge(graph.getSource()))->getId()) == 0) {
        min_vertex = min_edge->getId();
        size_t next = graph.getAdj()[min_vertex][first_edge_ind[min_vertex]].end;
        available_capacity[next][min_vertex] += available_capacity[min_vertex][next];
        available_capacity[min_vertex][next] = 0;
        link_cut.cut(min_vertex, next);
        link_cut.setCapacity(min_vertex, INT_MAX);
        first_edge_ind[min_vertex]++;
        edge_in_tree[min_vertex].erase(next);
        if (min_vertex == graph.getSource()) {
            break;
        }
    }
}

void DinicWithDynamicTree::updateAvailableCapacity(EdgeInTree &edge_in_tree, EdgeAvailableCapacity &availableCapacity) {
    for (const auto& [begin, ends] : edge_in_tree) {
        for (int end : ends) {
            int edge_capacity = link_cut.getEdgeCapacity(begin);
            availableCapacity[end][begin] += availableCapacity[begin][end] - edge_capacity;
            availableCapacity[begin][end] = edge_capacity;
        }
    }
}
