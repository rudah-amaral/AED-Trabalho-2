#ifndef GRAFO_H
#define GRAFO_H

#include "../Elemento/Elemento.h"

// Grafo nao direcionado, sem pesos, guardando as duas formas de
// armazenamento ao mesmo tempo (o PDF pede exatamente isso):
//   - matriz de adjacencia: responde "sao vizinhos?" em O(1);
//   - listas de adjacencia: percorrem so os vizinhos (grau e percursos).
//
// O vertice e guardado como Elemento* e o ID do elemento e a chave publica
// (mesmo padrao "PeloId" das outras estruturas). O grafo e dono dos
// Elementos* (o destrutor libera tudo). Copia proibida (double delete).
class Grafo {
public:
  Grafo();

  // sem copia: o grafo e dono dos ponteiros (evita double delete)
  Grafo(const Grafo &) = delete;
  Grafo &operator=(const Grafo &) = delete;

  ~Grafo();

  // adiciona um vertice; false para nulo ou ID repetido
  // O(n^2): a matriz n x n precisa ser alocada e copiada de novo
  bool adicionarVertice(Elemento *elem);

  // liga dois vertices; false se algum ID nao existe, se o destino
  // for o proprio vertice ou se a aresta ja existir
  // O(n): acha os dois indices; depois e O(1)
  bool adicionarAresta(int idA, int idB);

  // consulta na matriz: O(n) para achar os indices + O(1) na matriz
  bool saoVizinhos(int idA, int idB) const;

  // conta os vizinhos percorrendo a lista: O(n) para achar o indice +
  // O(grau); devolve -1 se o ID nao existe
  int grau(int id) const;

  // percursos: imprimem o ID de cada vertice na ordem de visita
  void buscaEmLargura(int idInicio) const;      // O(V + E)
  void buscaEmProfundidade(int idInicio) const; // O(V + E)

  // estado
  int numeroDeVertices() const; // O(1)
  int numeroDeArestas() const;  // O(1)
  bool vazio() const;           // O(1)

  // visualizacao das duas estruturas
  void imprimirMatriz() const; // O(V^2)
  void imprimirListas() const; // O(V + E)

private:
  // No da lista de adjacencia: guarda o INDICE do vertice vizinho.
  // E privado: o usuario do grafo nao enxerga esse detalhe (PDF, Parte II).
  class No {
  public:
    int indice;
    No *proximo;

    No(int indice, No *proximo) : indice(indice), proximo(proximo) {}
  };

  Elemento **vertices; // vetor de ponteiros (o grafo e dono)
  int qtdVertices;     // posicoes validas: 0..qtdVertices-1
  int qtdArestas;      // numero de arestas (cada uma ocupa 2 celulas)
  bool **matriz;       // matriz qtdVertices x qtdVertices
  No **listas;         // uma cabeca de lista por vertice

  // devolve o indice do vertice com esse ID, ou -1 (O(n))
  int indicePeloId(int id) const;

  // cresce vertices, listas e matriz em uma posicao (O(n^2))
  void crescerEstruturas();

  // libera todos os nos das listas e o vetor de cabecas (O(V + E))
  void limparListas();

  // visita em profundidade a partir de um INDICE (O(V + E))
  void dfs(int indice, bool *visitados, bool &primeiro) const;
};

#endif
