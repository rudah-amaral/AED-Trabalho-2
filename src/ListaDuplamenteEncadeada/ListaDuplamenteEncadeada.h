#ifndef LISTADUPLAMENTEENCADEADA_H
#define LISTADUPLAMENTEENCADEADA_H

#include "../Lista/Lista.h"

// Lista duplamente encadeada, com o no encapsulado (classe privada).
// A lista e dona dos Elementos* (o destrutor libera tudo).
class ListaDuplamenteEncadeada : public Lista {
public:
  ListaDuplamenteEncadeada();

  // sem copia: a lista e dona dos ponteiros (evita double delete)
  ListaDuplamenteEncadeada(const ListaDuplamenteEncadeada &) = delete;
  ListaDuplamenteEncadeada &
  operator=(const ListaDuplamenteEncadeada &) = delete;

  ~ListaDuplamenteEncadeada() override;

  bool inserirNoInicio(Elemento *elemento) override; // O(1)
  bool inserirNoFinal(Elemento *elemento) override;  // O(1)

  bool removerPrimeiro() override;     // O(1)
  bool removerUltimo() override;       // O(1)
  bool removerPeloId(int id) override; // O(n)

  Elemento *buscarPeloId(int id) const override;       // O(n)
  bool alterarPeloId(int id, Elemento *novo) override; // O(n)

  Elemento *obter(int indice) const; // O(n)
  int tamanho() const;               // O(1)
  bool vazia() const;                // O(1)

private:
  // No com os dois elos: anda para os dois lados.
  class No {
  public:
    Elemento *dado;
    No *proximo;
    No *anterior;

    No(Elemento *dado)
        : dado(dado), proximo(nullptr), anterior(nullptr) {}
  };

  No *inicio;
  No *fim;
  int quantidade;
};

#endif
