#include "Grafo.h"

#include <iostream>

// grafo vazio: nenhum vertice, nenhuma aresta, nenhum bloco alocado
Grafo::Grafo()
    : vertices(nullptr), qtdVertices(0), qtdArestas(0), matriz(nullptr),
      listas(nullptr) {}

// libera os elementos, os nos das listas, as linhas da matriz e os blocos
// (O(V + E + V^2), ou seja, O(V^2) por causa da matriz)
Grafo::~Grafo() {
  for (int i = 0; i < qtdVertices; ++i) {
    delete vertices[i];
  }
  delete[] vertices;

  limparListas();

  for (int i = 0; i < qtdVertices; ++i) {
    delete[] matriz[i];
  }
  delete[] matriz;
}

// busca linear no vetor de vertices (O(n))
int Grafo::indicePeloId(int id) const {
  for (int i = 0; i < qtdVertices; ++i) {
    if (vertices[i]->getID() == id) {
      return i;
    }
  }
  return -1;
}

// aloca tudo com uma posicao a mais, copia o que existia e substitui.
// A matriz e quadrada: crescer de n para n+1 custa O(n^2).
void Grafo::crescerEstruturas() {
  int novoN = qtdVertices + 1;

  // matriz nova (novoN x novoN), toda zerada
  bool **novaMatriz = new bool *[novoN];
  for (int i = 0; i < novoN; ++i) {
    novaMatriz[i] = new bool[novoN]();
  }

  // copia a parte antiga (qtdVertices x qtdVertices)
  for (int i = 0; i < qtdVertices; ++i) {
    for (int j = 0; j < qtdVertices; ++j) {
      novaMatriz[i][j] = matriz[i][j];
    }
  }

  // vetor de vertices e vetor de cabecas das listas, ambos com novoN
  Elemento **novosVertices = new Elemento *[novoN]();
  No **novasListas = new No *[novoN]();

  for (int i = 0; i < qtdVertices; ++i) {
    novosVertices[i] = vertices[i];
    novasListas[i] = listas[i];
  }

  // so depois de tudo copiado os blocos antigos sao liberados
  for (int i = 0; i < qtdVertices; ++i) {
    delete[] matriz[i];
  }
  delete[] matriz;
  delete[] vertices;
  delete[] listas;

  matriz = novaMatriz;
  vertices = novosVertices;
  listas = novasListas;
  qtdVertices = novoN;
}

// valida o ponteiro e o ID, cresce as estruturas e grava o novo vertice
// no fim do vetor (O(n^2) por causa da matriz)
bool Grafo::adicionarVertice(Elemento *elem) {
  if (elem == nullptr) {
    return false;
  }

  // ID duplicado nao entra; a posse continua com o chamador
  if (indicePeloId(elem->getID()) != -1) {
    return false;
  }

  crescerEstruturas();
  vertices[qtdVertices - 1] = elem;
  return true;
}

// liga dois vertices nas DUAS estruturas, mantendo-as em sincronia (O(n))
bool Grafo::adicionarAresta(int idA, int idB) {
  int a = indicePeloId(idA);
  int b = indicePeloId(idB);

  // algum dos dois nao existe
  if (a == -1 || b == -1) {
    return false;
  }

  // laco (vertice ligado a ele mesmo) nao entra
  if (a == b) {
    return false;
  }

  // aresta repetida: a matriz ja diz que sao vizinhos
  if (matriz[a][b]) {
    return false;
  }

  // matriz: como o grafo nao e direcionado, marca os dois lados
  matriz[a][b] = true;
  matriz[b][a] = true;

  // listas: insere na cabeca (O(1)) dos dois lados
  listas[a] = new No(b, listas[a]);
  listas[b] = new No(a, listas[b]);

  ++qtdArestas;
  return true;
}

// a matriz responde a pergunta em O(1); o custo e achar os indices (O(n))
bool Grafo::saoVizinhos(int idA, int idB) const {
  int a = indicePeloId(idA);
  int b = indicePeloId(idB);

  if (a == -1 || b == -1) {
    return false;
  }

  return matriz[a][b];
}

// grau = quantos vizinhos o vertice tem (O(n) para o indice + O(grau))
int Grafo::grau(int id) const {
  int indice = indicePeloId(id);
  if (indice == -1) {
    return -1;
  }

  int total = 0;
  for (No *atual = listas[indice]; atual != nullptr; atual = atual->proximo) {
    ++total;
  }
  return total;
}

