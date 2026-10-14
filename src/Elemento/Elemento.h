#ifndef ELEMENTO_H
#define ELEMENTO_H

class Elemento {
public:
  // Sobrescrevemos o construtor padrão, estabelecendo um parâmetro int.
  Elemento(int id);

  // Declaramos um getter para o atributo int.
  int getId() const;

  // Declaramos um método virtual puro, o que torna a classe automaticamente
  // abstrata e, portanto, impedimos a sua instanciação.
  // As classes que herdarem de Elemento tem como compromisso implementar esse
  // método.
  virtual void imprimirInfo() const = 0;

protected:
  // Id é um atributo protegido, isso o torna acessível apenas para a classe
  // Elemento e seus herdeiros. Porém, como Elemento é uma classe abstrata (ou
  // seja, que não podemos instanciar), id é somente acessível para as classes
  // herdeiras.
  //
  // NOTA: Acredito que id poderia ser um atributo privado, inacessível para
  // qualquer classe que não Elemento, já que declaramos um getter público para
  // ela.
  int id;
};

#endif
