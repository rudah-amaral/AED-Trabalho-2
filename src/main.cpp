#include <iomanip>
#include <iostream>

#include "ArvoreBinariaBusca/ArvoreBinariaBusca.h"
#include "Deque/Deque.h"
#include "Elemento/Elemento.h"
#include "ElementoDerivado/ElementoDerivado.h"
#include "ElementoNomeado/ElementoNomeado.h"
#include "Grafo/Grafo.h"
#include "ListaNaoOrdenada/ListaNaoOrdenada.h"
#include "ListaOrdenada/ListaOrdenada.h"
#include "Pilha/Pilha.h"
#include "PilhaEncadeada/PilhaEncadeada.h"
#include "FilaSequencial/FilaSequencial.h"
#include "FilaEncadeada/FilaEncadeada.h"

// cabecalho de secao em caixa
static void secao(const char *titulo) {
  std::cout << "\n============================================================\n";
  std::cout << " " << titulo << "\n";
  std::cout << "============================================================\n\n";
}

// cabecalho da tabela de elementos
static void cabecalhoTabela() {
  std::cout << "  idx | " << std::left << std::setw(16) << "tipo" << " | "
            << std::right << std::setw(4) << "ID" << " | dado\n";
  std::cout << "  ----+------------------+------+----------------\n";
}

// tabela da lista nao ordenada (indice + resumo de cada elemento)
static void imprimirTabela(const ListaNaoOrdenada &lista) {
  cabecalhoTabela();
  for (int i = 0; i < lista.tamanho(); ++i) {
    std::cout << "  " << std::right << std::setw(3) << i << " | ";
    lista.obter(i)->imprimirResumo();
  }
}

// tabela da lista ordenada
static void imprimirTabela(const ListaOrdenada &lista) {
  cabecalhoTabela();
  for (int i = 0; i < lista.tamanho(); ++i) {
    std::cout << "  " << std::right << std::setw(3) << i << " | ";
    lista.obter(i)->imprimirResumo();
  }
}

