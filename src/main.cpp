#include <iostream>

#include "Elemento/Elemento.h"
#include "ElementoDerivado/ElementoDerivado.h"
#include "ElementoNomeado/ElementoNomeado.h"
#include "ListaNaoOrdenada/ListaNaoOrdenada.h"

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

  return 0;
}
