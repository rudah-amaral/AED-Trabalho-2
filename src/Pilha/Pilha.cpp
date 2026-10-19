#include "Pilha.h"

// a lista interna ja nasce vazia
Pilha::Pilha() : lista() {}

// o destrutor da lista cuida da memoria dos elementos
Pilha::~Pilha() {}

// o topo da pilha e o fim da lista: inserir no final (O(1) amortizado)
bool Pilha::empilhar(Elemento *elemento) {
  return lista.inserirNoFinal(elemento);
}

// desempilhar e remover o ultimo da lista (O(1))
bool Pilha::desempilhar() { return lista.removerUltimo(); }

// consultar o topo e olhar a ultima posicao valida (O(1))
Elemento *Pilha::consultarTopo() const {
  return lista.obter(lista.tamanho() - 1);
}

// a lista cresce dobrando: a pilha nunca fica cheia
bool Pilha::pilhaCheia() const { return false; }

// O(1)
bool Pilha::pilhaVazia() const { return lista.vazia(); }

// O(1)
int Pilha::tamanho() const { return lista.tamanho(); }
