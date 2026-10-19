#include "ListaDuplamenteEncadeada.h"

// lista vazia: inicio e fim nulos
ListaDuplamenteEncadeada::ListaDuplamenteEncadeada()
    : inicio(nullptr), fim(nullptr), quantidade(0) {}

// libera os nos e os elementos (O(n))
ListaDuplamenteEncadeada::~ListaDuplamenteEncadeada() {
  No *atual = inicio;
  while (atual != nullptr) {
    No *proximo = atual->proximo;
    delete atual->dado;
    delete atual;
    atual = proximo;
  }
}

// entra antes do inicio; ajusta os dois elos (O(1))
bool ListaDuplamenteEncadeada::inserirNoInicio(Elemento *elemento) {
  if (elemento == nullptr) {
    return false;
  }

  No *novo = new No(elemento);
  novo->proximo = inicio;
  if (inicio != nullptr) {
    inicio->anterior = novo;
  } else {
    fim = novo;
  }
  inicio = novo;
  ++quantidade;
  return true;
}

// entra depois do fim (O(1) gracas a cauda)
bool ListaDuplamenteEncadeada::inserirNoFinal(Elemento *elemento) {
  if (elemento == nullptr) {
    return false;
  }

  No *novo = new No(elemento);
  novo->anterior = fim;
  if (fim != nullptr) {
    fim->proximo = novo;
  } else {
    inicio = novo;
  }
  fim = novo;
  ++quantidade;
  return true;
}

// tira o primeiro no (O(1))
bool ListaDuplamenteEncadeada::removerPrimeiro() {
  if (vazia()) {
    return false;
  }

  No *removido = inicio;
  inicio = inicio->proximo;
  if (inicio != nullptr) {
    inicio->anterior = nullptr;
  } else {
    fim = nullptr;
  }
  --quantidade;
  delete removido->dado;
  delete removido;
  return true;
}

// tira o ultimo no (O(1) gracas ao elo anterior)
bool ListaDuplamenteEncadeada::removerUltimo() {
  if (vazia()) {
    return false;
  }

  No *removido = fim;
  fim = fim->anterior;
  if (fim != nullptr) {
    fim->proximo = nullptr;
  } else {
    inicio = nullptr;
  }
  --quantidade;
  delete removido->dado;
  delete removido;
  return true;
}

// busca linear; religa os vizinhos (O(n))
bool ListaDuplamenteEncadeada::removerPeloId(int id) {
  No *atual = inicio;
  while (atual != nullptr && atual->dado->getID() != id) {
    atual = atual->proximo;
  }
  if (atual == nullptr) {
    return false;
  }

  if (atual->anterior != nullptr) {
    atual->anterior->proximo = atual->proximo;
  } else {
    inicio = atual->proximo;
  }
  if (atual->proximo != nullptr) {
    atual->proximo->anterior = atual->anterior;
  } else {
    fim = atual->anterior;
  }

  --quantidade;
  delete atual->dado;
  delete atual;
  return true;
}

// busca linear (O(n))
Elemento *ListaDuplamenteEncadeada::buscarPeloId(int id) const {
  No *atual = inicio;
  while (atual != nullptr) {
    if (atual->dado->getID() == id) {
      return atual->dado;
    }
    atual = atual->proximo;
  }
  return nullptr;
}

// troca o elemento do ID por outro de mesmo ID; deleta o antigo (O(n))
bool ListaDuplamenteEncadeada::alterarPeloId(int id, Elemento *novo) {
  No *atual = inicio;
  while (atual != nullptr && atual->dado->getID() != id) {
    atual = atual->proximo;
  }
  if (atual == nullptr || novo == nullptr) {
    return false;
  }
  if (novo == atual->dado) {
    return true;
  }
  if (novo->getID() != id) {
    return false;
  }

  delete atual->dado;
  atual->dado = novo;
  return true;
}

// percorre ate a posicao (O(n))
Elemento *ListaDuplamenteEncadeada::obter(int indice) const {
  if (indice < 0 || indice >= quantidade) {
    return nullptr;
  }

  No *atual = inicio;
  for (int i = 0; i < indice; ++i) {
    atual = atual->proximo;
  }
  return atual->dado;
}

// O(1)
int ListaDuplamenteEncadeada::tamanho() const { return quantidade; }

// O(1)
bool ListaDuplamenteEncadeada::vazia() const { return quantidade == 0; }
