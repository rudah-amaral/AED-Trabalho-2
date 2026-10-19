#include "ListaOrdenada.h"

// aloca o bloco inicial; so 0..quantidade-1 sao usados
ListaOrdenada::ListaOrdenada()
    : elementos(new Elemento *[CAPACIDADE_INICIAL]()), quantidade(0),
      capacidadeAtual(CAPACIDADE_INICIAL) {}

// libera os elementos e o bloco (O(n))
ListaOrdenada::~ListaOrdenada() {
  for (int i = 0; i < quantidade; ++i) {
    delete elementos[i];
  }
  delete[] elementos;
}

// se estiver cheio, aloca o dobro, copia os ponteiros e libera o antigo
// O(n) quando cresce
void ListaOrdenada::garantirCapacidade() {
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

// busca binaria: devolve o indice do ID ou -1 (O(log n))
int ListaOrdenada::buscarIndice(int id) const {
  int inicio = 0;
  int fim = quantidade - 1;

  while (inicio <= fim) {
    int meio = (inicio + fim) / 2;
    int idMeio = elementos[meio]->getID();

    if (idMeio == id) {
      return meio;
    }
    if (idMeio < id) {
      inicio = meio + 1;
    } else {
      fim = meio - 1;
    }
  }
  return -1;
}

// primeira posicao com ID >= id: onde o elemento deve entrar (O(log n))
int ListaOrdenada::posicaoDeInsercao(int id) const {
  int inicio = 0;
  int fim = quantidade - 1;

  while (inicio <= fim) {
    int meio = (inicio + fim) / 2;
    if (elementos[meio]->getID() < id) {
      inicio = meio + 1;
    } else {
      fim = meio - 1;
    }
  }
  return inicio;
}

// insere na posicao ordenada; rejeita ID duplicado (O(n): desloca)
bool ListaOrdenada::inserirOrdenado(Elemento *elemento) {
  if (elemento == nullptr) {
    return false;
  }

  int posicao = posicaoDeInsercao(elemento->getID());

  // duplicado: ja existe alguem com esse ID
  if (posicao < quantidade &&
      elementos[posicao]->getID() == elemento->getID()) {
    return false;
  }

  garantirCapacidade();

  // abre espaco da ultima posicao ate a posicao de insercao
  for (int i = quantidade; i > posicao; --i) {
    elementos[i] = elementos[i - 1];
  }
  elementos[posicao] = elemento;
  ++quantidade;
  return true;
}

// os dois metodos fazem a mesma coisa: inserir na posicao ordenada
bool ListaOrdenada::inserirNoInicio(Elemento *elemento) {
  return inserirOrdenado(elemento);
}

bool ListaOrdenada::inserirNoFinal(Elemento *elemento) {
  return inserirOrdenado(elemento);
}

// tira a posicao 0 e puxa todo mundo para tras (O(n))
bool ListaOrdenada::removerPrimeiro() {
  if (vazia()) {
    return false;
  }

  Elemento *removido = elementos[0];
  for (int i = 0; i < quantidade - 1; ++i) {
    elementos[i] = elementos[i + 1];
  }
  --quantidade;
  delete removido;
  return true;
}

// tira o ultimo (O(1))
bool ListaOrdenada::removerUltimo() {
  if (vazia()) {
    return false;
  }

  --quantidade;
  delete elementos[quantidade];
  return true;
}

// busca binaria + fecha o buraco (O(n): desloca)
bool ListaOrdenada::removerPeloId(int id) {
  int indice = buscarIndice(id);
  if (indice == -1) {
    return false;
  }

  Elemento *removido = elementos[indice];
  for (int i = indice; i < quantidade - 1; ++i) {
    elementos[i] = elementos[i + 1];
  }
  --quantidade;
  delete removido;
  return true;
}

// busca binaria; devolve o ponteiro ou nullptr (O(log n))
Elemento *ListaOrdenada::buscarPeloId(int id) const {
  int indice = buscarIndice(id);
  if (indice == -1) {
    return nullptr;
  }
  return elementos[indice];
}

// troca o elemento do ID por outro de mesmo ID; deleta o antigo (O(log n))
bool ListaOrdenada::alterarPeloId(int id, Elemento *novo) {
  int indice = buscarIndice(id);
  if (indice == -1 || novo == nullptr) {
    return false;
  }

  // mesmo ponteiro: nada a fazer
  if (novo == elementos[indice]) {
    return true;
  }

  // o ID e a chave: tem que ser o mesmo
  if (novo->getID() != id) {
    return false;
  }

  Elemento *antigo = elementos[indice];
  elementos[indice] = novo;
  delete antigo;
  return true;
}

// acesso por indice, com checagem de limites (O(1))
Elemento *ListaOrdenada::obter(int indice) const {
  if (indice < 0 || indice >= quantidade) {
    return nullptr;
  }
  return elementos[indice];
}

// O(1)
int ListaOrdenada::tamanho() const { return quantidade; }

// O(1)
int ListaOrdenada::capacidade() const { return capacidadeAtual; }

// O(1)
bool ListaOrdenada::vazia() const { return quantidade == 0; }
