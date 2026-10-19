#include "ListaSimplesmenteEncadeada.h"

// lista vazia: inicio e fim nulos
ListaSimplesmenteEncadeada::ListaSimplesmenteEncadeada()
    : inicio(nullptr), fim(nullptr), quantidade(0) {}

// libera os nos e os elementos (O(n))
ListaSimplesmenteEncadeada::~ListaSimplesmenteEncadeada() {
  No *atual = inicio;
  while (atual != nullptr) {
    No *proximo = atual->proximo;
    delete atual->dado;
    delete atual;
    atual = proximo;
  }
}

// o novo no vira o primeiro (O(1))
bool ListaSimplesmenteEncadeada::inserirNoInicio(Elemento *elemento) {
  if (elemento == nullptr) {
    return false;
  }

  No *novo = new No(elemento);
  novo->proximo = inicio;
  inicio = novo;
  if (fim == nullptr) {
    fim = novo;
  }
  ++quantidade;
  return true;
}

// usa a cauda: nao precisa percorrer (O(1))
bool ListaSimplesmenteEncadeada::inserirNoFinal(Elemento *elemento) {
  if (elemento == nullptr) {
    return false;
  }

  No *novo = new No(elemento);
  if (fim == nullptr) {
    inicio = novo;
  } else {
    fim->proximo = novo;
  }
  fim = novo;
  ++quantidade;
  return true;
}

// tira o primeiro no (O(1))
bool ListaSimplesmenteEncadeada::removerPrimeiro() {
  if (vazia()) {
    return false;
  }

  No *removido = inicio;
  inicio = inicio->proximo;
  if (inicio == nullptr) {
    fim = nullptr;
  }
  --quantidade;
  delete removido->dado;
  delete removido;
  return true;
}

// sem elo anterior, precisa achar o penultimo (O(n))
bool ListaSimplesmenteEncadeada::removerUltimo() {
  if (vazia()) {
    return false;
  }

  if (inicio == fim) { // so um no
    delete inicio->dado;
    delete inicio;
    inicio = nullptr;
    fim = nullptr;
    --quantidade;
    return true;
  }

  No *anterior = inicio;
  while (anterior->proximo != fim) {
    anterior = anterior->proximo;
  }
  delete fim->dado;
  delete fim;
  fim = anterior;
  fim->proximo = nullptr;
  --quantidade;
  return true;
}

// busca linear; religa o anterior no proximo (O(n))
bool ListaSimplesmenteEncadeada::removerPeloId(int id) {
  No *anterior = nullptr;
  No *atual = inicio;

  while (atual != nullptr && atual->dado->getID() != id) {
    anterior = atual;
    atual = atual->proximo;
  }
  if (atual == nullptr) {
    return false;
  }

  if (anterior == nullptr) {
    inicio = atual->proximo;
  } else {
    anterior->proximo = atual->proximo;
  }
  if (atual == fim) {
    fim = anterior;
  }
  --quantidade;
  delete atual->dado;
  delete atual;
  return true;
}

// busca linear (O(n))
Elemento *ListaSimplesmenteEncadeada::buscarPeloId(int id) const {
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
bool ListaSimplesmenteEncadeada::alterarPeloId(int id, Elemento *novo) {
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
Elemento *ListaSimplesmenteEncadeada::obter(int indice) const {
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
int ListaSimplesmenteEncadeada::tamanho() const { return quantidade; }

// O(1)
bool ListaSimplesmenteEncadeada::vazia() const { return quantidade == 0; }