int main() {
  // 1. polimorfismo: a mesma chamada, objetos de tipos diferentes
  secao("1. POLIMORFISMO COM ELEMENTO*");

  Elemento *elementos[2] = {
      new ElementoDerivado(2, 5),
      new ElementoNomeado(7, "Italo"),
  };

  for (int i = 0; i < 2; ++i) {
    std::cout << "Objeto " << i << " -> ";
    elementos[i]->imprimirResumo();
    elementos[i]->imprimirInfo();
    std::cout << "\n";
  }

  // o delete via Elemento* funciona por causa do destrutor virtual
  for (Elemento *elemento : elementos) {
    delete elemento;
  }

  // 2. lista nao ordenada: insere, busca, altera e remove
  secao("2. LISTA NAO ORDENADA");

  ListaNaoOrdenada lista;

  Elemento *e = new ElementoDerivado(10, 1);
  std::cout << "Insercao no final:    ";
  e->imprimirResumo();
  lista.inserirNoFinal(e);

  e = new ElementoNomeado(20, "Ana");
  std::cout << "Insercao no inicio:   ";
  e->imprimirResumo();
  lista.inserirNoInicio(e);

  e = new ElementoNomeado(30, "Bia");
  std::cout << "Insercao no final:    ";
  e->imprimirResumo();
  lista.inserirNoFinal(e);

  std::cout << "\nLista apos as insercoes (tamanho " << lista.tamanho()
            << ", capacidade " << lista.capacidade() << ")\n";
  imprimirTabela(lista);
  std::cout << "\n";

  // o PDF exige percorrer a estrutura chamando imprimirInfo() em cada elemento
  std::cout << "Apresentacao detalhada (imprimirInfo, uma chamada por "
               "elemento)\n";
  for (int i = 0; i < lista.tamanho(); ++i) {
    std::cout << "  [" << i << "] ";
    lista.obter(i)->imprimirResumo();
    lista.obter(i)->imprimirInfo();
    std::cout << "\n";
  }

  Elemento *achado = lista.buscarPeloId(20);
  std::cout << "Busca pelo ID 20: ";
  if (achado != nullptr) {
    std::cout << "encontrado -> ";
    achado->imprimirResumo();
  } else {
    std::cout << "nao encontrado\n";
  }

  std::cout << "Alterando o ID 20:\n";
  Elemento *antigo = lista.buscarPeloId(20);
  std::cout << "  antes:  ";
  antigo->imprimirResumo();
  Elemento *novo = new ElementoDerivado(20, 99);
  std::cout << "  depois: ";
  novo->imprimirResumo();
  lista.alterarPeloId(20, novo);

  std::cout << "Removendo o ID 10:\n  ";
  lista.buscarPeloId(10)->imprimirResumo();
  lista.removerPeloId(10);

  std::cout << "\nLista apos a alteracao e a remocao (tamanho "
            << lista.tamanho() << ")\n";
  imprimirTabela(lista);
  std::cout << "\n";

  std::cout << "Removendo o primeiro:\n  ";
  lista.obter(0)->imprimirResumo();
  lista.removerPrimeiro();

  std::cout << "Removendo o ultimo:\n  ";
  lista.obter(lista.tamanho() - 1)->imprimirResumo();
  lista.removerUltimo();

  std::cout << "A lista esta vazia? " << (lista.vazia() ? "sim" : "nao")
            << "\n";

  // 2.1 crescimento: 15 insercoes dobram o bloco de 10 para 20
  secao("2.1 CRESCIMENTO DA LISTA");

  ListaNaoOrdenada crescente;
  std::cout << "Capacidade inicial: " << crescente.capacidade() << "\n";

  for (int i = 0; i < 15; ++i) {
    crescente.inserirNoFinal(new ElementoNomeado(100 + i, "Crescimento"));
  }

  std::cout << "Apos 15 insercoes: tamanho " << crescente.tamanho()
            << " | capacidade " << crescente.capacidade() << "\n";
  std::cout << "Primeiro: ";
  crescente.obter(0)->imprimirResumo();
  std::cout << "Ultimo:   ";
  crescente.obter(crescente.tamanho() - 1)->imprimirResumo();

  // 3. lista ordenada: mantem a ordem pelo ID e rejeita duplicados
  secao("3. LISTA ORDENADA");

  ListaOrdenada ordenada;

  e = new ElementoNomeado(60, "Bia");
  std::cout << "Insercao no final:  ";
  e->imprimirResumo();
  ordenada.inserirNoFinal(e);

  e = new ElementoDerivado(40, 4);
  std::cout << "Insercao no inicio: ";
  e->imprimirResumo();
  ordenada.inserirNoInicio(e);

  e = new ElementoNomeado(50, "Ana");
  std::cout << "Insercao no final:  ";
  e->imprimirResumo();
  ordenada.inserirNoFinal(e);

  std::cout << "\nLista apos as insercoes fora de ordem (tamanho "
            << ordenada.tamanho() << ", capacidade " << ordenada.capacidade()
            << ")\n";
  imprimirTabela(ordenada);
  std::cout << "IDs em ordem:";
  for (int i = 0; i < ordenada.tamanho(); ++i) {
    std::cout << " " << ordenada.obter(i)->getID();
  }
  std::cout << "\n\n";

  Elemento *dup = new ElementoDerivado(50, 5);
  std::cout << "Inserir o ID 50 de novo:\n  ";
  dup->imprimirResumo();
  if (ordenada.inserirNoFinal(dup)) {
    std::cout << "  entrou (nao deveria!)\n";
  } else {
    std::cout << "  rejeitado (duplicado)\n";
    delete dup; // a lista nao assumiu a posse
  }

  achado = ordenada.buscarPeloId(50);
  std::cout << "Busca pelo ID 50: ";
  if (achado != nullptr) {
    std::cout << "encontrado -> ";
    achado->imprimirResumo();
  } else {
    std::cout << "nao encontrado\n";
  }

  std::cout << "Alterando o ID 50:\n";
  antigo = ordenada.buscarPeloId(50);
  std::cout << "  antes:  ";
  antigo->imprimirResumo();
  novo = new ElementoDerivado(50, 99);
  std::cout << "  depois: ";
  novo->imprimirResumo();
  ordenada.alterarPeloId(50, novo);

  std::cout << "Removendo o ID 40:\n  ";
  ordenada.buscarPeloId(40)->imprimirResumo();
  ordenada.removerPeloId(40);

  std::cout << "\nLista apos a alteracao e a remocao (tamanho "
            << ordenada.tamanho() << ")\n";
  imprimirTabela(ordenada);
  std::cout << "\n";

  std::cout << "Removendo o primeiro:\n  ";
  ordenada.obter(0)->imprimirResumo();
  ordenada.removerPrimeiro();

  std::cout << "Removendo o ultimo:\n  ";
  ordenada.obter(ordenada.tamanho() - 1)->imprimirResumo();
  ordenada.removerUltimo();

  std::cout << "A lista ordenada esta vazia? "
            << (ordenada.vazia() ? "sim" : "nao") << "\n";

  // 4. pilha: composicao com a lista sequencial
  secao("4. PILHA (LISTA SEQUENCIAL)");

  Pilha pilha;

  e = new ElementoDerivado(70, 7);
  std::cout << "Empilhando: ";
  e->imprimirResumo();
  pilha.empilhar(e);

  e = new ElementoNomeado(80, "oitenta");
  std::cout << "Empilhando: ";
  e->imprimirResumo();
  pilha.empilhar(e);

  std::cout << "Topo: ";
  pilha.consultarTopo()->imprimirResumo();
  std::cout << "cheia? " << (pilha.pilhaCheia() ? "sim" : "nao")
            << " | vazia? " << (pilha.pilhaVazia() ? "sim" : "nao")
            << " | tamanho: " << pilha.tamanho() << "\n";

  std::cout << "Desempilhando: ";
  pilha.consultarTopo()->imprimirResumo();
  pilha.desempilhar();
  std::cout << "Novo topo: ";
  pilha.consultarTopo()->imprimirResumo();

  // 5. pilha adaptadora sobre a lista simplesmente encadeada
  secao("5. PILHA ENCADEADA (LISTA SIMPLES)");

  PilhaEncadeada pilhaEncadeada;
  e = new ElementoDerivado(90, 9);
  std::cout << "Empilhando: ";
  e->imprimirResumo();
  pilhaEncadeada.empilhar(e);

  std::cout << "Topo: ";
  pilhaEncadeada.consultarTopo()->imprimirResumo();
  std::cout << "vazia? " << (pilhaEncadeada.pilhaVazia() ? "sim" : "nao")
            << " | tamanho: " << pilhaEncadeada.tamanho() << "\n";

  // 6. deque adaptador sobre a lista duplamente encadeada
  secao("6. DEQUE (LISTA DUPLAMENTE ENCADEADA)");

  Deque deque;

  e = new ElementoNomeado(110, "onze");
  std::cout << "Insercao no inicio: ";
  e->imprimirResumo();
  deque.inserirNoInicio(e);

  e = new ElementoDerivado(120, 12);
  std::cout << "Insercao no fim:    ";
  e->imprimirResumo();
  deque.inserirNoFim(e);

  e = new ElementoDerivado(100, 10);
  std::cout << "Insercao no inicio: ";
  e->imprimirResumo();
  deque.inserirNoInicio(e);

  std::cout << "\ntamanho: " << deque.tamanho() << "\n";
  std::cout << "Inicio: ";
  deque.consultarInicio()->imprimirResumo();
  std::cout << "Fim:    ";
  deque.consultarFim()->imprimirResumo();

  std::cout << "Removendo o inicio: ";
  deque.consultarInicio()->imprimirResumo();
  deque.removerInicio();

  std::cout << "Removendo o fim:    ";
  deque.consultarFim()->imprimirResumo();
  deque.removerFim();

  std::cout << "Novo inicio: ";
  deque.consultarInicio()->imprimirResumo();
  std::cout << "tamanho: " << deque.tamanho() << "\n";

  // 7. arvore binaria de busca: ordem pelo ID, percursos e estrutura
  secao("7. ARVORE BINARIA DE BUSCA");

  ArvoreBinariaBusca arvore;
  std::cout << "Inserindo fora de ordem: 50, 30, 70, 20, 40, 60, 80, 35\n\n";

  arvore.inserir(new ElementoDerivado(50, 5));
  arvore.inserir(new ElementoNomeado(30, "Ana"));
  arvore.inserir(new ElementoDerivado(70, 7));
  arvore.inserir(new ElementoNomeado(20, "Bia"));
  arvore.inserir(new ElementoDerivado(40, 4));
  arvore.inserir(new ElementoNomeado(60, "Caio"));
  arvore.inserir(new ElementoDerivado(80, 8));
  arvore.inserir(new ElementoNomeado(35, "Duda"));

  std::cout << "Arvore (tamanho " << arvore.tamanho() << ", altura "
            << arvore.altura() << ")\n";
  std::cout << "  emOrdem:  ";
  arvore.emOrdem();
  std::cout << "  preOrdem: ";
  arvore.preOrdem();
  std::cout << "  posOrdem: ";
  arvore.posOrdem();

  std::cout << "\nEstrutura (ID - elemento)\n";
  arvore.imprimirEstrutura();
  std::cout << "\n";

  achado = arvore.buscarPeloId(35);
  std::cout << "Busca pelo ID 35: ";
  if (achado != nullptr) {
    std::cout << "encontrado -> ";
    achado->imprimirResumo();
  } else {
    std::cout << "nao encontrado\n";
  }

  std::cout << "Busca pelo ID 99: "
            << (arvore.buscarPeloId(99) != nullptr ? "encontrado"
                                                   : "nao encontrado")
            << "\n";

  dup = new ElementoDerivado(50, 99);
  std::cout << "Inserir o ID 50 de novo:\n  ";
  dup->imprimirResumo();
  if (arvore.inserir(dup)) {
    std::cout << "  entrou (nao deveria!)\n";
  } else {
    std::cout << "  rejeitado (duplicado)\n";
    delete dup; // a arvore nao assumiu a posse
  }

  std::cout << "\nRemovendo 20 (folha):\n  ";
  arvore.buscarPeloId(20)->imprimirResumo();
  arvore.removerPeloId(20);
  std::cout << "  emOrdem: ";
  arvore.emOrdem();

  std::cout << "Removendo 30 (um filho):\n  ";
  arvore.buscarPeloId(30)->imprimirResumo();
  arvore.removerPeloId(30);
  std::cout << "  emOrdem: ";
  arvore.emOrdem();

  std::cout << "Removendo 50 (dois filhos, sucessor 60):\n  ";
  arvore.buscarPeloId(50)->imprimirResumo();
  arvore.removerPeloId(50);
  std::cout << "  emOrdem: ";
  arvore.emOrdem();

  std::cout << "\nEstrutura final (tamanho " << arvore.tamanho()
            << ", altura " << arvore.altura() << ")\n";
  arvore.imprimirEstrutura();

  // 8. grafo: matriz e lista de adjacencia ao mesmo tempo
  secao("8. GRAFO");

  Grafo grafo;

  std::cout << "Adicionando 6 vertices (IDs 10 a 60)...\n\n";
  grafo.adicionarVertice(new ElementoNomeado(10, "A"));
  grafo.adicionarVertice(new ElementoDerivado(20, 2));
  grafo.adicionarVertice(new ElementoNomeado(30, "C"));
  grafo.adicionarVertice(new ElementoDerivado(40, 4));
  grafo.adicionarVertice(new ElementoNomeado(50, "E"));
  grafo.adicionarVertice(new ElementoDerivado(60, 6));

  std::cout << "Ligando 10-20, 10-30, 20-40, 30-40, 40-50 e 50-60...\n\n";
  grafo.adicionarAresta(10, 20);
  grafo.adicionarAresta(10, 30);
  grafo.adicionarAresta(20, 40);
  grafo.adicionarAresta(30, 40);
  grafo.adicionarAresta(40, 50);
  grafo.adicionarAresta(50, 60);

  std::cout << "Vertices: " << grafo.numeroDeVertices()
            << " | Arestas: " << grafo.numeroDeArestas() << "\n\n";

  grafo.imprimirMatriz();
  std::cout << "\n";
  grafo.imprimirListas();
  std::cout << "\n";

  std::cout << "10 e 20 sao vizinhos? "
            << (grafo.saoVizinhos(10, 20) ? "sim" : "nao") << "\n";
  std::cout << "10 e 40 sao vizinhos? "
            << (grafo.saoVizinhos(10, 40) ? "sim" : "nao") << "\n\n";

  std::cout << "grau(10) = " << grafo.grau(10) << "\n";
  std::cout << "grau(40) = " << grafo.grau(40) << "\n";
  std::cout << "grau(60) = " << grafo.grau(60) << "\n\n";

  grafo.buscaEmLargura(10);
  grafo.buscaEmProfundidade(10);

  

// 9. fila sequencial: adaptadora sobre a lista nao ordenada (FIFO)
secao("9. FILA SEQUENCIAL (LISTA NAO ORDENADA)");
 FilaSequencial fila;

 e = new ElementoDerivado(130, 13);
 std::cout << "Enfileirando: ";
 e->imprimirResumo();
 fila.enfileirar(e);

 e = new ElementoNomeado(140, "Fabi");
 std::cout << "Enfileirando: ";
 e->imprimirResumo();
 fila.enfileirar(e);

 e = new ElementoDerivado(150, 15);
 std::cout << "Enfileirando: ";
 e->imprimirResumo();
 fila.enfileirar(e);

 std::cout << "\ncheia? " << (fila.filaCheia() ? "sim" : "nao")
           << " | vazia? " << (fila.filaVazia() ? "sim" : "nao") << "\n";
 std::cout << "Inicio: ";
 fila.consultarInicio()->imprimirResumo();

 // FIFO: sai primeiro quem entrou primeiro
 std::cout << "\nDesenfileirando: ";
 fila.consultarInicio()->imprimirResumo();
 fila.desenfileirar();

 std::cout << "Desenfileirando: ";
 fila.consultarInicio()->imprimirResumo();
 fila.desenfileirar();

 std::cout << "Novo inicio: ";
 fila.consultarInicio()->imprimirResumo();

 fila.desenfileirar();
 std::cout << "Fila vazia apos esvaziar? "
           << (fila.filaVazia() ? "sim" : "nao") << "\n";



 // 10. fila encadeada: adaptadora sobre a lista simplesmente encadeada
  secao("10. FILA ENCADEADA (LISTA SIMPLES)");

  FilaEncadeada filaEnc;

  e = new ElementoDerivado(160, 16);
  std::cout << "Enfileirando: ";
  e->imprimirResumo();
  filaEnc.enfileirar(e);

  e = new ElementoNomeado(170, "Gabi");
  std::cout << "Enfileirando: ";
  e->imprimirResumo();
  filaEnc.enfileirar(e);

  e = new ElementoDerivado(180, 18);
  std::cout << "Enfileirando: ";
  e->imprimirResumo();
  filaEnc.enfileirar(e);

  std::cout << "\ncheia? " << (filaEnc.filaCheia() ? "sim" : "nao")
            << " | vazia? " << (filaEnc.filaVazia() ? "sim" : "nao") << "\n";
  std::cout << "Inicio: ";
  filaEnc.consultarInicio()->imprimirResumo();

  //sai primeiro quem entrou primeiro
  std::cout << "\nDesenfileirando: ";
  filaEnc.consultarInicio()->imprimirResumo();
  filaEnc.desenfileirar();

  std::cout << "Desenfileirando: ";
  filaEnc.consultarInicio()->imprimirResumo();
  filaEnc.desenfileirar();

  std::cout << "Novo inicio: ";
  filaEnc.consultarInicio()->imprimirResumo();

  filaEnc.desenfileirar();
  std::cout << "Fila vazia apos esvaziar? "
            << (filaEnc.filaVazia() ? "sim" : "nao") << "\n";
  
  std::cout << "\n=== Fim da demonstracao ===\n";

  return 0;
}
