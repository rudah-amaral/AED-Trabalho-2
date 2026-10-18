#include "ElementoDerivado.h"

#include <iostream>

// O construtor da derivada chama o construtor da base na lista de
// inicialização: ": Elemento(id)". A base é construída primeiro; só depois
// o corpo deste construtor é executado. O atributo próprio também é
// inicializado diretamente na lista.
ElementoDerivado::ElementoDerivado(int id, int atributoExemplo)
    : Elemento(id), atributoExemplo(atributoExemplo) {
  std::cout << "Eu sou impresso toda vez que sou instanciado" << std::endl;
}

// Getter const: devolve o atributo próprio sem alterar o objeto.
int ElementoDerivado::getAtributoExemplo() const {
  return this->atributoExemplo;
}

// Setter: altera o atributo próprio.
void ElementoDerivado::setAtributoExemplo(int valor) {
  this->atributoExemplo = valor;
}

// Implementação do método virtual puro herdado de Elemento.
// Se este método não existisse, ElementoDerivado continuaria abstrata.
void ElementoDerivado::imprimirInfo() const {
  std::cout << "Oi, eu sou um ElementoDerivado!" << std::endl;
  // getID() é público e herdado; por isso pode ser chamado aqui.
  std::cout << "Tenho um atributo herdado ID que vale: " << this->getID()
            << std::endl;
  std::cout << "Tambem tenho um atributo da minha propria classe que vale: "
            << this->atributoExemplo << std::endl;
}
