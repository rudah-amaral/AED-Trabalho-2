#include <iostream>

#include "Deque/Deque.h"
#include "Elemento/Elemento.h"
#include "ElementoDerivado/ElementoDerivado.h"
#include "ElementoNomeado/ElementoNomeado.h"
#include "ListaNaoOrdenada/ListaNaoOrdenada.h"
#include "ListaOrdenada/ListaOrdenada.h"
#include "Pilha/Pilha.h"
#include "PilhaEncadeada/PilhaEncadeada.h"

// cabecalho de secao; cada secao termina com uma linha em branco
static void secao(const char *titulo) {
  std::cout << "=== " << titulo << " ===\n";
}

int main() {
  // 1. polimorfismo: a mesma chamada, objetos de tipos diferentes
  secao("1. Polimorfismo com Elemento*");

  Elemento *elementos[2] = {
      new ElementoDerivado(2, 5),
      new ElementoNomeado(7, "Italo"),
  };

  for (int i = 0; i < 2; ++i) {
    if (i > 0) {
      std::cout << "\n";
    }
    std::cout << "Objeto " << i << ":\n";
    elementos[i]->imprimirInfo();
  }
  std::cout << "\n";

  // o delete via Elemento* funciona por causa do destrutor virtual
  for (Elemento *elemento : elementos) {
    delete elemento;
  }

  // 2. lista nao ordenada: insere, busca, altera e remove
  secao("2. Lista nao ordenada");

  ListaNaoOrdenada lista;

  lista.inserirNoFinal(new ElementoDerivado(10, 1));
  lista.inserirNoInicio(new ElementoNomeado(20, "Ana"));
  lista.inserirNoFinal(new ElementoNomeado(30, "Bia"));

  std::cout << "Apos as insercoes:\n";
  for (int i = 0; i < lista.tamanho(); ++i) {
    if (i > 0) {
      std::cout << "\n";
    }
    std::cout << "Elemento " << i << ":\n";
    lista.obter(i)->imprimirInfo();
  }
  std::cout << "\n";

  std::cout << "Busca pelo ID 20: "
            << (lista.buscarPeloId(20) != nullptr ? "encontrado"
                                                  : "nao encontrado")
            << "\n";

  std::cout << "Alterando o elemento de ID 20...\n";
  lista.alterarPeloId(20, new ElementoDerivado(20, 99));

  std::cout << "Removendo o elemento de ID 10...\n";
  lista.removerPeloId(10);

  std::cout << "Apos a alteracao e a remocao:\n";
  for (int i = 0; i < lista.tamanho(); ++i) {
    if (i > 0) {
      std::cout << "\n";
    }
    std::cout << "Elemento " << i << ":\n";
    lista.obter(i)->imprimirInfo();
  }
  std::cout << "\n";

  std::cout << "Removendo o primeiro e o ultimo...\n";
  lista.removerPrimeiro();
  lista.removerUltimo();
  std::cout << "A lista esta vazia? " << (lista.vazia() ? "sim" : "nao")
            << "\n";
  std::cout << "\n";

  // 2.1 crescimento: 15 insercoes dobram o bloco de 10 para 20
  secao("2.1 Crescimento da lista");

  ListaNaoOrdenada crescente;
  std::cout << "capacidade inicial: " << crescente.capacidade() << "\n";

  for (int i = 0; i < 15; ++i) {
    crescente.inserirNoFinal(new ElementoNomeado(100 + i, "Crescimento"));
  }
  std::cout << "apos 15 insercoes -> tamanho: " << crescente.tamanho()
            << " | capacidade: " << crescente.capacidade() << "\n";
  std::cout << "\n";

  // 3. lista ordenada: mantem a ordem pelo ID e rejeita duplicados
  secao("3. Lista ordenada");

  ListaOrdenada ordenada;

  ordenada.inserirNoFinal(new ElementoNomeado(60, "Bia"));
  ordenada.inserirNoInicio(new ElementoDerivado(40, 4));
  ordenada.inserirNoFinal(new ElementoNomeado(50, "Ana"));

  std::cout << "Apos as insercoes (fora de ordem):\n";
  for (int i = 0; i < ordenada.tamanho(); ++i) {
    if (i > 0) {
      std::cout << "\n";
    }
    std::cout << "Elemento " << i << ":\n";
    ordenada.obter(i)->imprimirInfo();
  }
  std::cout << "\n";

  std::cout << "Ordem dos IDs:";
  for (int i = 0; i < ordenada.tamanho(); ++i) {
    std::cout << " " << ordenada.obter(i)->getID();
  }
  std::cout << "\n";

  Elemento *duplicado = new ElementoDerivado(50, 5);
  if (ordenada.inserirNoFinal(duplicado)) {
    std::cout << "Inserir o ID 50 de novo: entrou (nao deveria!)\n";
  } else {
    std::cout << "Inserir o ID 50 de novo: rejeitado (duplicado)\n";
    delete duplicado; // a lista nao assumiu a posse
  }

  std::cout << "Busca pelo ID 50: "
            << (ordenada.buscarPeloId(50) != nullptr ? "encontrado"
                                                     : "nao encontrado")
            << "\n";

  std::cout << "Alterando o elemento de ID 50...\n";
  ordenada.alterarPeloId(50, new ElementoDerivado(50, 99));

  std::cout << "Removendo o ID 40...\n";
  ordenada.removerPeloId(40);

  std::cout << "Apos a alteracao e a remocao:\n";
  for (int i = 0; i < ordenada.tamanho(); ++i) {
    if (i > 0) {
      std::cout << "\n";
    }
    std::cout << "Elemento " << i << ":\n";
    ordenada.obter(i)->imprimirInfo();
  }
  std::cout << "\n";

  std::cout << "Removendo o primeiro e o ultimo...\n";
  ordenada.removerPrimeiro();
  ordenada.removerUltimo();
  std::cout << "A lista ordenada esta vazia? "
            << (ordenada.vazia() ? "sim" : "nao") << "\n";

  // Pilha por composicao com a lista sequencial.
  Pilha pilha;
  pilha.empilhar(new ElementoDerivado(1, 11));
  pilha.empilhar(new ElementoNomeado(2, "dois"));

  std::cout << "\n--- Pilha (lista sequencial) ---\n";
  std::cout << "topo: ID " << pilha.consultarTopo()->getID()
            << " | tamanho: " << pilha.tamanho() << "\n";
  std::cout << "cheia? " << (pilha.pilhaCheia() ? "sim" : "nao")
            << " | vazia? " << (pilha.pilhaVazia() ? "sim" : "nao") << "\n";
  pilha.desempilhar();
  std::cout << "topo depois do desempilhar: ID "
            << pilha.consultarTopo()->getID() << "\n";

  // Pilha adaptadora sobre a lista simplesmente encadeada.
  PilhaEncadeada pilhaEncadeada;
  pilhaEncadeada.empilhar(new ElementoDerivado(7, 7));

  std::cout << "\n--- Pilha encadeada ---\n";
  std::cout << "topo: ID " << pilhaEncadeada.consultarTopo()->getID()
            << " | vazia? " << (pilhaEncadeada.pilhaVazia() ? "sim" : "nao")
            << "\n";

  // Deque adaptador sobre a lista duplamente encadeada.
  Deque deque;
  deque.inserirNoInicio(new ElementoNomeado(10, "dez"));
  deque.inserirNoFim(new ElementoDerivado(20, 2));
  deque.inserirNoInicio(new ElementoDerivado(5, 5));

  std::cout << "\n--- Deque ---\n";
  std::cout << "inicio: ID " << deque.consultarInicio()->getID()
            << " | fim: ID " << deque.consultarFim()->getID()
            << " | tamanho: " << deque.tamanho() << "\n";
  deque.removerInicio();
  deque.removerFim();
  std::cout << "depois de remover as pontas -> tamanho: " << deque.tamanho()
            << " | inicio: ID " << deque.consultarInicio()->getID() << "\n";

  return 0;
}
