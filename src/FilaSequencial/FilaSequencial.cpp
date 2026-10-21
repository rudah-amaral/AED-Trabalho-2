#include "FilaSequencial.h"

// Toda insercao acontece no fim: e isso que garante a ordem FIFO.
void FilaSequencial::enfileirar(Elemento *elemento) {
  this->lista.inserirNoFinal(elemento);
}

// Toda remocao acontece no inicio: sai quem entrou primeiro na fila.
void FilaSequencial::desenfileirar() {
  if (!this->lista.vazia()) {
    this->lista.removerPrimeiro();
  }
}

// O inicio da fila e o indice 0 da lista.
Elemento *FilaSequencial::consultarInicio() const {
  if (this->lista.vazia()) {
    return nullptr;
  }
  return this->lista.obter(0);
}

// A lista dobra a capacidade quando enche, entao a fila nunca fica cheia.
bool FilaSequencial::filaCheia() const { return false; }

bool FilaSequencial::filaVazia() const { return this->lista.vazia(); }
