import networkx as nx
from graphs.graph import Graph


class CompleteGraph(Graph):
    def __init__(self, name: str, start: int, finish: int, step: int):
        super().__init__(name, start, finish, step)

    def _generate_graph(self, n: int) -> nx.Graph:
        return nx.complete_graph(n)
