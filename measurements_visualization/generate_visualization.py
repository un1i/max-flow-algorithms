from plot_generator import PlotGenerator
from plot_generator import ChangeableParam


def main():
    generators = [
        PlotGenerator('complete_bipartite_graphs_result', 'Полный двудольный граф'),
        PlotGenerator('complete_graphs_result', 'Полный граф'),
        PlotGenerator('dense_graphs_result', 'Плотный граф'),
        PlotGenerator('grid_graphs_result', 'Сеточный граф'),
        PlotGenerator('increase_num_edges_graphs_result', 'Случайный граф', ChangeableParam.EDGE),
        PlotGenerator('sparse_graphs_result', 'Разреженный граф'),
    ]

    for gen in generators:
        gen.create_plot()


if __name__ == '__main__':
    main()
