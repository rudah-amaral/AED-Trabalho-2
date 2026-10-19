#include <iostream>

#include "ArvoreBinariaBusca/ArvoreBinariaBusca.h"
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

  std::cout << "Apos as insercoes (tamanho " << lista.tamanho()
            << ", capacidade " << lista.capacidade() << "):\n";
  for (int i = 0; i < lista.tamanho(); ++i) {
    std::cout << "  [" << i << "] ";
    lista.obter(i)->imprimirResumo();
  }
  std::cout << "\n";

  // o PDF exige percorrer a estrutura chamando imprimirInfo() em cada elemento
  std::cout << "Percurso com imprimirInfo() (cada tipo responde do seu jeito):\n";
  for (int i = 0; i < lista.tamanho(); ++i) {
    std::cout << "Elemento " << i << ":\n";
    lista.obter(i)->imprimirInfo();
    std::cout << "\n";
  }

  std::cout << "Busca pelo ID 20: "
            << (lista.buscarPeloId(20) != nullptr ? "encontrado"
                                                  : "nao encontrado")
            << "\n";

  std::cout << "Alterando o elemento de ID 20...\n";
  lista.alterarPeloId(20, new ElementoDerivado(20, 99));

  std::cout << "Removendo o elemento de ID 10...\n";
  lista.removerPeloId(10);

  std::cout << "Apos a alteracao e a remocao (tamanho " << lista.tamanho()
            << "):\n";
  for (int i = 0; i < lista.tamanho(); ++i) {
    std::cout << "  [" << i << "] ";
    lista.obter(i)->imprimirResumo();
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

  std::cout << "Apos as insercoes (fora de ordem) - tamanho "
            << ordenada.tamanho() << ", capacidade " << ordenada.capacidade()
            << ":\n";
  for (int i = 0; i < ordenada.tamanho(); ++i) {
    std::cout << "  [" << i << "] ";
    ordenada.obter(i)->imprimirResumo();
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

  std::cout << "Apos a alteracao e a remocao (tamanho " << ordenada.tamanho()
            << "):\n";
  for (int i = 0; i < ordenada.tamanho(); ++i) {
    std::cout << "  [" << i << "] ";
    ordenada.obter(i)->imprimirResumo();
  }
  std::cout << "\n";

  std::cout << "Removendo o primeiro e o ultimo...\n";
  ordenada.removerPrimeiro();
  ordenada.removerUltimo();
  std::cout << "A lista ordenada esta vazia? "
            << (ordenada.vazia() ? "sim" : "nao") << "\n";
  std::cout << "\n";

  // 4. pilha: composicao com a lista sequencial
  secao("4. Pilha (lista sequencial)");

  Pilha pilha;
  pilha.empilhar(new ElementoDerivado(70, 7));
  pilha.empilhar(new ElementoNomeado(80, "oitenta"));

  std::cout << "Topo da pilha:\n  ";
  pilha.consultarTopo()->imprimirResumo();
  std::cout << "\n";

  std::cout << "cheia? " << (pilha.pilhaCheia() ? "sim" : "nao")
            << " | vazia? " << (pilha.pilhaVazia() ? "sim" : "nao")
            << " | tamanho: " << pilha.tamanho() << "\n";

  std::cout << "Desempilhando...\n";
  pilha.desempilhar();
  std::cout << "Novo topo:\n  ";
  pilha.consultarTopo()->imprimirResumo();
  std::cout << "\n";

  // 5. pilha adaptadora sobre a lista simplesmente encadeada
  secao("5. Pilha encadeada (lista simples)");

  PilhaEncadeada pilhaEncadeada;
  pilhaEncadeada.empilhar(new ElementoDerivado(90, 9));

  std::cout << "Topo da pilha:\n  ";
  pilhaEncadeada.consultarTopo()->imprimirResumo();
  std::cout << "\n";

  std::cout << "vazia? " << (pilhaEncadeada.pilhaVazia() ? "sim" : "nao")
            << " | tamanho: " << pilhaEncadeada.tamanho() << "\n";
  std::cout << "\n";

  // 6. deque adaptador sobre a lista duplamente encadeada
  secao("6. Deque (lista duplamente encadeada)");

  Deque deque;
  deque.inserirNoInicio(new ElementoNomeado(110, "onze"));
  deque.inserirNoFim(new ElementoDerivado(120, 12));
  deque.inserirNoInicio(new ElementoDerivado(100, 10));

  std::cout << "Inicio:\n  ";
  deque.consultarInicio()->imprimirResumo();
  std::cout << "\n";

  std::cout << "Fim:\n  ";
  deque.consultarFim()->imprimirResumo();
  std::cout << "\n";

  std::cout << "tamanho: " << deque.tamanho() << "\n";

  std::cout << "Removendo as pontas...\n";
  deque.removerInicio();
  deque.removerFim();
  std::cout << "Novo inicio:\n  ";
  deque.consultarInicio()->imprimirResumo();
  std::cout << "\n";

  std::cout << "tamanho: " << deque.tamanho() << "\n";
  std::cout << "\n";

  // 7. arvore binaria de busca: ordem pelo ID e percursos
  secao("7. Arvore binaria de busca");

  ArvoreBinariaBusca arvore;
  arvore.inserir(new ElementoDerivado(50, 5));
  arvore.inserir(new ElementoNomeado(30, "Ana"));
  arvore.inserir(new ElementoDerivado(70, 7));
  arvore.inserir(new ElementoNomeado(20, "Bia"));
  arvore.inserir(new ElementoDerivado(40, 4));
  arvore.inserir(new ElementoNomeado(60, "Caio"));
  arvore.inserir(new ElementoDerivado(80, 8));
  arvore.inserir(new ElementoNomeado(35, "Duda"));

  std::cout << "Apos 8 insercoes (fora de ordem) - tamanho "
            << arvore.tamanho() << ", altura " << arvore.altura() << ":\n";
  std::cout << "  emOrdem:  ";
  arvore.emOrdem();
  std::cout << "  preOrdem: ";
  arvore.preOrdem();
  std::cout << "  posOrdem: ";
  arvore.posOrdem();
  std::cout << "\n";

  Elemento *buscado = arvore.buscarPeloId(35);
  std::cout << "Busca pelo ID 35: ";
  if (buscado != nullptr) {
    buscado->imprimirResumo();
  } else {
    std::cout << "nao encontrado\n";
  }

  std::cout << "Busca pelo ID 99: "
            << (arvore.buscarPeloId(99) != nullptr ? "encontrado"
                                                   : "nao encontrado")
            << "\n";

  Elemento *dup = new ElementoDerivado(50, 99);
  if (arvore.inserir(dup)) {
    std::cout << "Inserir o ID 50 de novo: entrou (nao deveria!)\n";
  } else {
    std::cout << "Inserir o ID 50 de novo: rejeitado (duplicado)\n";
    delete dup; // a arvore nao assumiu a posse
  }

  std::cout << "\nRemovendo 20 (folha)...\n";
  arvore.removerPeloId(20);
  std::cout << "  emOrdem: ";
  arvore.emOrdem();

  std::cout << "Removendo 30 (um filho)...\n";
  arvore.removerPeloId(30);
  std::cout << "  emOrdem: ";
  arvore.emOrdem();

  std::cout << "Removendo 50 (dois filhos, sucessor 60)...\n";
  arvore.removerPeloId(50);
  std::cout << "  emOrdem: ";
  arvore.emOrdem();

  std::cout << "Altura final: " << arvore.altura()
            << " | tamanho: " << arvore.tamanho() << "\n";
  std::cout << "\n";

  std::cout << "=== Fim da demonstracao ===\n";

  return 0;
}
