#ifndef PILHAENCADEADA_H
#define PILHAENCADEADA_H

#include "../ListaSimplesmenteEncadeada/ListaSimplesmenteEncadeada.h"

// Pilha adaptadora (Parte II): composicao com a lista simplesmente encadeada.
// O topo e o inicio da lista, entao empilhar/desempilhar sao O(1).
class PilhaEncadeada {
public:
  PilhaEncadeada();

  // sem copia: os elementos pertencem a lista interna
  PilhaEncadeada(const PilhaEncadeada &) = delete;
  PilhaEncadeada &operator=(const PilhaEncadeada &) = delete;

  ~PilhaEncadeada();

  bool empilhar(Elemento *elemento); // O(1)
  bool desempilhar();                // O(1)
  Elemento *consultarTopo() const;   // O(1)
  bool pilhaCheia() const;           // sempre false (lista encadeada cresce)
  bool pilhaVazia() const;           // O(1)
  int tamanho() const;               // O(1)

private:
  ListaSimplesmenteEncadeada lista; // composicao
};

#endif
