#ifndef LISTA_H
#define LISTA_H

#include "../Elemento/Elemento.h"

// Interface abstrata das listas: a nao ordenada e a ordenada
// implementam os mesmos metodos.
class Lista {
public:
  virtual ~Lista() = default;

  virtual bool inserirNoInicio(Elemento *elemento) = 0;
  virtual bool inserirNoFinal(Elemento *elemento) = 0;
  virtual bool removerPrimeiro() = 0;
  virtual bool removerUltimo() = 0;
  virtual bool removerPeloId(int id) = 0;
  virtual Elemento *buscarPeloId(int id) const = 0;
  virtual bool alterarPeloId(int id, Elemento *novo) = 0;
};

#endif
