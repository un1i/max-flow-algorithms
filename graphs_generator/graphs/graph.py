from abc import ABC, abstractmethod
import random
from pathlib import Path
import networkx as nx


class Graph(ABC):
    DIRNAME = Path('..') / 'experiment' / 'graphs'
    WEIGHT_RANGE: tuple = (1, 100)

    def __init__(self, name: str, start: int, finish: int, step: int):
        self.name = name
        self.gen_range = range(start, finish, step)

    @abstractmethod
    def _generate_graph(self, param: int) -> nx.Graph:
        pass

    def __add_weight_to_edges(self, graph: nx.Graph):
        for u, v in graph.edges():
            graph[u][v]['weight'] = random.randint(*self.WEIGHT_RANGE)

    def _write_graph_to_file(self, file, cur_graph: nx.Graph):
        file.write(f'{cur_graph.number_of_nodes()} {cur_graph.number_of_edges()}\n')
        for u, v, data in cur_graph.edges(data=True):
            file.write(f'{u} {v} {data["weight"]}\n')

    def write_graphs_to_file(self):
        path = Path(self.DIRNAME) / self.name
        num_graphs: int = len(self.gen_range)
        with open(path, 'w') as file:
            file.write(f'{num_graphs}\n')
            for x in self.gen_range:
                cur_graph = self._generate_graph(x)
                self.__add_weight_to_edges(cur_graph)
                self._write_graph_to_file(file, cur_graph)
