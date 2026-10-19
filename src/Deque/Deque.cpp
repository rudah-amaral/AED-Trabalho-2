#include "Deque.h"

// a lista interna ja nasce vazia
Deque::Deque() : lista() {}

// o destrutor da lista cuida da memoria dos elementos
Deque::~Deque() {}

// as duas pontas do deque sao as duas pontas da lista dupla (O(1))
bool Deque::inserirNoInicio(Elemento *elemento) {
  return lista.inserirNoInicio(elemento);
}

bool Deque::inserirNoFim(Elemento *elemento) {
  return lista.inserirNoFinal(elemento);
}

bool Deque::removerInicio() { return lista.removerPrimeiro(); }

bool Deque::removerFim() { return lista.removerUltimo(); }

// consultar e olhar as pontas, sem remover (O(1))
Elemento *Deque::consultarInicio() const { return lista.obter(0); }

Elemento *Deque::consultarFim() const {
  return lista.obter(lista.tamanho() - 1);
}

// O(1)
bool Deque::vazia() const { return lista.vazia(); }

// O(1)
int Deque::tamanho() const { return lista.tamanho(); }
