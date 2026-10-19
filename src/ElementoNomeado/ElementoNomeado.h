#ifndef ELEMENTONOMEADO_H
#define ELEMENTONOMEADO_H

#include <string>

#include "../Elemento/Elemento.h"

// Segunda classe concreta de demonstração.
//
// Ela também herda publicamente de Elemento, mas possui um estado próprio
// diferente: um nome (std::string). Isso mostra que a mesma estrutura pode
// armazenar objetos de tipos diferentes, desde que todos sejam Elemento.
class ElementoNomeado : public Elemento {
public:
  ElementoNomeado(int id, const std::string &nome);

  // Métodos específicos desta classe.
  // Retorna uma referência const para evitar copiar a string.
  const std::string &getNome() const;
  void setNome(const std::string &nome);

  // Sobrescreve o método virtual puro de Elemento.
  void imprimirInfo() const override;

  // Versao compacta, usada quando a lista imprime todos os elementos.
  void imprimirResumo() const override;

private:
  std::string nome;
};

#endif
