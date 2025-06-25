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

- **Leitores**: Lista encadeada de leitores com suas afinidades literárias, livros lidos, desejados e recomendados.
- **Livros**: Lista encadeada de livros com informações completas (título, autor, gênero, ano).
- **Rede de Afinidades**: Sistema automático que conecta leitores com preferências literárias similares.

### Sistema de Afinidades

A BookED implementa um sistema inteligente de afinidades entre leitores baseado em suas preferências de gênero literário:

- Quando os leitores são carregados, o sistema automaticamente identifica afinidades entre eles
- Leitores com pelo menos um gênero literário em comum são considerados afins
- Cada leitor mantém uma lista de outros leitores com quem tem afinidade
- **Exemplo**: Se Alice gosta de Romance e Terror, e Bob gosta de Terror e Mistério, eles terão afinidade pelo gênero Terror em comum

### Funcionalidades Principais

1. **Adicionar Livro Lido** (Comando 1): Um leitor pode marcar um livro como lido.
2. **Adicionar Livro Desejado** (Comando 2): Um leitor pode adicionar um livro à sua lista de desejos.
3. **Recomendar Livro** (Comando 3): Um leitor pode recomendar um livro para outro leitor.
4. **Aceitar Recomendação** (Comando 4): Um leitor pode aceitar uma recomendação, movendo o livro da lista de recomendados para a lista de desejados.
5. **Remover Recomendação** (Comando 5): Um leitor pode remover uma recomendação da sua lista de recomendados.
6. **Descobrir Livros em Comum** (Comando 6): Identifica livros que dois leitores leram em comum.
7. **Verificar Afinidade** (Comando 7): Verifica se dois leitores têm afinidades literárias em comum baseado em seus gêneros preferidos.

### Módulos Detalhados

#### Leitor (`leitor.h` / `leitor.c`)
- **Estruturas**: `Leitor`, `Celula`, `Lista_leitores`
- **Gerenciamento de Listas**:
  - `criar_lista_leitores()` / `inserir_leitor()` / `imprimir_lista_leitores()`
  - `libera_lista_leitores()` / `buscar_leitor_por_id()`
- **Funcionalidades do Leitor**:
  - `inicializa_leitor()` / `imprime_leitor()` / `obter_nome_leitor()`
  - `adicionar_livro_lido()` / `adicionar_livro_desejado()`
  - `recomendar_livro()` / `aceitar_recomendacao()` / `remover_recomendacao()`
  - `imprimir_livros_lidos()` / `imprimir_livros_desejados()` / `imprimir_livros_recomendados()`
- **Sistema de Afinidades**:
  - `construir_rede_afinidades()` / `calcular_afinidades_leitor()`
  - `tem_afinidade_genero()` / `imprimir_afinidades_leitor()`
- **Funcionalidades Auxiliares**:
  - `descobrir_livros_em_comum_leitores()` / `descobrir_livros_em_comum_leitores_para_saida()`

#### Livro (`livro.h` / `livro.c`)
- **Estruturas**: `Livro`, `Celula`, `Lista_livro`
- **Gerenciamento de Listas**:
  - `criar_lista_livro()` / `inserir_livro()` / `imprimir_lista_livro()`
  - `buscar_livro_por_id()` / `livro_ja_existe_na_lista()` / `remover_livro_da_lista()`
- **Funcionalidades do Livro**:
  - `inicializar_livro()` / `imprime_livro()` / `obter_titulo_livro()`
- **Análise Comparativa**:
  - `descobrir_livros_em_comum()` / `descobrir_livros_em_comum_para_saida()`

#### Arquivo (`arquivo.h` / `arquivo.c`)
- **Funções de Entrada**:
  - `registrar_leitores_from_txt()` / `registrar_livros_from_txt()`
  - `processar_comandos()`
- **Funções de Saída**:
  - `abrir_arquivo_saida()` / `fechar_arquivo_saida()` / `escrever_saida()`
- **Execução de Comandos**:
  - `executar_comando_adicionar_livro_lido()` / `executar_comando_adicionar_livro_desejado()`
  - `executar_comando_recomendar_livro()` / `executar_comando_aceitar_recomendacao()`
  - `executar_comando_remover_recomendacao()` / `executar_comando_descobrir_livros_em_comum()`
  - `executar_comando_verificar_afinidade()`

### Compilação e Execução

```bash
gcc -o bookED main.c leitor.c livro.c arquivo.c
./bookED
```

**Fluxo de Execução do Programa:**
1. Carrega leitores de `leitores.txt`
2. Carrega livros de `livros.txt`
3. **Constrói automaticamente a rede de afinidades entre leitores**
4. Processa comandos de `comandos.txt`
5. Gera relatório detalhado em `saida.txt`
6. Exibe o estado final de todos os leitores com suas afinidades

### Formato dos Arquivos de Entrada

- **leitores.txt**: `Id;nome;n_afinidades;afinidade1;afinidade2;...`
  - Exemplo: `1;Alice;2;Romance;Terror`
- **livros.txt**: `id;titulo;autor;genero;ano`
  - Exemplo: `1;O Iluminado;Stephen King;Terror;1977`
- **comandos.txt**: `funcionalidade;param1;param2;param3`
  - Exemplo: `7;1;0;2` (Verificar afinidade entre leitor 1 e leitor 2)

### Comandos Disponíveis

| ID | Comando | Parâmetros | Descrição |
|---|---|---|---|
| 1 | Adicionar Livro Lido | id_leitor;id_livro;0 | Adiciona livro à lista de lidos |
| 2 | Adicionar Livro Desejado | id_leitor;id_livro;0 | Adiciona livro à lista de desejados |
| 3 | Recomendar Livro | id_leitor_origem;id_livro;id_leitor_destino | Recomenda livro para outro leitor |
| 4 | Aceitar Recomendação | id_leitor;id_livro;0 | Move livro de recomendados para desejados |
| 5 | Remover Recomendação | id_leitor;id_livro;0 | Remove livro da lista de recomendados |
| 6 | Descobrir Livros em Comum | id_leitor1;0;id_leitor2 | Encontra livros lidos por ambos os leitores |
| 7 | Verificar Afinidade | id_leitor_origem;0;id_leitor_destino | Verifica se dois leitores têm gêneros em comum |
| 8 | Imprime BookED | 

### Arquivos de Saída

- **saida.txt**: Contém o log detalhado de todas as operações executadas

### Estrutura de Dados Utilizada

- **Listas Encadeadas**: Para gerenciar leitores, livros e suas relações
- **Estruturas Dinâmicas**: Alocação dinâmica de memória para flexibilidade
- **Rede de Relações**: Sistema de ponteiros para mapear afinidades entre leitores