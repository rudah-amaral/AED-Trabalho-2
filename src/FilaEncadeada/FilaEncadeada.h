#ifndef FILAENCADEADA_H
#define FILAENCADEADA_H

#include "../ListaSimplesmenteEncadeada/ListaSimplesmenteEncadeada.h"

// A entrada e o FIM da lista (usa a cauda) e a saida e o INICIO, entao
// enfileirar/desenfileirar sao O(1). Corrige o problema da FilaSequencial
// de remover o primeiro elemento e ter que deslocar todos os demais com O(n).
class FilaEncadeada {
public:
  FilaEncadeada();

  // sem copia: os elementos pertencem a lista interna
  FilaEncadeada(const FilaEncadeada &) = delete;
  FilaEncadeada &operator=(const FilaEncadeada &) = delete;

  ~FilaEncadeada();

  bool enfileirar(Elemento *elemento); // O(1)
  bool desenfileirar();                // O(1)
  Elemento *consultarInicio() const;   // O(1)
  bool filaCheia() const;              // sempre falso (lista encadeada cresce)
  bool filaVazia() const;              // O(1)

private:
  ListaSimplesmenteEncadeada lista; // composicao
};

#endif
