# Campo Minado Recursivo em C

Implementação do jogo **Campo Minado Recursivo** em linguagem C pura, desenvolvida para a **Atividade Avaliativa 1** da disciplina de **Estrutura de Dados**.

O projeto utiliza matrizes bidimensionais para representar o tabuleiro, geração pseudoaleatória para posicionar as minas e recursividade para abrir automaticamente regiões formadas por casas sem minas próximas.

## Identificação do projeto

| Informação | Descrição |
|---|---|
| **Nome do game** | Campo Minado Recursivo |
| **Tema** | Aplicação da recursividade em um jogo |
| **Linguagem** | C pura |
| **Metodologia ativa** | Aprendizagem por Projeto |
| **Atividade** | Atividade Avaliativa 1 |
| **Período de entrega** | 15 a 22 de setembro de 2026 |
| **Valor** | 1,5 ponto |
| **Forma de avaliação** | Apresentação em sala e respostas às perguntas do professor |

O grupo possui **cinco integrantes**, atendendo ao limite estabelecido de quatro a seis acadêmicos.

## Acadêmicos

- **João Victor Queiroz de Lima** - RA: 2051524
- **Leonardo Di Camargo Rodrigues** - RA: 2809028
- **Luiz Gustavo Mendes Lemes** - RA: 2618028
- **Micael Marinho Souza** - RA: 2819457
- **Wagner Lourenço de Oliveira Junior** - RA: 2819473

## Informações acadêmicas

- **Instituição:** Universidade Tecnológica Federal do Paraná - UTFPR
- **Câmpus:** Cornélio Procópio
- **Curso:** Tecnologia em Análise e Desenvolvimento de Sistemas
- **Disciplina:** Estrutura de Dados
- **Professor:** Prof. Dr. Clayton Kossoski
- **Período:** 2º semestre de 2026

## Atendimento aos requisitos da atividade

| Requisito | Como foi atendido |
|---|---|
| Aplicar recursividade em um jogo | A função `abrirCasa()` chama a si mesma para revelar as casas vizinhas de uma região vazia. |
| Utilizar C pura | O projeto foi desenvolvido em C e utiliza somente as bibliotecas padrão `stdio.h`, `stdlib.h` e `time.h`. |
| Equipe entre 4 e 6 integrantes | O grupo é formado pelos cinco acadêmicos relacionados neste README. |
| Código-fonte comentado | O arquivo `campo_minado.c` contém comentários que identificam as principais etapas do algoritmo. |
| Repositório público no GitHub | O repositório deve permanecer público para permitir o acesso ao código e ao README durante a avaliação. |
| Instruções de execução | As etapas de compilação e execução estão documentadas neste arquivo. |

## Objetivo

O objetivo do projeto é aplicar, de forma prática, os principais conceitos estudados na disciplina, especialmente a **recursividade** e o funcionamento da **pilha de chamadas**.

Além disso, o programa trabalha com:

- matrizes bidimensionais;
- funções;
- estruturas de repetição;
- estruturas condicionais;
- validação de coordenadas;
- geração de números pseudoaleatórios;
- controle de posições abertas;
- condições de vitória e derrota.

## Funcionalidades

- Definição personalizada da quantidade de linhas e colunas;
- Tabuleiro configurável entre `2 x 2` e `20 x 20`;
- Escolha da quantidade de minas;
- Validação do tamanho do campo e do número de minas;
- Distribuição pseudoaleatória das minas;
- Garantia de que a primeira jogada válida seja segura;
- Cálculo automático da quantidade de minas ao redor de cada posição;
- Abertura recursiva das regiões vazias;
- Identificação automática de vitória e derrota;
- Exibição das minas ao final da partida.

## Primeira jogada segura

Nesta versão, as minas não são geradas no início do programa. Elas são posicionadas somente depois que o jogador informa a primeira coordenada válida.

A função responsável recebe a linha e a coluna da primeira jogada:

```c
void colocarMinas(int linhaSegura, int colunaSegura)
```

Durante a distribuição, essa coordenada é ignorada:

```c
if (linha == linhaSegura && coluna == colunaSegura)
{
    continue;
}
```

Desse modo, a primeira casa escolhida nunca contém uma mina. Após a distribuição, o programa calcula os números de todas as casas seguras.

## Representação do tabuleiro

O jogo utiliza duas matrizes globais:

```c
int campo[MAX_LINHAS][MAX_COLUNAS];
int aberto[MAX_LINHAS][MAX_COLUNAS];
```

