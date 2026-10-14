#include "../Elemento/Elemento.h"

#ifndef DERIVADOEXEMPLO_H
#define DERIVADOEXEMPLO_H

class ElementoDerivado : Elemento {
public:
  ElementoDerivado(int id, int atributoExemplo);
  // O identificador override assume duas funções:
  // 1ª - Ela indica intenção para o leitor, especificamente a intenção de
  // que estamos sobrecarregando um método virtual puro da classe pai.
  // 2ª - Ela indica para o compilador que o método sobrecarregado é
  // originalmente da classe pai, permitindo que ele consiga checar em tempo de
  // compilação que estamos de fato sobrescrevendo um método ao invés de estar
  // adicionando um novo, nos dando mensagens de erro mais condizentes caso
  // ocorram.
  void imprimirInfo() const override;

private:
  int atributoExemplo;
};

#endif
