# Trabalho 2 de Algoritmos e Estruturas de Dados

## Instruções de uso

Para compilar o projeto use o comando `make`. Ele seguirá as instruções definidas no [Makefile](Makefile).

Para gerar o arquivo `compile_commands.json` para habilitar compleção de código através de uma LSP, use o comando `bear -- make`. Se você não sabe o que isso significa, pode ignorar sem problemas.

## Análise Computacional das operações das estruturas de dados

### ListaNaoOrdenada

| *Operação*  | *Complexidade* |
|------------------|-------------|
| inserirNoInicio            | O(n)            |
| inserirNoFinal            | O(1) amortizado            |
| removerPrimeiro            | O(1)            |
| removerUltimo            | O(1)            |
| removerPeloId            | O(n)            |
| buscarPeloId            | O(n)            |
| alterarPeloId            | O(n)            |
| obter            | O(1)            |
| tamanho            | O(1)            |
| capacidade            | O(1)            |
| vazia            | O(1)            |
| buscarIndice            | O(n)            |
| garantirCapacidade            | O(n)*            |

### ListaOrdenada
| *Operação*  | *Complexidade* |
|------------------|-------------|
| inserirNoInicio            | O(n)            |
| inserirNoFinal            | O(n)             |
| removerPrimeiro            | O(n)            |
| removerUltimo            | O(1)            |
| removerPeloId            | O(n)            |
| buscarPeloId            | O(log n)            |
| alterarPeloId            | O(log n)            |
| obter            | O(1)            |
| tamanho            | O(1)            |
| capacidade            | O(1)            |
| vazia            | O(1)            |
| buscarIndice            | O(log n)            |
| posicaoDeInsercao            | O(log n)            |
| inserirOrdenado            | O(n)            |
| garantirCapacidade            | O(n)*            |

### Pilha - Lista não ordenada
| *Operação*  | *Complexidade* |
|------------------|-------------|
| empilhar            | O(1) amortizado            |
| desempilhar            | O(1)             |
| empilhar            | O(1)          |
| consultarTopo            | O(1)          |
| pilhaCheia            | O(1)          |
| pilhaVazia            | O(1)          |
| tamanho            | O(1)          |

### FilaSequencial
| *Operação*  | *Complexidade* |
|------------------|-------------|
| enfileirar            | O(1) amortizado            |
| desenfileirar            | O(1)             |
| consultarInicio            | O(1)          |
| filaCheia            | O(1)  |
| filaVazia            | O(1)          |

### Deque
| *Operação*  | *Complexidade* |
|------------------|-------------|
| inserirNoInicio            | O(1)            |
| inserirNoFim            | O(1)             |
| removerInicio            | O(1)          |
| removerFim            | O(1)          |
| consultarInicio            | O(1)          |
| consultarFim            | O(1)          |
| vazia            | O(1)          |
| tamanho            | O(1)          |

### ListaSimplesmenteEncadeada
| *Operação*  | *Complexidade* |
|------------------|-------------|
| inserirNoInicio            | O(1)            |
| inserirNoFinal            | O(1)             |
| removerPrimeiro            | O(1)          |
| removerPrimeiro            | O(n)          |
| removerPeloId            | O(n)          |
| buscarPeloId            | O(n)          |
| alterarPeloId            | O(n)          |
| obter            | O(n)          |
| tamanho            | O(1)          |
| vazia            | O(1)          |

### ListaDuplamenteEncadeadaCircular
| *Operação*  | *Complexidade* |
|------------------|-------------|
| inserirNoInicio            | O(1)            |
| inserirNoFinal            | O(1)             |
| removerPrimeiro            | O(1)          |
| removerPrimeiro            | O(1)          |
| removerPeloId            | O(n)          |
| buscarPeloId            | O(n)          |
| alterarPeloId            | O(n)          |
| obter            | O(n)          |
| tamanho            | O(1)          |
| vazia            | O(1)          |

### ListaDuplamenteEncadeada
| *Operação*  | *Complexidade* |
|------------------|-------------|
| inserirNoInicio            | O(1)            |
| inserirNoFinal            | O(1)             |
| removerPrimeiro            | O(1)          |
| removerPrimeiro            | O(1)          |
| removerPeloId            | O(n)          |
| buscarPeloId            | O(n)          |
| alterarPeloId            | O(n)          |
| obter            | O(n)          |
| tamanho            | O(1)          |
| vazia            | O(1)          |

### FilaEncadeada
| *Operação*  | *Complexidade* |
|------------------|-------------|
| enfileirar            | O(1) amortizado            |
| desenfileirar            | O(1)             |
| consultarInicio            | O(1)          |
| filaCheia            | O(1)  |
| filaVazia            | O(1)          |

### PilhaEncadeada
| *Operação*  | *Complexidade* |
|------------------|-------------|
| empilhar            | O(1)            |
| desempilhar            | O(1)             |
| empilhar            | O(1)          |
| consultarTopo            | O(1)          |
| pilhaCheia            | O(1)          |
| pilhaVazia            | O(1)          |
| tamanho            | O(1)          |


### FilaEncadeada
| *Operação*  | *Complexidade* |
|------------------|-------------|
| empilhar            | O(1)            |
| desempilhar            | O(1)             |
| empilhar            | O(1)          |
| consultarTopo            | O(1)          |
| pilhaCheia            | O(1)          |
| pilhaVazia            | O(1)          |
| tamanho            | O(1)          |
### ArvoreBinariaBusca
| *Operação*  | *Complexidade* |
|------------------|-------------|
| inserir            | O(h)            |
| buscarPeloId            | O(h)            |
| removerPeloId            | O(h)            |
| emOrdem            | O(n)            |
| preOrdem            | O(n)            |
| posOrdem            | O(n)            |
| imprimirEstrutura            | O(n)            |
| altura            | O(n)            |
| tamanho            | O(1)            |
| vazia            | O(1)            |
| insere            | O(h)            |
| busca            | O(h)            |
| remove            | O(h)            |
| minimo            | O(h)            |
| removeMin            | O(h)            |
| limpa            | O(n)            |
| emOrdemNo            | O(n)            |
| preOrdemNo            | O(n)            |
| posOrdemNo            | O(n)            |
| estruturaNo            | O(n)            |
| alturaNo            | O(n)            |


## Integrantes do Grupo

Renan Da Silva Barros

Rudah Coutinho Amaral

Ítalo Rosa Gonçalves
