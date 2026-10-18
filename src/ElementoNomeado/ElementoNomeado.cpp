#include "ElementoNomeado.h"

#include <iostream>

// A base é construída primeiro (Elemento(id)); depois o atributo nome é
// inicializado com a string recebida.
ElementoNomeado::ElementoNomeado(int id, const std::string &nome)
    : Elemento(id), nome(nome) {}

// Devolve a string por referência const: evita uma cópia desnecessária.
const std::string &ElementoNomeado::getNome() const { return this->nome; }

// Recebe a string por referência const: evita cópia na chamada.
void ElementoNomeado::setNome(const std::string &nome) { this->nome = nome; }

// Implementação própria de imprimirInfo. A saída é diferente da versão de
// ElementoDerivado: é isso que evidencia o polimorfismo quando as duas
// classes são chamadas pelo mesmo ponteiro de Elemento.
void ElementoNomeado::imprimirInfo() const {
  std::cout << "Oi, eu sou um ElementoNomeado!" << std::endl;
  std::cout << "Meu ID herdado: " << this->getID() << std::endl;
  std::cout << "Meu nome (atributo proprio): " << this->nome << std::endl;
}
