from graphs.random_graph import RandomGraph
from graphs.complete_graph import CompleteGraph
from graphs.grid_graph import GridGraph
from graphs.complete_bipartite_graph import CompleteBipartiteGraph
from graphs.increase_num_edges_graph import IncreaseNumEdgesGraph


def main():
    graphs = [
        RandomGraph('dense_graphs', 0.8, 100, 1001, 100),
        RandomGraph('sparse_graphs', 0.1, 500, 5001, 500),
        CompleteGraph('complete_graphs', 100, 1001, 100),
        GridGraph('grid_graphs', 10, 101, 10),
        CompleteBipartiteGraph('complete_bipartite_graphs', 50, 501, 50),
        IncreaseNumEdgesGraph('increase_num_edges_graphs', 3000, 100000, 1000001, 100000)
    ]
    for graph in graphs:
        graph.write_graphs_to_file()


if __name__ == '__main__':
    main()
