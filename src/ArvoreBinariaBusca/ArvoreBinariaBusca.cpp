#include "ArvoreBinariaBusca.h"

#include <iostream>

// arvore vazia: raiz nula e nenhum elemento
ArvoreBinariaBusca::ArvoreBinariaBusca() : raiz(nullptr), qtd(0) {}

// libera os nos e os elementos (O(n))
ArvoreBinariaBusca::~ArvoreBinariaBusca() {
  limpa(raiz);
  raiz = nullptr;
}

// pos-ordem: libera os filhos antes do no e do dado (O(n))
void ArvoreBinariaBusca::limpa(No *no) {
  if (no == nullptr) {
    return;
  }
  limpa(no->esq);
  limpa(no->dir);
  delete no->dado;
  delete no;
}

// comeca a insercao pela raiz (O(h))
bool ArvoreBinariaBusca::inserir(Elemento *elem) {
  if (elem == nullptr) {
    return false;
  }

  bool ok = false;
  raiz = insere(raiz, elem, ok);
  return ok;
}

// compara os IDs e desce ate achar um lugar livre (O(h))
ArvoreBinariaBusca::No *ArvoreBinariaBusca::insere(No *no, Elemento *elem,
                                                   bool &ok) {
  if (no == nullptr) {
    ok = true;
    ++qtd;
    return new No(elem);
  }

  if (elem->getID() < no->dado->getID()) {
    no->esq = insere(no->esq, elem, ok);
  } else if (elem->getID() > no->dado->getID()) {
    no->dir = insere(no->dir, elem, ok);
  }
  // ID igual: nao entra e a posse continua com o chamador
  return no;
}

// busca binaria na arvore (O(h))
Elemento *ArvoreBinariaBusca::buscarPeloId(int id) const {
  const No *no = busca(raiz, id);
  return no == nullptr ? nullptr : no->dado;
}

// desce comparando o ID: menor vai para a esquerda, maior para a direita
const ArvoreBinariaBusca::No *ArvoreBinariaBusca::busca(const No *no,
                                                        int id) const {
  if (no == nullptr || no->dado->getID() == id) {
    return no;
  }
  if (id < no->dado->getID()) {
    return busca(no->esq, id);
  }
  return busca(no->dir, id);
}

// comeca a remocao pela raiz (O(h))
bool ArvoreBinariaBusca::removerPeloId(int id) {
  bool ok = false;
  raiz = remove(raiz, id, ok);
  return ok;
}

// os tres casos de remocao (O(h))
ArvoreBinariaBusca::No *ArvoreBinariaBusca::remove(No *no, int id, bool &ok) {
  if (no == nullptr) {
    return nullptr;
  }

  if (id < no->dado->getID()) {
    no->esq = remove(no->esq, id, ok);
    return no;
  }
  if (id > no->dado->getID()) {
    no->dir = remove(no->dir, id, ok);
    return no;
  }

  ok = true;
  --qtd;

  // caso 1: folha
  if (no->esq == nullptr && no->dir == nullptr) {
    delete no->dado;
    delete no;
    return nullptr;
  }

  // caso 2: um filho ocupa o lugar do no
  if (no->esq == nullptr) {
    No *filho = no->dir;
    delete no->dado;
    delete no;
    return filho;
  }
  if (no->dir == nullptr) {
    No *filho = no->esq;
    delete no->dado;
    delete no;
    return filho;
  }

  // caso 3: dois filhos -> sucessor (menor da subarvore direita)
  No *sucessor = minimo(no->dir);
  delete no->dado;           // libera o elemento removido
  no->dado = sucessor->dado; // transfere o ponteiro do sucessor
  no->dir = removeMin(no->dir);
  return no;
}

// menor ID de uma subarvore (O(h))
ArvoreBinariaBusca::No *ArvoreBinariaBusca::minimo(No *no) const {
  while (no->esq != nullptr) {
    no = no->esq;
  }
  return no;
}

// remove o no minimo sem deletar o dado (ele foi transferido) (O(h))
ArvoreBinariaBusca::No *ArvoreBinariaBusca::removeMin(No *no) {
  if (no->esq == nullptr) {
    No *dir = no->dir;
    delete no;
    return dir;
  }
  no->esq = removeMin(no->esq);
  return no;
}

// percurso em ordem: esquerda, no, direita (O(n))
void ArvoreBinariaBusca::emOrdem() const {
  bool primeiro = true;
  emOrdemNo(raiz, primeiro);
  std::cout << "\n";
}

void ArvoreBinariaBusca::emOrdemNo(const No *no, bool &primeiro) const {
  if (no == nullptr) {
    return;
  }
  emOrdemNo(no->esq, primeiro);
  if (!primeiro) {
    std::cout << " ";
  }
  std::cout << no->dado->getID();
  primeiro = false;
  emOrdemNo(no->dir, primeiro);
}

// percurso pre-ordem: no, esquerda, direita (O(n))
void ArvoreBinariaBusca::preOrdem() const {
  bool primeiro = true;
  preOrdemNo(raiz, primeiro);
  std::cout << "\n";
}

void ArvoreBinariaBusca::preOrdemNo(const No *no, bool &primeiro) const {
  if (no == nullptr) {
    return;
  }
  if (!primeiro) {
    std::cout << " ";
  }
  std::cout << no->dado->getID();
  primeiro = false;
  preOrdemNo(no->esq, primeiro);
  preOrdemNo(no->dir, primeiro);
}

// percurso pos-ordem: esquerda, direita, no (O(n))
void ArvoreBinariaBusca::posOrdem() const {
  bool primeiro = true;
  posOrdemNo(raiz, primeiro);
  std::cout << "\n";
}

void ArvoreBinariaBusca::posOrdemNo(const No *no, bool &primeiro) const {
  if (no == nullptr) {
    return;
  }
  posOrdemNo(no->esq, primeiro);
  posOrdemNo(no->dir, primeiro);
  if (!primeiro) {
    std::cout << " ";
  }
  std::cout << no->dado->getID();
  primeiro = false;
}

// altura em numero de niveis (O(n))
int ArvoreBinariaBusca::altura() const { return alturaNo(raiz); }

int ArvoreBinariaBusca::alturaNo(const No *no) const {
  if (no == nullptr) {
    return 0;
  }

  int esq = alturaNo(no->esq);
  int dir = alturaNo(no->dir);
  return 1 + (esq > dir ? esq : dir);
}

// O(1)
int ArvoreBinariaBusca::tamanho() const { return qtd; }

// O(1)
bool ArvoreBinariaBusca::vazia() const { return qtd == 0; }
