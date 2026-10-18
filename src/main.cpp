#include <iostream>

#include "Elemento/Elemento.h"
#include "ElementoDerivado/ElementoDerivado.h"
#include "ElementoNomeado/ElementoNomeado.h"

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

  return 0;
}
