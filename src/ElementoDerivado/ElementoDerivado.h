#ifndef ELEMENTODERIVADO_H
#define ELEMENTODERIVADO_H

#include "../Elemento/Elemento.h"

// Primeira classe concreta de demonstração.
//
// A herança é PÚBLICA: "ElementoDerivado é um Elemento". Isso preserva a
// relação "é um" e permite guardar um ElementoDerivado em um Elemento*,
// que é exatamente o que o polimorfismo da Parte I precisa.
// Em C++, a herança padrão de "class" é privada; por isso o "public" é
// obrigatório aqui.
class ElementoDerivado : public Elemento {
public:
  ElementoDerivado(int id, int atributoExemplo);

  // Métodos específicos desta classe (além do imprimirInfo herdado).
  int getAtributoExemplo() const;
  void setAtributoExemplo(int valor);

  // O "override" avisa o compilador que este método sobrescreve um método
  // virtual da classe pai. Se a assinatura não bater (por exemplo, faltar
  // const), o compilador gera erro em vez de criar um método novo sem querer.
  void imprimirInfo() const override;

  // Versao compacta, usada quando a lista imprime todos os elementos.
  void imprimirResumo() const override;

private:
  // Atributo próprio da classe derivada. É privado: nem a classe pai nem
  // outras classes conseguem acessá-lo diretamente.
  int atributoExemplo;
};

#endif
