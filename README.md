# BookED

Este projeto é um sistema simples para gerenciar leitores e livros, desenvolvido em C.

## Estrutura do Projeto

- `main.c`: Função principal do programa e leitura dos leitores a partir de um arquivo.
- `leitor.h` / `leitor.c`: Definição e implementação das estruturas e funções relacionadas aos leitores e suas listas.
- `leitores.txt`: Arquivo de entrada com os dados dos leitores.
- `livros.txt`: Arquivo de entrada com os dados dos livros.
- `saida.txt`: Arquivo de saída (ainda não utilizado).
- `livro.h` / `livro.c`: Reservados para implementação futura das funcionalidades de livros.

## Funcionalidades Implementadas

### Leitura e Registro de Leitores

- Leitura dos dados dos leitores a partir do arquivo [`leitores.txt`](leitores.txt).
- Estruturas de dados para armazenar leitores em uma lista encadeada ([`Leitor`](leitor.c), [`Celula`](leitor.c), [`Lista_leitores`](leitor.c)).
- Funções para criar lista de leitores, inserir leitores e imprimir a lista:
  - [`criar_lista_leitores`](leitor.c)
  - [`inserir_leitor`](leitor.c)
  - [`imprimir_lista_leitores`](leitor.c)
  - [`inicializa_leitor`](leitor.c)
  - [`imprime_leitor`](leitor.c)

### Execução

O programa principal ([`main.c`](main.c)):

- Cria uma lista de leitores.
- Lê os leitores do arquivo [`leitores.txt`](leitores.txt).
- Imprime a lista de leitores lidos.

## Próximos Passos

- Implementar as funcionalidades relacionadas aos livros em [`livro.h`](livro.h) e [`livro.c`](livro.c).
- Implementar comandos adicionais e interação com o usuário.
- Utilizar o arquivo [`saida.txt`](saida.txt) para registrar saídas do programa.

---