import matplotlib.pyplot as plt


def generate_planar_graph(vertices, edges):
    graph = {}
    for i in range(vertices):
        x, y, num_neighbors, *neighbors = map(float, input().split())
        neighbors = [n - 1 for n in neighbors]
        graph[i] = {"x": x, "y": y, "neighbors": neighbors}
    return graph


def draw_planar_graph(graph):
    plt.figure()
    for vertex, data in graph.items():
        x = data["x"]
        y = data["y"]
        plt.plot(x, y, "bo")
        plt.text(x, y, str(vertex), fontsize=12, ha="center")
        for neighbor in data["neighbors"]:
            if neighbor in graph:  # Check if the neighbor vertex exists
                nx = graph[neighbor]["x"]
                ny = graph[neighbor]["y"]
                plt.plot([x, nx], [y, ny], "k-")
    plt.title("Planar Graph")
    plt.axis("equal")
    plt.show()


def main():
    vertices, edges = map(int, input().split())
    graph = generate_planar_graph(vertices, edges)
    draw_planar_graph(graph)


if __name__ == "__main__":
    main()
