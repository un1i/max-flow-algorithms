from graphs.random_graph import RandomGraph
from graphs.complete_graph import CompleteGraph
from graphs.grid_graph import GridGraph
from graphs.complete_bipartite_graph import CompleteBipartiteGraph
from graphs.increase_num_edges_graph import IncreaseNumEdgesGraph


def main():
    start = 10
    finish = 100
    step = 10
    graphs = [
        RandomGraph('dense_graphs', 0.8, start, finish, step),
        RandomGraph('sparse_graphs', 0.1, start, finish, step),
        CompleteGraph('complete_graphs', start, finish, step),
        GridGraph('grid_graphs', start, finish, step),
        CompleteBipartiteGraph('complete_bipartite_graphs', start, finish, step),
        IncreaseNumEdgesGraph('increase_num_edges_graphs', 100, 500, 5000, 500)
    ]
    for graph in graphs:
        graph.write_graphs_to_file()


if __name__ == '__main__':
    main()
