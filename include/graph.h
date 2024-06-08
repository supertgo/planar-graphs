#include "point.h"
#include <vector>

class Graph {
private:
  unsigned int v_cardinality;
  unsigned int edges_cardinality;
  std::vector<Point> vertices;
  std::vector<std::vector<int>> adj;
  std::vector<std::vector<int>> faces;
  void init_graph();

public:
  Graph();
  void find_faces();
  void print_graph();
};
