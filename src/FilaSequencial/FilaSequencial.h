#ifndef FILASEQUENCIAL_H
#define FILASEQUENCIAL_H

#include "../Elemento/Elemento.h"
#include "../ListaNaoOrdenada/ListaNaoOrdenada.h"

// Fila (FIFO) sequencial, implementada como adaptadora da ListaNaoOrdenada.

// A fila guarda uma lista por composicao e restringe o acesso a apenas duas pontas:
//   - entrada: sempre no final  da lista
//   - saida:   sempre no inicio da lista

// Limitacao conhecida: como a lista e sequencial, remover o primeiro
// elemento exige deslocar todos os demais (O(n)). A FilaEncadeada resolve o problema

class FilaSequencial {
public:
  FilaSequencial() = default;

  // Proibe copia: a lista interna e dona dos elementos, e copiar a fila
  // faria dois objetos tentarem deletar os mesmos ponteiros.
  FilaSequencial(const FilaSequencial &) = delete;
  FilaSequencial &operator=(const FilaSequencial &) = delete;

  // Insere o elemento no fim da fila.
  void enfileirar(Elemento *elemento);

  // Remove o elemento do inicio da fila (nao faz nada se estiver vazia).
  void desenfileirar();

  // Consulta o inicio sem remover. Devolve nullptr se a fila estiver vazia.
  Elemento *consultarInicio() const;

  // Espelha o pilhaCheia(): a lista cresce sozinha, entao nunca fica cheia.
  bool filaCheia() const;

  bool filaVazia() const;

private:
  // Composicao: a fila "tem uma lista". O proprio destrutor da lista libera os
  // elementos, entao a fila nao precisa de destrutor proprio.
  ListaNaoOrdenada lista;
};

#endif
