#ifndef LISTASIMPLESMENTEENCADEADA_H
#define LISTASIMPLESMENTEENCADEADA_H

#include "../Lista/Lista.h"

// Lista simplesmente encadeada, com o no encapsulado (classe privada).
// A lista e dona dos Elementos* (o destrutor libera tudo).
class ListaSimplesmenteEncadeada : public Lista {
public:
  ListaSimplesmenteEncadeada();

  // sem copia: a lista e dona dos ponteiros (evita double delete)
  ListaSimplesmenteEncadeada(const ListaSimplesmenteEncadeada &) = delete;
  ListaSimplesmenteEncadeada &
  operator=(const ListaSimplesmenteEncadeada &) = delete;

  ~ListaSimplesmenteEncadeada() override;

  bool inserirNoInicio(Elemento *elemento) override; // O(1)
  bool inserirNoFinal(Elemento *elemento) override;  // O(1) - com cauda

  bool removerPrimeiro() override;     // O(1)
  bool removerUltimo() override;       // O(n) - precisa achar o penultimo
  bool removerPeloId(int id) override; // O(n)

  Elemento *buscarPeloId(int id) const override;       // O(n)
  bool alterarPeloId(int id, Elemento *novo) override; // O(n)

  Elemento *obter(int indice) const; // O(n)
  int tamanho() const;               // O(1)
  bool vazia() const;                // O(1)

private:
  // No privado: o usuario da lista nao enxerga esse detalhe.
  class No {
  public:
    Elemento *dado;
    No *proximo;

    No(Elemento *dado) : dado(dado), proximo(nullptr) {}
  };

  No *inicio; // primeiro no
  No *fim;    // ultimo no (permite inserir no final em O(1))
  int quantidade;
};

#endif
