#include "graph.h"
#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  Graph *g = new Graph();

  auto f = g->find_faces();

  g->print_graph(f);

  return 0;
}
