#include "graph.h"
#include <algorithm>
#include <iostream>

Graph::Graph() {
  unsigned int v_cardinality, edges_cardinality;
  std::cin >> v_cardinality >> edges_cardinality;

  this->v_cardinality = v_cardinality;
  this->edges_cardinality = edges_cardinality;

  this->init_graph();
}

void Graph::init_graph() {
  float x, y;
  int neighbohrs;

  this->adj.resize(this->v_cardinality);

  for (unsigned int i = 0; i < this->v_cardinality; i++) {
    std::cin >> x >> y >> neighbohrs;

    this->vertices.push_back({x, y});
    this->adj[i].resize(neighbohrs);

    int current_neighbor;

    for (int j = 0; j < neighbohrs; j++) {
      std::cin >> current_neighbor;
      // -1 cause the starting vertices is 1 by the input
      this->adj[i][j] = current_neighbor - 1;
    }
  }
}

std::vector<std::vector<int>> Graph::find_faces() {
  int n = this->vertices.size();
  std::vector<std::vector<char>> used(n);

  for (int i = 0; i < n; i++) {
    used[i].resize(this->adj[i].size());
    used[i].assign(this->adj[i].size(), 0);
    auto compare = [&](int l, int r) {
      Point pl = this->vertices[l] - this->vertices[i];
      Point pr = this->vertices[r] - this->vertices[i];
      if (pl.half() != pr.half())
        return pl.half() < pr.half();
      return pl.cross(pr) > 0;
    };
    std::sort(this->adj[i].begin(), this->adj[i].end(), compare);
  }

  std::vector<std::vector<int>> faces;
  for (int i = 0; i < n; i++) {
    for (unsigned int edge_id = 0; edge_id < this->adj[i].size(); edge_id++) {
      if (used[i][edge_id]) {
        continue;
      }
      std::vector<int> face;
      int v = i;
      int e = edge_id;
      while (!used[v][e]) {
        used[v][e] = true;
        face.push_back(v);
        int u = this->adj[v][e];
        size_t e1 =
            std::lower_bound(this->adj[u].begin(), this->adj[u].end(), v,
                             [&](int l, int r) {
                               Point pl = this->vertices[l] - this->vertices[u];
                               Point pr = this->vertices[r] - this->vertices[u];
                               if (pl.half() != pr.half())
                                 return pl.half() < pr.half();
                               return pl.cross(pr) > 0;
                             }) -
            this->adj[u].begin() + 1;
        if (e1 == this->adj[u].size()) {
          e1 = 0;
        }
        v = u;
        e = e1;
      }

      std::reverse(face.begin(), face.end());
      int sign = 0;
      for (unsigned int j = 0; j < face.size(); j++) {
        int j1 = (j + 1) % face.size();
        int j2 = (j + 2) % face.size();
        float val = this->vertices[face[j]].cross(this->vertices[face[j1]],
                                                  this->vertices[face[j2]]);
        if (val > 0) {
          sign = 1;
          break;
        } else if (val < 0) {
          sign = -1;
          break;
        }
      }
      if (sign <= 0) {
        faces.insert(faces.begin(), face);
      } else {
        faces.emplace_back(face);
      }
    }
  }
  return faces;
}

void Graph::print_graph(std::vector<std::vector<int>> faces) {
  for (size_t i = 0; i < faces.size(); i++) {
    std::cout << faces[i].size() + 1 << " ";
    std::cout << faces[i][faces[i].size() - 1] + 1;
    for (unsigned int j = 0; j < faces[i].size(); j++) {
      std::cout << " " << faces[i][j] + 1;
    }
    std::cout << std::endl;
  }
}