### Matriz `campo`

Armazena o conteúdo real de cada posição:

| Valor | Significado |
|---:|---|
| `-1` | A posição contém uma mina |
| `0` | Não existem minas nas posições vizinhas |
| `1` a `8` | Quantidade de minas ao redor da posição |

### Matriz `aberto`

Controla quais posições já foram reveladas:

| Valor | Significado |
|---:|---|
| `0` | Casa fechada |
| `1` | Casa aberta ou já visitada |

A matriz `aberto` não representa a pilha da recursividade. Ela funciona como um registro das posições já processadas, impedindo que uma mesma casa seja visitada indefinidamente.

## Estrutura do programa

O programa foi dividido em funções, cada uma responsável por uma parte específica do jogo.

### `escolherDificuldade()`

Solicita a quantidade de linhas, colunas e minas. A função utiliza estruturas `do while` para repetir a leitura enquanto os valores informados forem inválidos.

As dimensões aceitas variam de `2` a `20`. A quantidade de minas deve ser pelo menos `1` e menor que o total de casas, garantindo a existência de uma posição segura.

### `inicializarJogo()`

Percorre a área utilizada das duas matrizes e atribui zero a todas as posições:

- `campo[i][j] = 0`: posição inicialmente sem mina e sem número calculado;
- `aberto[i][j] = 0`: posição inicialmente fechada.

### `colocarMinas(int linhaSegura, int colunaSegura)`

Distribui a quantidade escolhida de minas em posições pseudoaleatórias.

A geração das coordenadas utiliza:

```c
int linha = rand() % linhas;
int coluna = rand() % colunas;
```

A função não coloca uma mina na primeira casa escolhida e também verifica se a posição sorteada já contém `-1`, evitando que duas minas ocupem a mesma casa.

### `posicaoValida(int linha, int coluna)`

Verifica se uma coordenada está dentro dos limites definidos pelo usuário.

A função retorna verdadeiro quando:

```c
linha >= 0 && linha < linhas &&
coluna >= 0 && coluna < colunas
```

Essa verificação é importante principalmente nas bordas do tabuleiro e durante as chamadas recursivas.

### `contarMinasAoRedor(int linha, int coluna)`

Analisa as posições vizinhas de uma casa e retorna quantas delas contêm minas.

Os dois laços variam de `-1` a `1`, permitindo examinar uma região de até `3 x 3` ao redor da posição recebida. Antes de acessar uma posição vizinha, o programa verifica se ela está dentro do tabuleiro.

### `calcularNumeros()`

Percorre todo o campo depois da colocação das minas. Para cada casa que não contém `-1`, chama `contarMinasAoRedor()` e armazena o resultado na matriz `campo`.

Assim, cada posição segura passa a armazenar um número entre `0` e `8`.

### `abrirCasa(int linha, int coluna)`

É a principal função recursiva do projeto.

Quando uma casa com valor zero é aberta, a função chama a si mesma para visitar as oito posições vizinhas:

```c
abrirCasa(linha + i, coluna + j);
```

A expansão possui três condições de parada:

1. A posição está fora do tabuleiro;
2. A posição já foi aberta;
3. A posição possui valor diferente de zero.

Antes de visitar os vizinhos, a posição atual é marcada como aberta:

```c
aberto[linha][coluna] = 1;
```

Essa marcação impede chamadas repetidas e evita uma recursão infinita. O comportamento é semelhante ao algoritmo **Flood Fill**, utilizado para explorar regiões conectadas.

### `mostrarCampo(int mostrarMinas)`

Exibe o tabuleiro no terminal.

| Símbolo | Significado |
|:---:|---|
| `#` | Casa fechada |
| Espaço | Casa aberta sem minas ao redor |
| `1` a `8` | Quantidade de minas vizinhas |
| `*` | Mina revelada ao final da partida |

O parâmetro `mostrarMinas` funciona como um valor lógico:

- `0`: mantém as minas escondidas durante a partida;
- `1`: revela as minas após a vitória ou derrota.

### `verificarVitoria()`

Percorre o tabuleiro procurando alguma posição que não seja mina e ainda esteja fechada.

Se encontrar uma casa segura fechada, retorna `0`. Se terminar a verificação sem encontrar nenhuma, retorna `1`, indicando que todas as casas seguras foram abertas.

### `main()`

Controla o fluxo principal do programa:

