# BookED

Este projeto é um sistema para gerenciar leitores e livros, desenvolvido em C.

## Estrutura do Projeto

- `main.c`: Função principal do programa.
- `leitor.h` / `leitor.c`: Definição e implementação das estruturas e funções relacionadas aos leitores e suas listas.
- `livro.h` / `livro.c`: Definição e implementação das estruturas e funções relacionadas aos livros e suas listas.
- `arquivo.h` / `arquivo.c`: Funções para manipulação de arquivos (leitura, escrita e processamento de comandos).
- `leitores.txt`: Arquivo de entrada com os dados dos leitores.
- `livros.txt`: Arquivo de entrada com os dados dos livros.
- `comandos.txt`: Arquivo de entrada com os comandos a serem executados.
- `saida.txt`: Arquivo de saída com o relatório das ações executadas.

## Funcionalidades Implementadas

### Estruturas de Dados

- **Leitores**: Lista encadeada de leitores com suas afinidades, livros lidos, desejados e recomendados.
- **Livros**: Lista encadeada de livros com informações completas (título, autor, gênero, ano).

### Funcionalidades Principais

1. **Adicionar Livro Lido** (Comando 1): Um leitor pode marcar um livro como lido.
2. **Adicionar Livro Desejado** (Comando 2): Um leitor pode adicionar um livro à sua lista de desejos.
3. **Recomendar Livro** (Comando 3): Um leitor pode recomendar um livro para outro leitor.

### Módulos

#### Leitor (`leitor.h` / `leitor.c`)
- Estruturas: `Leitor`, `Celula`, `Lista_leitores`
- Funções principais:
  - `criar_lista_leitores()` / `inserir_leitor()` / `imprimir_lista_leitores()`
  - `inicializa_leitor()` / `imprime_leitor()`
  - `adicionar_livro_lido()` / `adicionar_livro_desejado()`
  - `recomendar_livro()` / `aceitar_recomendacao()`
  - `buscar_leitor_por_id()`

#### Livro (`livro.h` / `livro.c`)
- Estruturas: `Livro`, `Celula`, `Lista_livro`
- Funções principais:
  - `criar_lista_livro()` / `inserir_livro()` / `imprimir_lista_livro()`
  - `inicializar_livro()` / `imprime_livro()`
  - `buscar_livro_por_id()` / `obter_titulo_livro()`
  - `livro_ja_existe_na_lista()` / `remover_livro_da_lista()`

#### Arquivo (`arquivo.h` / `arquivo.c`)
- Funções de leitura:
  - `registrar_leitores_from_txt()` / `registrar_livros_from_txt()`
  - `processar_comandos()`
- Funções de escrita:
  - `abrir_arquivo_saida()` / `fechar_arquivo_saida()` / `escrever_saida()`
- Execução de comandos:
  - `executar_comando_adicionar_livro_lido()`
  - `executar_comando_adicionar_livro_desejado()`
  - `executar_comando_recomendar_livro()`

### Compilação e Execução

```bash
gcc -o bookeditor main.c leitor.c livro.c arquivo.c
./bookeditor
```

O programa:
1. Carrega leitores de `leitores.txt`
2. Carrega livros de `livros.txt`
3. Processa comandos de `comandos.txt`
4. Gera relatório em `saida.txt`
5. Exibe o estado final dos leitores

### Formato dos Arquivos

- **leitores.txt**: `Id;nome;n_afinidades;afinidade1;afinidade2;...`
- **livros.txt**: `id;titulo;autor;genero;ano`
- **comandos.txt**: `funcionalidade;param1;param2;param3`
- **saida.txt**: Relatório textual das ações executadas

## Próximos Passos

- Implementar comando para aceitar recomendações
- Adicionar validações adicionais
- Implementar funcionalidades de busca e filtragem

---