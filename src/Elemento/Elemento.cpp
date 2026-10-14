#include "Elemento.h"

// Para a implementação do construtor, dizemos que o id do objeto instanciado
// (this) recebe o valor do parâmetro id.
Elemento::Elemento(int id) { this->id = id; }

// De forma semelhante, a implementação de getId retorna o id do elemento
// instanciado.
int Elemento::getId() const { return this->id; }
