#include "PilhaEncadeada.h"

// a lista interna ja nasce vazia
PilhaEncadeada::PilhaEncadeada() : lista() {}

// o destrutor da lista cuida da memoria dos elementos
PilhaEncadeada::~PilhaEncadeada() {}

// o topo e o inicio da lista: inserir no inicio e O(1)
bool PilhaEncadeada::empilhar(Elemento *elemento) {
  return lista.inserirNoInicio(elemento);
}

// desempilhar e remover o primeiro no (O(1))
bool PilhaEncadeada::desempilhar() { return lista.removerPrimeiro(); }

// consultar o topo e olhar a posicao 0 (O(1))
Elemento *PilhaEncadeada::consultarTopo() const { return lista.obter(0); }

// lista encadeada cresce enquanto houver memoria: nunca fica cheia
bool PilhaEncadeada::pilhaCheia() const { return false; }

// O(1)
bool PilhaEncadeada::pilhaVazia() const { return lista.vazia(); }

// O(1)
int PilhaEncadeada::tamanho() const { return lista.tamanho(); }
