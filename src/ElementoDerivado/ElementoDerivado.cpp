#include "ElementoDerivado.h"
#include <iostream>

// Mais uma implementação de um construtor, agora de uma classe herdeira.
// Observe como ela chama o construtor do pai.
ElementoDerivado::ElementoDerivado(int id, int atributoExemplo) : Elemento(id) {
  this->atributoExemplo = atributoExemplo;
  std::cout << "Eu sou impresso toda vez que sou instanciado" << std::endl;
}

// Implementação do método virtual puro imprimirInfo. Se ele não fosse
// implementado, permaneceria virtual (duh), o que implicaria em
// ElementoDerivado ser uma classe abstrata também.
void ElementoDerivado::imprimirInfo() const {
  std::cout << "Oi, eu sou um objeto que herda de Elemento!" << std::endl;
  std::cout << "Tenho um atributo herdado id que vale: " << this->getId()
            << std::endl;
  std::cout << "Também tenho um atributo da minha própria classe que vale: "
            << this->atributoExemplo << std::endl;
}
