#ifndef ELEMENTO_H
#define ELEMENTO_H

// Classe abstrata que representa qualquer elemento que pode ser armazenado
// nas estruturas de dados do trabalho. Ela define o "contrato" mínimo que
// todos os elementos concretos devem cumprir: ter um ID e saber se apresentar.
class Elemento {
public:
  // Construtor protegido? Não: ele é público para que as classes derivadas
  // possam chamá-lo na lista de inicialização. O "explicit" impede que um int
  // seja convertido implicitamente em um Elemento.
  explicit Elemento(int id);

  // Getter público e const: o ID é um atributo protegido, então o acesso
  // externo acontece exclusivamente por aqui. O const garante que o método
  // não altera o estado do objeto.
  int getID() const;

  // Método virtual puro: torna a classe abstrata (não pode ser instanciada)
  // e obriga todas as classes concretas a implementarem sua própria versão.
  virtual void imprimirInfo() const = 0;

  // Destrutor virtual: essencial para que, ao deletar um objeto através de um
  // ponteiro para Elemento, o destrutor da classe derivada seja chamado.
  // Sem ele, o comportamento é indefinido (e recursos da derivada podem vazar).
  virtual ~Elemento() = default;

protected:
  // ID é protegido: acessível apenas por Elemento e por suas classes
  // derivadas. Como Elemento é abstrata, na prática ele é usado pelas filhas.
  int ID;
};

#endif
