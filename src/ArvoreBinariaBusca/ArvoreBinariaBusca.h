#ifndef ARVOREBINARIABUSCA_H
#define ARVOREBINARIABUSCA_H

#include "../Elemento/Elemento.h"

// Arvore binaria de busca ordenada pelo ID.
// A arvore e dona dos Elementos* (o destrutor libera tudo).
// h = altura: inserir, buscar e remover sao O(h).
class ArvoreBinariaBusca {
public:
  ArvoreBinariaBusca();

  // sem copia: a arvore e dona dos ponteiros (evita double delete)
  ArvoreBinariaBusca(const ArvoreBinariaBusca &) = delete;
  ArvoreBinariaBusca &operator=(const ArvoreBinariaBusca &) = delete;

  ~ArvoreBinariaBusca();

  // insere na posicao ditada pelo ID; false para nulo ou duplicado
  bool inserir(Elemento *elem); // O(h)

  // devolve o elemento do ID ou nullptr
  Elemento *buscarPeloId(int id) const; // O(h)

  // remove e destroi o elemento do ID
  bool removerPeloId(int id); // O(h)

  // percursos: imprimem o ID de cada no
  void emOrdem() const;  // O(n)
  void preOrdem() const; // O(n)
  void posOrdem() const; // O(n)

  int altura() const; // O(n)
  int tamanho() const; // O(1)
  bool vazia() const;  // O(1)

private:
  // No privado: o usuario da arvore nao enxerga esse detalhe.
  class No {
  public:
    Elemento *dado;
    No *esq;
    No *dir;

    explicit No(Elemento *dado) : dado(dado), esq(nullptr), dir(nullptr) {}
  };

  No *raiz;
  int qtd;

  No *insere(No *no, Elemento *elem, bool &ok); // O(h)
  const No *busca(const No *no, int id) const;  // O(h)
  No *remove(No *no, int id, bool &ok);         // O(h)
  No *minimo(No *no) const;                     // O(h)
  No *removeMin(No *no);                        // O(h)
  void limpa(No *no);                           // O(n)
  void emOrdemNo(const No *no) const;           // O(n)
  void preOrdemNo(const No *no) const;          // O(n)
  void posOrdemNo(const No *no) const;          // O(n)
  int alturaNo(const No *no) const;             // O(n)
};

#endif
