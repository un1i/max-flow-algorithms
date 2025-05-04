from pathlib import Path
from matplotlib import pyplot as plt
import numpy as np
from enum import Enum


class ChangeableParam(Enum):
    VERTEX = 'Число вершин'
    EDGE = 'Число ребер'


class PlotGenerator:
    INPUT_DIRNAME = Path('..') / 'experiment' / 'results'
    OUTPUT_DIRNAME = Path('plots')
    ALGORITHMS_NAME = (
        'Эдмондс-Карп',
        'Диниц',
        'МКМ',
        'Мод Эдмондс-Карп',
        'Диниц с динам. деревьями'
    )

    def __init__(self, filename: str, plot_name: str, changeable_param=ChangeableParam.VERTEX):
        self.filename = filename
        self.plot_name = plot_name
        self.changeable_param = changeable_param

    def create_plot(self):
        path = self.INPUT_DIRNAME / self.filename
        with open(path, 'r') as file:
            variable_param = np.array(list(map(int, file.readline().split())))
            algorithms_time = [list(map(int, file.readline().split())) for _ in range(len(self.ALGORITHMS_NAME))]

        fig, ax = plt.subplots()
        for i in range(len(algorithms_time)):
            ax.plot(variable_param, np.array(algorithms_time[i]), label=self.ALGORITHMS_NAME[i])
        ax.set_xlabel(self.changeable_param.value)
        ax.set_ylabel('Время, мс')
        ax.legend(prop={'size': 9}, loc='upper left')

        plt.savefig(self.OUTPUT_DIRNAME / f'{self.filename}.png')
        plt.close(fig)