// BFS: fila simples em array, marca antes de enfileirar (O(V + E))
void Grafo::buscaEmLargura(int idInicio) const {
  int inicio = indicePeloId(idInicio);
  if (inicio == -1) {
    std::cout << "Vertice " << idInicio << " nao existe.\n";
    return;
  }

  bool *visitados = new bool[qtdVertices]();
  int *fila = new int[qtdVertices];
  int frente = 0;
  int tras = 0;

  visitados[inicio] = true;
  fila[tras++] = inicio;

  std::cout << "Busca em largura a partir do ID " << idInicio << ": ";
  bool primeiro = true;

  while (frente < tras) {
    int atual = fila[frente++];

    if (!primeiro) {
      std::cout << " ";
    }
    std::cout << vertices[atual]->getID();
    primeiro = false;

    // enfileira cada vizinho ainda nao visitado, na ordem da lista
    for (No *vizinho = listas[atual]; vizinho != nullptr;
         vizinho = vizinho->proximo) {
      if (!visitados[vizinho->indice]) {
        visitados[vizinho->indice] = true;
        fila[tras++] = vizinho->indice;
      }
    }
  }

  std::cout << "\n";
  delete[] fila;
  delete[] visitados;
}

// DFS: recursiva, segue um vizinho ate o fim antes de voltar (O(V + E))
void Grafo::buscaEmProfundidade(int idInicio) const {
  int inicio = indicePeloId(idInicio);
  if (inicio == -1) {
    std::cout << "Vertice " << idInicio << " nao existe.\n";
    return;
  }

  bool *visitados = new bool[qtdVertices]();
  bool primeiro = true;

  std::cout << "Busca em profundidade a partir do ID " << idInicio << ": ";
  dfs(inicio, visitados, primeiro);
  std::cout << "\n";

  delete[] visitados;
}

// visita o vertice e desce para o primeiro vizinho nao visitado (O(V + E))
void Grafo::dfs(int indice, bool *visitados, bool &primeiro) const {
  visitados[indice] = true;

  if (!primeiro) {
    std::cout << " ";
  }
  std::cout << vertices[indice]->getID();
  primeiro = false;

  for (No *vizinho = listas[indice]; vizinho != nullptr;
       vizinho = vizinho->proximo) {
    if (!visitados[vizinho->indice]) {
      dfs(vizinho->indice, visitados, primeiro);
    }
  }
}

// O(1)
int Grafo::numeroDeVertices() const { return qtdVertices; }

// O(1)
int Grafo::numeroDeArestas() const { return qtdArestas; }

// O(1)
bool Grafo::vazio() const { return qtdVertices == 0; }

// imprime a matriz inteira, com o ID de cada vertice no cabecalho (O(V^2))
void Grafo::imprimirMatriz() const {
  if (vazio()) {
    std::cout << "Grafo sem vertices.\n";
    return;
  }

  std::cout << "Matriz de adjacencia (1 = vizinho, 0 = nao):\n";
  std::cout << "       ";
  for (int j = 0; j < qtdVertices; ++j) {
    std::cout << " " << vertices[j]->getID();
  }
  std::cout << "\n";

  for (int i = 0; i < qtdVertices; ++i) {
    std::cout << "ID " << vertices[i]->getID() << ": ";
    for (int j = 0; j < qtdVertices; ++j) {
      std::cout << " " << (matriz[i][j] ? 1 : 0);
    }
    std::cout << "\n";
  }
}

// percorre as listas mostrando os vizinhos de cada vertice (O(V + E))
void Grafo::imprimirListas() const {
  if (vazio()) {
    std::cout << "Grafo sem vertices.\n";
    return;
  }

  std::cout << "Listas de adjacencia:\n";
  for (int i = 0; i < qtdVertices; ++i) {
    std::cout << "ID " << vertices[i]->getID() << ": ";

    No *atual = listas[i];
    if (atual == nullptr) {
      std::cout << "(sem vizinhos)";
    }
    while (atual != nullptr) {
      std::cout << vertices[atual->indice]->getID();
      atual = atual->proximo;
      if (atual != nullptr) {
        std::cout << ", ";
      }
    }
    std::cout << "\n";
  }
}

// libera os nos de todas as listas e o vetor de cabecas (O(V + E))
void Grafo::limparListas() {
  for (int i = 0; i < qtdVertices; ++i) {
    No *atual = listas[i];
    while (atual != nullptr) {
      No *proximo = atual->proximo;
      delete atual;
      atual = proximo;
    }
  }
  delete[] listas;
  listas = nullptr;
}
