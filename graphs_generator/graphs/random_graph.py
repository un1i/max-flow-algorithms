import networkx as nx
from graphs.graph import Graph


class RandomGraph(Graph):
    def __init__(self, name: str, p: float, start: int, finish: int, step: int):
        super().__init__(name, start, finish, step)
        self.p = p

    def _generate_graph(self, n: int) -> nx.Graph:
        return nx.erdos_renyi_graph(n, self.p, directed=True)
