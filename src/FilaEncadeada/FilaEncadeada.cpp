#include "FilaEncadeada.h"

// a lista interna ja nasce vazia
FilaEncadeada::FilaEncadeada() : lista() {}

// o destrutor da lista cuida da memoria dos elementos
FilaEncadeada::~FilaEncadeada() {}

// a entrada e o fim da lista: inserir no final usa a cauda O(1)
bool FilaEncadeada::enfileirar(Elemento *elemento) {
  return lista.inserirNoFinal(elemento);
}

// a saida e o inicio da lista: remover o primeiro no com O(1)
bool FilaEncadeada::desenfileirar() { return lista.removerPrimeiro(); }

// o inicio da fila e a posicao 0; obter(0) nao percorre nada O(1)
// e devolve nullptr se a fila estiver vazia
Elemento *FilaEncadeada::consultarInicio() const { return lista.obter(0); }

// lista encadeada cresce enquanto houver memoria: nunca fica cheia
bool FilaEncadeada::filaCheia() const { return false; }

// O(1)
bool FilaEncadeada::filaVazia() const { return lista.vazia(); }
