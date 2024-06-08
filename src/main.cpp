#include "graph.h"
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  Graph g = Graph();

  g.find_faces();

  g.print_graph();

  return 0;
}
