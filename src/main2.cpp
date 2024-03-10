#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

struct Ponto {
  double x, y;
};

// Função para calcular o ângulo polar de uma aresta
double anguloPolar(Ponto a, Ponto b) { return atan2(b.y - a.y, b.x - a.x); }

// Função para listar todas as faces em um grafo plano
// void listarFaces(int N, int M, std::vector<Ponto> vertices,
//                  std::vector<std::vector<int>> adjacencias) {
  // Ordenar as arestas adjacentes para cada vértice por ângulo polar
  // for (int i = 0; i < N; ++i) {
  //     std::sort(adjacencias[i].begin(), adjacencias[i].end(), [&](int u, int
  //     v) {
  //         return anguloPolar(vertices[i], vertices[u]) <
  //         anguloPolar(vertices[i], vertices[v]);
  //     });
  // }

  // // Travessia do grafo para encontrar as faces
  // std::vector<std::vector<int>> faces;
  // std::vector<bool> visitado(N, false);
  // for (int i = 0; i < N; ++i) {
  //     for (int j = 0; j < adjacencias[i].size(); ++j) {
  //         int u = i, v = adjacencias[i][j];
  //         if (!visitado[u] || !visitado[v]) {
  //             std::vector<int> face;
  //             int k = j;
  //             do {
  //                 face.push_back(u);
  //                 visitado[u] = true;
  //                 u = v;
  //                 k = (k + 1) % adjacencias[u].size();
  //                 v = adjacencias[u][k];
  //             } while (u != i || v != adjacencias[i][j]);
  //             faces.push_back(face);
  //         }
  //     }
  // }

  // // Imprimir as faces
  // std::cout << faces.size() << std::endl;
  // for (const auto& face : faces) {
  //     std::cout << face.size() << " ";
  //     for (int v : face) {
  //         std::cout << v + 1 << " "; // Adicionando 1 para ajustar o índice
  //         para 1-indexado
  //     }
  //     std::cout << std::endl;
  // }
  // for (auto &adj : adjacencias) {
  //   std::sort(adj.begin(), adj.end(), [&](int a, int b) {
  //     return anguloPolar(vertices[a], vertices[b]) <
  //            anguloPolar(vertices[b], vertices[a]);
  //   });
  // }

  // std::cout << "passed" << std::endl;

  // Marcação de arestas visitadas
  // std::vector<std::pair<int, int>> arestasVisitadas;

  // Função auxiliar para encontrar a próxima aresta a ser visitada
  // auto encontrarProximaAresta = [&](int u, int v) {
  //   auto it = std::find(adjacencias[u].begin(), adjacencias[u].end(), v);
  //   if (it != adjacencias[u].end()) {
  //     ++it;
  //     if (it == adjacencias[u].end()) {
  //       it = adjacencias[u].begin();
  //     }
  //     return *it;
  //   }
  //   return -1; // Não encontrado
  // };

  // Travessia do grafo para identificar as faces
//   for (int u = 0; u < N; u++) {
//     for (int v : adjacencias[u]) {
//       if (std::find(arestasVisitadas.begin(), arestasVisitadas.end(),
//                     std::make_pair(u, v)) == arestasVisitadas.end()) {
//         std::vector<int> face;
//         int w = v;
//         do {
//           face.push_back(w);
//           int next = encontrarProximaAresta(u, w);
//           arestasVisitadas.push_back(std::make_pair(u, w));
//           u = w;
//           w = next;
//         } while (w != v);

//         // Imprime a face
//         std::cout << "Face: ";
//         for (int i : face) {
//           std::cout << i << " ";
//         }
//         std::cout << std::endl;
//       }
//     }
//   }
// }
// void listarFaces(int N, int M, std::vector<Ponto> vertices,
//                  std::vector<std::vector<int>> adjacencias) {

//  for (auto &adj : adjacencias) {
//     std::sort(adj.begin(), adj.end(), [&](int a, int b) {
//       return anguloPolar(vertices[a], vertices[b]) <
//              anguloPolar(vertices[b], vertices[a]);
//     });
//  }

//  std::cout << "passed" << std::endl;

//  // Marcação de arestas visitadas
//  std::vector<std::pair<int, int>> arestasVisitadas;

//  // Função auxiliar para encontrar a próxima aresta a ser visitada
//  auto encontrarProximaAresta = [&](int u, int v) {
//     auto it = std::find(adjacencias[u].begin(), adjacencias[u].end(), v);
//     if (it != adjacencias[u].end()) {
//       ++it;
//       if (it == adjacencias[u].end()) {
//         it = adjacencias[u].begin();
//       }
//       return *it;
//     }
//     return -1; // Não encontrado
//  };

//  // Travessia do grafo para identificar as faces
//  for (int u = 0; u < N; u++) {
//     for (int v : adjacencias[u]) {
//       if (std::find(arestasVisitadas.begin(), arestasVisitadas.end(),
//                     std::make_pair(u, v)) == arestasVisitadas.end()) {
//         std::vector<int> face;
//         int w = v;
//         do {
//           face.push_back(w);
//           int next = encontrarProximaAresta(u, w);
//           if (next == -1) {
//             break; // Interrompe o loop se a próxima aresta não for encontrada
//           }
//           arestasVisitadas.push_back(std::make_pair(u, w));
//           u = w;
//           w = next;
//         } while (w != v);

//         // Imprime a face
//         std::cout << "Face: ";
//         for (int i : face) {
//           std::cout << i << " ";
//         }
//         std::cout << std::endl;
//       }
//     }
//  }
// }

int main() {
  // Exemplo de leitura dos dados de entrada
  int N, M;
  std::cin >> N >> M;
  std::vector<Ponto> vertices(N);
  std::vector<std::vector<int>> adjacencias(N);
  for (int i = 0; i < N; ++i) {
    std::cin >> vertices[i].x >> vertices[i].y;
    int di;
    std::cin >> di;
    adjacencias[i].resize(di);
    for (int j = 0; j < di; ++j) {
      std::cin >> adjacencias[i][j];
      --adjacencias[i][j]; // Ajustando para 0-indexado
    }
  }

  // Chamar a função para listar as faces
  listarFaces(N, M, vertices, adjacencias);

  return 0;
}
