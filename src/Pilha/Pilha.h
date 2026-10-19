#ifndef PILHA_H
#define PILHA_H

#include "../ListaNaoOrdenada/ListaNaoOrdenada.h"

// Pilha por composicao: a lista subjacente e quem guarda os elementos.
class Pilha {
public:
  Pilha();

  // sem copia: os elementos pertencem a lista interna
  Pilha(const Pilha &) = delete;
  Pilha &operator=(const Pilha &) = delete;

  ~Pilha();

  bool empilhar(Elemento *elemento); // O(1) amortizado
  bool desempilhar();                // O(1)
  Elemento *consultarTopo() const;   // O(1)
  bool pilhaCheia() const;           // sempre false (a lista cresce)
  bool pilhaVazia() const;           // O(1)
  int tamanho() const;               // O(1)

private:
  ListaNaoOrdenada lista; // composicao ("tem uma" lista)
};

#endif
