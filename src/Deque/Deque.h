#ifndef DEQUE_H
#define DEQUE_H

#include "../ListaDuplamenteEncadeada/ListaDuplamenteEncadeada.h"

// Deque adaptador (Parte II): composicao com a lista duplamente encadeada.
// Todas as operacoes nas pontas sao O(1).
class Deque {
public:
  Deque();

  // sem copia: os elementos pertencem a lista interna
  Deque(const Deque &) = delete;
  Deque &operator=(const Deque &) = delete;

  ~Deque();

  bool inserirNoInicio(Elemento *elemento); // O(1)
  bool inserirNoFim(Elemento *elemento);    // O(1)
  bool removerInicio();                     // O(1)
  bool removerFim();                        // O(1)
  Elemento *consultarInicio() const;        // O(1)
  Elemento *consultarFim() const;           // O(1)
  bool vazia() const;                       // O(1)
  int tamanho() const;                      // O(1)

private:
  ListaDuplamenteEncadeada lista; // composicao
};

#endif
