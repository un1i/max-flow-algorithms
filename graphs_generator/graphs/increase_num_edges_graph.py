import networkx as nx
from graphs.graph import Graph


class IncreaseNumEdgesGraph(Graph):
    def __init__(self, name: str, n: int, start: int, finish: int, step: int):
        super().__init__(name, start, finish, step)
        self.n = n

    def _generate_graph(self, m: int) -> nx.Graph:
        return nx.gnm_random_graph(self.n, m, directed=False)
