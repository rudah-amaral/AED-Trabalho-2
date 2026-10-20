#include "ElementoDerivado.h"

#include <iomanip>
#include <iostream>

// O construtor da derivada chama o construtor da base na lista de
// inicialização: ": Elemento(id)". A base é construída primeiro; só depois
// o corpo deste construtor é executado. O atributo próprio também é
// inicializado diretamente na lista.
ElementoDerivado::ElementoDerivado(int id, int atributoExemplo)
    : Elemento(id), atributoExemplo(atributoExemplo) {}

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
  std::cout << "    Oi, eu sou um ElementoDerivado!" << std::endl;
  // getID() é público e herdado; por isso pode ser chamado aqui.
  std::cout << "    Tenho um atributo herdado ID que vale: " << this->getID()
            << std::endl;
  std::cout
      << "    Tambem tenho um atributo da minha propria classe que vale: "
      << this->atributoExemplo << std::endl;
}

// Versao compacta em colunas, usada nas tabelas das listas.
void ElementoDerivado::imprimirResumo() const {
  std::cout << std::left << std::setw(16) << "ElementoDerivado" << " | "
            << std::right << std::setw(4) << this->getID() << " | valor: "
            << this->atributoExemplo << std::endl;
}