1. Inicializa a semente do gerador pseudoaleatório;
2. Solicita e valida as configurações;
3. Inicializa as matrizes;
4. Exibe o campo e recebe uma jogada;
5. Valida a coordenada informada;
6. Gera as minas depois da primeira jogada válida;
7. Calcula os números do campo;
8. Verifica se o jogador selecionou uma mina;
9. Abre a posição escolhida;
10. Verifica a condição de vitória;
11. Revela o campo e apresenta o resultado final.

## Recursividade e pilha de chamadas

Recursividade ocorre quando uma função chama a si mesma. Neste projeto, cada chamada de `abrirCasa()` possui seu próprio contexto, incluindo:

- os parâmetros `linha` e `coluna`;
- as variáveis locais;
- o ponto para o qual a execução deverá retornar.

Esses contextos são mantidos na pilha de chamadas. Quando uma condição de parada executa `return`, a chamada atual termina e a execução retorna para a chamada anterior.

A matriz `aberto` complementa esse processo ao registrar todas as posições já visitadas, inclusive aquelas cujas chamadas já foram finalizadas.

## Estrutura esperada do repositório

```text
campo-minado-recursivo/
├── campo_minado.c
└── README.md
```

- `campo_minado.c`: código-fonte comentado do jogo;
- `README.md`: descrição, funcionamento e instruções de execução.

> Caso o arquivo-fonte tenha outro nome no repositório, os comandos de compilação devem ser ajustados para usar o nome correspondente.

## Compilação e execução

O programa não utiliza bibliotecas externas. É necessário apenas possuir um compilador compatível com C, como o GCC.

### Pré-requisitos

- GCC, MinGW, MSYS2 ou outro compilador C;
- Terminal, prompt de comando, ou VSCODE;
- Arquivo `campo_minado.c` salvo no diretório do projeto.

### Windows com GCC/MinGW ou MSYS2

```bash
gcc campo_minado.c -o campo_minado.exe
./campo_minado.exe
```

### Linux

```bash
gcc campo_minado.c -o campo_minado
./campo_minado
```

## Como jogar

1. Execute o programa pelo terminal;
2. Informe a quantidade de linhas, entre `2` e `20`;
3. Informe a quantidade de colunas, entre `2` e `20`;
4. Escolha a quantidade de minas, respeitando o limite exibido;
5. Digite o número da linha e da coluna da casa que deseja abrir;
6. Continue escolhendo posições até abrir todas as casas seguras ou encontrar uma mina.

A primeira jogada válida é protegida. As minas são geradas somente depois dessa escolha e a coordenada informada não pode receber uma mina.

### Símbolos apresentados

| Símbolo | Significado |
|:---:|---|
| `#` | Casa fechada |
| Espaço vazio | Casa aberta sem minas vizinhas |
| `1` a `8` | Quantidade de minas nas posições vizinhas |
| `*` | Mina revelada no encerramento da partida |

## Exemplo de uso

```text
Quantidade de linhas (2 a 20): 5
Quantidade de colunas (2 a 20): 5
Quantidade de minas: 5

     CAMPO MINADO

   0 1 2 3 4
0  # # # # #
1  # # # # #
2  # # # # #
3  # # # # #
4  # # # # #

Digite a linha: 2
Digite a coluna: 3
```

## Limitações conhecidas

- O programa não possui sistema de bandeiras;
- Entradas não numéricas não são tratadas completamente pelo `scanf()`;
- A interface funciona somente no terminal;
- As matrizes utilizam tamanho máximo estático de `20 x 20`;
- Somente a primeira casa é garantida como segura; as casas vizinhas dela ainda podem conter minas.

## Possíveis melhorias

- Validar entradas com `fgets()` e conversão controlada;
- Adicionar marcação e remoção de bandeiras;
- Criar níveis predefinidos de dificuldade;
- Permitir reiniciar a partida;
- Exibir cores no terminal;
- Agrupar o estado do jogo em uma `struct`;
- Garantir uma região segura ao redor da primeira jogada;
- Implementar uma interface gráfica.

## Conclusão

O projeto apresenta uma aplicação prática da recursividade em um problema conhecido. A expansão automática das casas vazias permite observar o funcionamento das condições de parada, das chamadas recursivas e da pilha durante a execução.

Além da recursividade, o desenvolvimento integrou matrizes, funções, laços, condicionais, validação de posições e geração pseudoaleatória, reunindo diferentes conteúdos da disciplina em uma aplicação interativa.
