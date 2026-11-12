# Trabalho 2 de Algoritmos e Estruturas de Dados

## Instruções de uso

Para compilar o projeto use o comando `make`. Ele seguirá as instruções definidas no [Makefile](Makefile).

Para gerar o arquivo `compile_commands.json` para habilitar compleção de código através de uma LSP, use o comando `bear -- make`. Se você não sabe o que isso significa, pode ignorar sem problemas.

## Grafo (Parte II)

### Decisões de design

- **As duas formas de armazenamento ao mesmo tempo** (exigência do PDF): a matriz de adjacência responde "são vizinhos?" em O(1), enquanto as listas de adjacência percorrem apenas os vizinhos, o que torna grau e percursos eficientes.
- **Vértice = `Elemento*`**: mantém o padrão das outras estruturas (o grafo é dono dos elementos e o destrutor libera tudo). O ID do elemento é a chave pública, então o grafo aceita `ElementoDerivado` e `ElementoNomeado` misturados.
- **Grafo não direcionado e sem pesos**: a aresta `(u, v)` vale nos dois sentidos; por isso a matriz é simétrica e cada aresta ocupa uma posição nas duas listas.
- **Laço e aresta repetida são rejeitados**: `adicionarAresta` devolve `false` nos dois casos, evitando grau duplicado e linhas duplicadas nas listas.
- **Cópia proibida** (`= delete`): o grafo é dono de ponteiros crus; uma cópia rasa levaria a double delete.
- **Nó da lista é classe privada**: o usuário do grafo não enxerga o detalhe de implementação (PDF, Parte II).

### Complexidades do Grafo

| Operação | Complexidade | Motivo |
|---|---|---|
| `adicionarVertice` | **O(V²)** | a matriz V×V é alocada e copiada de novo |
| `adicionarAresta` | **O(V)** | dois `indicePeloId` (busca linear) + O(1) nas listas |
| `saoVizinhos` | **O(V)** | `indicePeloId` + O(1) na matriz |
| `grau` | **O(V + grau)** | `indicePeloId` + percorre a lista de vizinhos |
| `buscaEmLargura` (BFS) | **O(V + E)** | cada vértice e cada aresta são examinados uma vez |
| `buscaEmProfundidade` (DFS) | **O(V + E)** | idem, com recursão |
| `numeroDeVertices` / `numeroDeArestas` / `vazio` | **O(1)** | leitura de contadores |
| `imprimirMatriz` | **O(V²)** | percorre todas as células |
| `imprimirListas` | **O(V + E)** | percorre vértices e arestas |
| destrutor | **O(V² + E)** | libera matriz, listas e elementos |
| `indicePeloId` (auxiliar) | **O(V)** | busca linear no vetor de vértices |

