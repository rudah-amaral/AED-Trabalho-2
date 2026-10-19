#include "ListaNaoOrdenada.h"

// aloca o bloco inicial; so 0..quantidade-1 sao usados
ListaNaoOrdenada::ListaNaoOrdenada()
    : elementos(new Elemento *[CAPACIDADE_INICIAL]()), quantidade(0),
      capacidadeAtual(CAPACIDADE_INICIAL) {}

// libera os elementos e o bloco (O(n))
ListaNaoOrdenada::~ListaNaoOrdenada() {
  for (int i = 0; i < quantidade; ++i) {
    delete elementos[i];
  }
  delete[] elementos;
}

// se estiver cheio, aloca o dobro, copia os ponteiros e libera o antigo
// (aloca o novo antes de liberar: se new[] falhar, a lista continua valida)
// O(n) quando cresce
void ListaNaoOrdenada::garantirCapacidade() {
  if (quantidade < capacidadeAtual) {
    return;
  }

  int novaCapacidade = capacidadeAtual * 2;
  Elemento **novo = new Elemento *[novaCapacidade]();
  for (int i = 0; i < quantidade; ++i) {
    novo[i] = elementos[i];
  }
  delete[] elementos;
  elementos = novo;
  capacidadeAtual = novaCapacidade;
}

// abre espaco na posicao 0 e insere (O(n))
bool ListaNaoOrdenada::inserirNoInicio(Elemento *elemento) {
  if (elemento == nullptr) {
    return false;
  }

  garantirCapacidade();

  for (int i = quantidade; i > 0; --i) {
    elementos[i] = elementos[i - 1];
  }
  elementos[0] = elemento;
  ++quantidade;
  return true;
}

// insere no fim; O(1) amortizado (a realocacao e rara)
bool ListaNaoOrdenada::inserirNoFinal(Elemento *elemento) {
  if (elemento == nullptr) {
    return false;
  }

  garantirCapacidade();

  elementos[quantidade] = elemento;
  ++quantidade;
  return true;
}

// tira o primeiro; como a lista nao tem ordem, o ultimo ocupa o buraco (O(1))
bool ListaNaoOrdenada::removerPrimeiro() {
  if (vazia()) {
    return false;
  }

  Elemento *removido = elementos[0];
  elementos[0] = elementos[quantidade - 1];
  --quantidade;
  delete removido;
  return true;
}

// tira o ultimo (O(1))
bool ListaNaoOrdenada::removerUltimo() {
  if (vazia()) {
    return false;
  }

  --quantidade;
  delete elementos[quantidade];
  return true;
}

// busca o ID e remove trocando com o ultimo (O(n))
bool ListaNaoOrdenada::removerPeloId(int id) {
  int indice = buscarIndice(id);
  if (indice == -1) {
    return false;
  }

  Elemento *removido = elementos[indice];
  elementos[indice] = elementos[quantidade - 1];
  --quantidade;
  delete removido;
  return true;
}

// busca linear; devolve o ponteiro ou nullptr (O(n))
Elemento *ListaNaoOrdenada::buscarPeloId(int id) const {
  int indice = buscarIndice(id);
  if (indice == -1) {
    return nullptr;
  }
  return elementos[indice];
}

// troca o elemento do ID por outro de mesmo ID; deleta o antigo (O(n))
bool ListaNaoOrdenada::alterarPeloId(int id, Elemento *novo) {
  int indice = buscarIndice(id);
  if (indice == -1 || novo == nullptr) {
    return false;
  }

  // mesmo ponteiro: nada a fazer
  if (novo == elementos[indice]) {
    return true;
  }

  // tem que ser o mesmo ID
  if (novo->getID() != id) {
    return false;
  }

  // nao deixa o mesmo ponteiro entrar duas vezes
  for (int i = 0; i < quantidade; ++i) {
    if (elementos[i] == novo) {
      return false;
    }
  }

  Elemento *antigo = elementos[indice];
  elementos[indice] = novo;
  delete antigo;
  return true;
}

// acesso por indice, com checagem de limites (O(1))
Elemento *ListaNaoOrdenada::obter(int indice) const {
  if (indice < 0 || indice >= quantidade) {
    return nullptr;
  }
  return elementos[indice];
}

// O(1)
int ListaNaoOrdenada::tamanho() const { return quantidade; }

// O(1)
int ListaNaoOrdenada::capacidade() const { return capacidadeAtual; }

// O(1)
bool ListaNaoOrdenada::vazia() const { return quantidade == 0; }

// busca linear pelo ID (O(n))
int ListaNaoOrdenada::buscarIndice(int id) const {
  for (int i = 0; i < quantidade; ++i) {
    if (elementos[i]->getID() == id) {
      return i;
    }
  }
  return -1;
}
