#ifndef LISTAORDENADA_H
#define LISTAORDENADA_H

#include "../Lista/Lista.h"

// Lista sequencial ordenada por ID, com capacidade dinamica.
// A lista e dona dos Elementos* e do bloco (o destrutor libera tudo).
class ListaOrdenada : public Lista {
public:
  static constexpr int CAPACIDADE_INICIAL = 10;

  ListaOrdenada();

  // sem copia: a lista e dona dos ponteiros (evita double delete)
  ListaOrdenada(const ListaOrdenada &) = delete;
  ListaOrdenada &operator=(const ListaOrdenada &) = delete;

  ~ListaOrdenada() override;

  // na ordenada os dois inserem na posicao certa (nome vem do PDF)
  bool inserirNoInicio(Elemento *elemento) override; // O(n)
  bool inserirNoFinal(Elemento *elemento) override;  // O(n)

  // remocoes: destroem o elemento e devolvem false se nao achar
  bool removerPrimeiro() override;     // O(n) - desloca todo mundo
  bool removerUltimo() override;       // O(1)
  bool removerPeloId(int id) override; // O(n)

  // busca e alteracao
  Elemento *buscarPeloId(int id) const override;       // O(log n)
  bool alterarPeloId(int id, Elemento *novo) override; // O(log n)

  // acesso e estado
  Elemento *obter(int indice) const; // O(1)
  int tamanho() const;               // O(1)
  int capacidade() const;            // O(1)
  bool vazia() const;                // O(1)

private:
  // posicao do ID no array (busca binaria), ou -1
  int buscarIndice(int id) const; // O(log n)

  // primeira posicao com ID >= id: onde inserir
  int posicaoDeInsercao(int id) const; // O(log n)

  // insere na posicao ordenada; rejeita duplicado
  bool inserirOrdenado(Elemento *elemento); // O(n)

  // garante espaco; dobra o bloco se estiver cheio
  void garantirCapacidade(); // O(n) quando cresce

  Elemento **elementos; // bloco alocado com new[]
  int quantidade;       // posicoes validas: 0..quantidade-1
  int capacidadeAtual;  // tamanho do bloco
};

#endif
