#ifndef LISTANAOORDENADA_H
#define LISTANAOORDENADA_H

#include "../Lista/Lista.h"

// Lista sequencial nao ordenada, com capacidade dinamica.
// A lista e dona dos Elementos* e do bloco (o destrutor libera tudo).
class ListaNaoOrdenada : public Lista {
public:
  static constexpr int CAPACIDADE_INICIAL = 10;

  ListaNaoOrdenada();

  // sem copia: a lista e dona dos ponteiros (evita double delete)
  ListaNaoOrdenada(const ListaNaoOrdenada &) = delete;
  ListaNaoOrdenada &operator=(const ListaNaoOrdenada &) = delete;

  ~ListaNaoOrdenada() override;

  // insercoes: false so se o ponteiro for nulo (a lista cresce sozinha)
  bool inserirNoInicio(Elemento *elemento) override; // O(n)
  bool inserirNoFinal(Elemento *elemento) override;  // O(1) amortizado

  // remocoes: destroem o elemento e devolvem false se nao achar
  bool removerPrimeiro() override;     // O(1)
  bool removerUltimo() override;       // O(1)
  bool removerPeloId(int id) override; // O(n)

  // busca e alteracao
  Elemento *buscarPeloId(int id) const override;       // O(n)
  bool alterarPeloId(int id, Elemento *novo) override; // O(n) - mantem a chave

  // acesso e estado
  Elemento *obter(int indice) const; // O(1)
  int tamanho() const;               // O(1)
  int capacidade() const;            // O(1)
  bool vazia() const;                // O(1)

private:
  // indice do ID no array, ou -1
  int buscarIndice(int id) const; // O(n)

  // garante espaco; dobra o bloco se estiver cheio
  void garantirCapacidade(); // O(n) quando cresce

  Elemento **elementos; // bloco alocado com new[]
  int quantidade;       // posicoes validas: 0..quantidade-1
  int capacidadeAtual;  // tamanho do bloco
};

#endif
