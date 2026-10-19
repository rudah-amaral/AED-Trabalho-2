#include <iostream>

#include "Deque/Deque.h"
#include "Elemento/Elemento.h"
#include "ElementoDerivado/ElementoDerivado.h"
#include "ElementoNomeado/ElementoNomeado.h"
#include "ListaNaoOrdenada/ListaNaoOrdenada.h"
#include "ListaOrdenada/ListaOrdenada.h"
#include "Pilha/Pilha.h"
#include "PilhaEncadeada/PilhaEncadeada.h"

int main() {
  // As duas classes concretas são guardadas no mesmo vetor de ponteiros
  // para Elemento. Isso só é possível porque a herança é pública.
  Elemento *elementos[2] = {
      new ElementoDerivado(2, 5),
      new ElementoNomeado(7, "Italo"),
  };

  std::cout << "\n--- Chamando imprimirInfo() pelo ponteiro de Elemento ---\n";

  // A chamada é resolvida em tempo de execução: cada objeto executa a sua
  // própria versão de imprimirInfo(), graças ao método virtual.
  for (Elemento *elemento : elementos) {
    elemento->imprimirInfo();
    std::cout << std::endl;
  }

  // O delete é feito através do ponteiro de Elemento. O destrutor virtual
  // da base garante que o destrutor correto de cada classe derivada rode.
  for (Elemento *elemento : elementos) {
    delete elemento;
  }

  // Lista nao ordenada: insere, busca, altera e remove.
  ListaNaoOrdenada lista;

  lista.inserirNoFinal(new ElementoDerivado(10, 1));
  lista.inserirNoInicio(new ElementoNomeado(20, "Ana"));
  lista.inserirNoFinal(new ElementoNomeado(30, "Bia"));

  std::cout << "--- Lista nao ordenada (apos insercoes) ---\n";
  for (int i = 0; i < lista.tamanho(); ++i) {
    lista.obter(i)->imprimirInfo();
    std::cout << std::endl;
  }

  std::cout << "Busca pelo ID 20: "
            << (lista.buscarPeloId(20) != nullptr ? "encontrado"
                                                  : "nao encontrado")
            << "\n\n";

  std::cout << "Alterando o elemento de ID 20...\n";
  lista.alterarPeloId(20, new ElementoDerivado(20, 99));

  std::cout << "Removendo o elemento de ID 10...\n\n";
  lista.removerPeloId(10);

  std::cout << "--- Lista apos alteracao e remocao ---\n";
  for (int i = 0; i < lista.tamanho(); ++i) {
    lista.obter(i)->imprimirInfo();
    std::cout << std::endl;
  }

  std::cout << "Removendo o primeiro...\n";
  lista.removerPrimeiro();
  std::cout << "Removendo o ultimo...\n";
  lista.removerUltimo();
  std::cout << "A lista esta vazia? " << (lista.vazia() ? "sim" : "nao")
            << "\n";

  // Teste de crescimento: a capacidade inicial e 10; 15 insercoes
  // fazem o bloco dobrar para 20.
  ListaNaoOrdenada crescente;
  for (int i = 0; i < 15; ++i) {
    crescente.inserirNoFinal(new ElementoNomeado(100 + i, "Crescimento"));
  }
  std::cout << "\n--- Crescimento ---\n";
  std::cout << "tamanho: " << crescente.tamanho()
            << " | capacidade: " << crescente.capacidade() << "\n";

  // Lista ordenada: mantem a ordem pelo ID, rejeita duplicados e usa
  // busca binaria.
  ListaOrdenada ordenada;

  ordenada.inserirNoFinal(new ElementoNomeado(30, "Bia"));
  ordenada.inserirNoInicio(new ElementoDerivado(10, 1));
  ordenada.inserirNoFinal(new ElementoNomeado(20, "Ana"));

  std::cout << "\n--- Lista ordenada (apos insercoes fora de ordem) ---\n";
  for (int i = 0; i < ordenada.tamanho(); ++i) {
    ordenada.obter(i)->imprimirInfo();
    std::cout << std::endl;
  }

  std::cout << "Ordem dos IDs:";
  for (int i = 0; i < ordenada.tamanho(); ++i) {
    std::cout << " " << ordenada.obter(i)->getID();
  }
  std::cout << "\n";

  Elemento *duplicado = new ElementoDerivado(20, 2);
  if (ordenada.inserirNoFinal(duplicado)) {
    std::cout << "Inserir o ID 20 de novo: entrou (nao deveria!)\n";
  } else {
    std::cout << "Inserir o ID 20 de novo: rejeitado (duplicado)\n";
    delete duplicado; // a lista nao assumiu a posse
  }

  std::cout << "Busca pelo ID 20: "
            << (ordenada.buscarPeloId(20) != nullptr ? "encontrado"
                                                     : "nao encontrado")
            << "\n";

  std::cout << "Alterando o elemento de ID 20...\n";
  ordenada.alterarPeloId(20, new ElementoDerivado(20, 99));

  std::cout << "Removendo o ID 10...\n";
  ordenada.removerPeloId(10);

  std::cout << "\n--- Lista ordenada (apos alteracao e remocao) ---\n";
  for (int i = 0; i < ordenada.tamanho(); ++i) {
    ordenada.obter(i)->imprimirInfo();
    std::cout << std::endl;
  }

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
