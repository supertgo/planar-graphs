#include "point.h"
#include <vector>

class Graph {
private:
  unsigned int v_cardinality;
  unsigned int edges_cardinality;
  std::vector<Point> vertices;
  std::vector<std::vector<int>> adj;
  void init_graph();

public:
  Graph();
  std::vector<std::vector<int>> find_faces();
  void print_graph(std::vector<std::vector<int>> faces);
};
