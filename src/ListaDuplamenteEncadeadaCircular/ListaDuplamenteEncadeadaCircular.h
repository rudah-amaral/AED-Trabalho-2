#ifndef LISTADUPLAMENTEENCADEADACIRCULAR_H
#define LISTADUPLAMENTEENCADEADACIRCULAR_H

#include "../Lista/Lista.h"

// Lista duplamente encadeada circular, com o no encapsulado.
// O primeiro no e a cabeca; o ultimo e cabeca->anterior.
class ListaDuplamenteEncadeadaCircular : public Lista {
public:
  ListaDuplamenteEncadeadaCircular();

  // sem copia: a lista e dona dos ponteiros (evita double delete)
  ListaDuplamenteEncadeadaCircular(const ListaDuplamenteEncadeadaCircular &) =
      delete;
  ListaDuplamenteEncadeadaCircular &
  operator=(const ListaDuplamenteEncadeadaCircular &) = delete;

  ~ListaDuplamenteEncadeadaCircular() override;

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
  class No {
  public:
    Elemento *dado;
    No *proximo;
    No *anterior;

    No(Elemento *dado) : dado(dado), proximo(nullptr), anterior(nullptr) {}
  };

  No *cabeca; // primeiro no (nullptr se a lista estiver vazia)
  int quantidade;
};

#endif
