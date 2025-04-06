import networkx as nx
from graphs.graph import Graph


class GridGraph(Graph):
    def __init__(self, name: str, start: int, finish: int, step: int):
        super().__init__(name, start, finish, step)

    def _generate_graph(self, n: int) -> nx.Graph:
        self.n = n
        return nx.grid_2d_graph(n, n)

    def _write_graph_to_file(self, file, cur_graph: nx.Graph):
        file.write(f'{cur_graph.number_of_nodes()} {cur_graph.number_of_edges()}\n')
        for u, v, data in cur_graph.edges(data=True):
            file.write(f'{u[0] * self.n + u[1]} {v[0] * self.n + v[1]} {data["weight"]}\n')
