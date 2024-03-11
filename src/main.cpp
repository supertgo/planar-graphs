#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
  float x, y;

  Point(float x_, float y_) : x(x_), y(y_) {}

  Point operator-(const Point &p) const { return Point(x - p.x, y - p.y); }

  float cross(const Point &p) const { return x * p.y - y * p.x; }

  float cross(const Point &p, const Point &q) const {
    return (p - *this).cross(q - *this);
  }

  int half() const { return int(y < 0 || (y == 0 && x < 0)); }
};

std::vector<std::vector<int>> find_faces(std::vector<Point> vertices,
                                         std::vector<std::vector<int>> adj) {
  int n = vertices.size();
  std::vector<std::vector<char>> used(n);
  for (int i = 0; i < n; i++) {
    used[i].resize(adj[i].size());
    used[i].assign(adj[i].size(), 0);
    auto compare = [&](int l, int r) {
      Point pl = vertices[l] - vertices[i];
      Point pr = vertices[r] - vertices[i];
      if (pl.half() != pr.half())
        return pl.half() < pr.half();
      return pl.cross(pr) > 0;
    };
    std::sort(adj[i].begin(), adj[i].end(), compare);
  }
  std::vector<std::vector<int>> faces;
  for (int i = 0; i < n; i++) {
    for (int edge_id = 0; edge_id < adj[i].size(); edge_id++) {
      if (used[i][edge_id]) {
        continue;
      }
      std::vector<int> face;
      int v = i;
      int e = edge_id;
      while (!used[v][e]) {
        used[v][e] = true;
        face.push_back(v);
        int u = adj[v][e];
        int e1 = std::lower_bound(adj[u].begin(), adj[u].end(), v,
                                  [&](int l, int r) {
                                    Point pl = vertices[l] - vertices[u];
                                    Point pr = vertices[r] - vertices[u];
                                    if (pl.half() != pr.half())
                                      return pl.half() < pr.half();
                                    return pl.cross(pr) > 0;
                                  }) -
                 adj[u].begin() + 1;
        if (e1 == adj[u].size()) {
          e1 = 0;
        }
        v = u;
        e = e1;
      }
      std::reverse(face.begin(), face.end());
      int sign = 0;
      for (int j = 0; j < face.size(); j++) {
        int j1 = (j + 1) % face.size();
        int j2 = (j + 2) % face.size();
        float val =
            vertices[face[j]].cross(vertices[face[j1]], vertices[face[j2]]);
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
int main(int argc, char *argv[]) {
  unsigned int ve, edges, faces;
  float x, y;
  int neighbors;

  std::cin >> ve >> edges;

  faces = edges - ve + 2;

  std::vector<Point> vertices;
  std::vector<std::vector<int>> adj;

  adj.resize(ve);

  for (unsigned int i = 0; i < ve; i++) {
    std::cin >> x >> y >> neighbors;

    vertices.push_back({x, y});
    adj[i].resize(neighbors);

    int n;

    for (int j = 0; j < neighbors; j++) {
      std::cin >> n;
      // -1 cause the starting vertex is 1 by the input
      adj[i][j] = n - 1;
    }
  }

   std::cout << "answer: "<< std::endl;
   std::cout << faces << std::endl;

  auto f = find_faces(vertices, adj);

  for (int i = 0; i < f.size(); i++) {
    std::cout <<  f[i].size() + 1 << " ";
    std::cout <<  f[i][f[i].size() -1] + 1 ;
    for (int j = 0; j < f[i].size(); j++) {
      std::cout << " " << f[i][j] + 1;
    }
    std::cout << std::endl;
  }


  return 0;
}
