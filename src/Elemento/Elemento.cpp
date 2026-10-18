#include "Elemento.h"

// Lista de inicialização: o atributo ID é inicializado diretamente com o
// valor do parâmetro, antes do corpo do construtor. É a forma idiomática de
// inicializar membros em C++.
Elemento::Elemento(int id) : ID(id) {}

// getter const: apenas devolve o valor de ID, sem modificar o objeto.
int Elemento::getID() const { return this->ID; }
