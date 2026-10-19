#include "ListaDuplamenteEncadeadaCircular.h"

// lista vazia: cabeca nula
ListaDuplamenteEncadeadaCircular::ListaDuplamenteEncadeadaCircular()
    : cabeca(nullptr), quantidade(0) {}

// percorre o circulo liberando nos e elementos (O(n))
ListaDuplamenteEncadeadaCircular::~ListaDuplamenteEncadeadaCircular() {
  if (cabeca == nullptr) {
    return;
  }

  No *atual = cabeca;
  do {
    No *proximo = atual->proximo;
    delete atual->dado;
    delete atual;
    atual = proximo;
  } while (atual != cabeca);
}

// na lista vazia o no aponta para ele mesmo (circulo de um) (O(1))
bool ListaDuplamenteEncadeadaCircular::inserirNoInicio(Elemento *elemento) {
  if (elemento == nullptr) {
    return false;
  }

  No *novo = new No(elemento);
  if (cabeca == nullptr) {
    novo->proximo = novo;
    novo->anterior = novo;
    cabeca = novo;
  } else {
    No *ultimo = cabeca->anterior;
    novo->proximo = cabeca;
    novo->anterior = ultimo;
    ultimo->proximo = novo;
    cabeca->anterior = novo;
    cabeca = novo;
  }
  ++quantidade;
  return true;
}

// entra antes da cabeca: vira o ultimo (O(1))
bool ListaDuplamenteEncadeadaCircular::inserirNoFinal(Elemento *elemento) {
  if (elemento == nullptr) {
    return false;
  }
  if (cabeca == nullptr) {
    return inserirNoInicio(elemento);
  }

  No *novo = new No(elemento);
  No *ultimo = cabeca->anterior;
  novo->proximo = cabeca;
  novo->anterior = ultimo;
  ultimo->proximo = novo;
  cabeca->anterior = novo;
  ++quantidade;
  return true;
}

// tira a cabeca (O(1))
bool ListaDuplamenteEncadeadaCircular::removerPrimeiro() {
  if (vazia()) {
    return false;
  }

  No *removido = cabeca;
  if (quantidade == 1) {
    cabeca = nullptr;
  } else {
    No *ultimo = cabeca->anterior;
    cabeca = cabeca->proximo;
    cabeca->anterior = ultimo;
    ultimo->proximo = cabeca;
  }
  --quantidade;
  delete removido->dado;
  delete removido;
  return true;
}

// tira o ultimo (cabeca->anterior) (O(1))
bool ListaDuplamenteEncadeadaCircular::removerUltimo() {
  if (vazia()) {
    return false;
  }

  No *removido = cabeca->anterior;
  if (quantidade == 1) {
    cabeca = nullptr;
  } else {
    No *novoUltimo = removido->anterior;
    novoUltimo->proximo = cabeca;
    cabeca->anterior = novoUltimo;
  }
  --quantidade;
  delete removido->dado;
  delete removido;
  return true;
}

// busca linear pelo circulo (O(n))
bool ListaDuplamenteEncadeadaCircular::removerPeloId(int id) {
  if (vazia()) {
    return false;
  }

  No *atual = cabeca;
  do {
    if (atual->dado->getID() == id) {
      break;
    }
    atual = atual->proximo;
  } while (atual != cabeca);

  if (atual->dado->getID() != id) {
    return false; // deu a volta e nao achou
  }
  if (atual == cabeca) {
    return removerPrimeiro();
  }
  if (atual == cabeca->anterior) {
    return removerUltimo();
  }

  atual->anterior->proximo = atual->proximo;
  atual->proximo->anterior = atual->anterior;
  --quantidade;
  delete atual->dado;
  delete atual;
  return true;
}

// busca linear pelo circulo (O(n))
Elemento *ListaDuplamenteEncadeadaCircular::buscarPeloId(int id) const {
  if (vazia()) {
    return nullptr;
  }

  No *atual = cabeca;
  do {
    if (atual->dado->getID() == id) {
      return atual->dado;
    }
    atual = atual->proximo;
  } while (atual != cabeca);
  return nullptr;
}

// troca o elemento do ID por outro de mesmo ID; deleta o antigo (O(n))
bool ListaDuplamenteEncadeadaCircular::alterarPeloId(int id, Elemento *novo) {
  if (vazia() || novo == nullptr) {
    return false;
  }

  No *atual = cabeca;
  do {
    if (atual->dado->getID() == id) {
      break;
    }
    atual = atual->proximo;
  } while (atual != cabeca);

  if (atual->dado->getID() != id) {
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

// anda pelo circulo ate a posicao (O(n))
Elemento *ListaDuplamenteEncadeadaCircular::obter(int indice) const {
  if (indice < 0 || indice >= quantidade) {
    return nullptr;
  }

  No *atual = cabeca;
  for (int i = 0; i < indice; ++i) {
    atual = atual->proximo;
  }
  return atual->dado;
}

// O(1)
int ListaDuplamenteEncadeadaCircular::tamanho() const { return quantidade; }

// O(1)
bool ListaDuplamenteEncadeadaCircular::vazia() const { return quantidade == 0; }
