# Campo Minado Recursivo em C

Projeto desenvolvido para a disciplina de **Estrutura de Dados**, do curso de **Tecnologia em Análise e Desenvolvimento de Sistemas da Universidade Tecnológica Federal do Paraná — Câmpus Cornélio Procópio**, no segundo semestre de 2026, sob orientação do **Prof. Dr. Clayton Kossoski**.

## Sobre o projeto

O projeto consiste em um jogo de Campo Minado executado no terminal e implementado em C puro. O jogador deve abrir todas as casas seguras do tabuleiro sem selecionar uma mina, utilizando os números revelados para orientar suas próximas escolhas.

Escolhemos o Campo Minado porque a abertura automática de regiões vazias permite aplicar a recursividade de maneira direta. Ao selecionar uma casa sem minas ao redor, a mesma operação de abertura é repetida para suas vizinhas, até alcançar os limites da região. Dessa forma, o jogo relaciona os conceitos de caso base, chamada recursiva e pilha de chamadas a uma funcionalidade que pode ser observada durante a partida.

## Integrantes

| Nome | Registro acadêmico (RA) |
| --- | --- |
| João Victor Queiroz de Lima | 2051524 |
| Leonardo Di Camargo Rodrigues | 2809028 |
| Luiz Gustavo Mendes Lemes | 2618028 |
| Micael Marinho Souza | 2819457 |
| Wagner Lourenço de Oliveira Junior | 2819473 |

## Objetivo

Aplicar a recursividade na abertura de casas de um Campo Minado, utilizando matrizes para representar o tabuleiro e funções para organizar as etapas do jogo. O trabalho também envolve a verificação dos limites da matriz, o controle das casas já abertas e a identificação das condições de vitória e derrota.

## Funcionalidades

- Tabuleiro de **5 × 5**, com **7 minas** e **18 casas seguras**.
- Distribuição pseudoaleatória das minas, sem repetição de posições.
- Contagem de minas nas oito posições vizinhas de cada casa, incluindo diagonais.
- Abertura recursiva de regiões sem minas próximas.
- Verificação de coordenadas fora dos limites do tabuleiro.
- Identificação de vitória ao abrir todas as casas seguras.
- Encerramento da partida ao selecionar uma mina.
- Exibição das minas ao final do jogo.

## Tecnologias utilizadas

O programa utiliza a linguagem **C** e apenas bibliotecas padrão:

| Biblioteca | Utilização |
| --- | --- |
| `stdio.h` | Entrada e saída de dados com `scanf` e `printf` |
| `stdlib.h` | Geração de números pseudoaleatórios com `rand` e `srand` |
| `time.h` | Obtenção do horário para inicializar a sequência pseudoaleatória |

## Estrutura do projeto

```text
campo-minado-recursivo/
├── main.c       # Código-fonte comentado do jogo.
├── README.md    # Documentação do projeto.
└── .gitignore   # Exclusão de arquivos gerados na compilação.
```

## Como compilar e executar

É necessário ter um compilador de C instalado, como GCC, e abrir o terminal na pasta que contém o arquivo `main.c`. Os comandos abaixo utilizam o padrão **C11**.

### Windows — PowerShell

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o campo_minado.exe
.\campo_minado.exe
```

### Linux ou macOS

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o campo_minado
./campo_minado
```

Também é possível utilizar Clang, substituindo `gcc` por `clang`. Em uma IDE, basta criar um projeto de console em C e adicionar o arquivo `main.c`. Não são necessárias bibliotecas externas.

## Como jogar

Ao iniciar a partida, o programa apresenta o tabuleiro com todas as casas fechadas. As linhas e as colunas são identificadas por números de **0 a 4**.

```text
     CAMPO MINADO

   0 1 2 3 4
0  # # # # #
1  # # # # #
2  # # # # #
3  # # # # #
4  # # # # #
```

1. Digite o número da linha e pressione **Enter**.
2. Digite o número da coluna e pressione **Enter**.
3. Observe as casas reveladas e escolha a próxima posição.
4. Continue até abrir todas as casas seguras ou encontrar uma mina.

Por exemplo, a linha `2` e a coluna `3` correspondem à quarta casa da terceira linha. Como as minas são sorteadas a cada inicialização, o resultado dessa escolha depende da partida.

### Símbolos do tabuleiro

| Símbolo | Significado |
| --- | --- |
| `#` | Casa fechada |
| Espaço em branco | Casa aberta sem minas ao redor |
| Número de `1` a `8` | Quantidade de minas nas casas vizinhas |
| `*` | Mina revelada no encerramento |

### Regras

Uma casa numerada informa quantas minas existem ao seu redor, considerando as direções horizontal, vertical e diagonal. Ao abrir uma casa de valor zero, o programa revela automaticamente a região vazia conectada e as casas numeradas que a delimitam.

Selecionar uma casa já aberta não altera o tabuleiro. Coordenadas inteiras fora do intervalo de 0 a 4 são rejeitadas, e o jogador pode tentar novamente.

A vitória acontece quando todas as **18 casas seguras** estão abertas. Selecionar uma mina encerra a partida em derrota. Nos dois casos, as minas são exibidas; casas seguras ainda fechadas permanecem representadas por `#`.

Para jogar novamente, execute o programa outra vez. Para interromper uma partida, utilize `Ctrl+C` no terminal.

## Organização do código

### Representação do tabuleiro

O jogo utiliza duas matrizes globais:

| Matriz | Responsabilidade |
| --- | --- |
| `campo[LINHAS][COLUNAS]` | Armazena `-1` para minas e valores de `0` a `8` para a quantidade de minas ao redor das casas seguras |
| `aberto[LINHAS][COLUNAS]` | Armazena `0` para casas fechadas e `1` para casas abertas |

Essa separação permite controlar o que o jogador visualiza sem modificar o conteúdo do campo. A matriz `aberto` também impede que uma posição seja processada repetidamente durante a expansão recursiva.

As constantes `LINHAS`, `COLUNAS` e `NUM_MINAS`, declaradas em um `enum`, definem a configuração do tabuleiro.

### Principais funções

| Função | Responsabilidade |
| --- | --- |
| `inicializarJogo()` | Zerar as matrizes antes da partida |
| `colocarMinas()` | Distribuir as minas em posições distintas |
| `posicaoValida()` | Verificar os limites do tabuleiro |
| `contarMinasAoRedor()` | Contar minas nas posições vizinhas válidas |
| `calcularNumeros()` | Preencher os valores das casas seguras |
| `abrirCasa()` | Abrir uma casa e expandir recursivamente as regiões de zeros |
| `mostrarCampo()` | Exibir o tabuleiro conforme o estado da partida |
| `verificarVitoria()` | Verificar se todas as casas seguras foram abertas |
| `main()` | Controlar a inicialização, as jogadas e o encerramento |

## Aplicação da recursividade

A recursividade está concentrada na função `abrirCasa(int linha, int coluna)`. Ela utiliza uma técnica de preenchimento de região conhecida como **flood fill**, na qual a abertura de uma casa pode iniciar a abertura de suas vizinhas.

### Condições de parada

Cada chamada verifica três situações:

1. **Posição fora do tabuleiro:** retorna antes de acessar as matrizes.
2. **Casa já aberta:** retorna para evitar uma nova exploração da mesma posição.
3. **Casa com valor diferente de zero:** abre a casa e encerra a expansão daquela chamada.

Durante uma jogada, a verificação de mina ocorre em `main`, antes da chamada de `abrirCasa`. Assim, a função é acionada pelo jogador somente para posições seguras. Uma casa zero também não possui minas entre seus vizinhos.

### Expansão recursiva

Após verificar a posição, a função marca a casa como aberta:

```c
aberto[linha][coluna] = 1;
```

Se o valor da casa for zero, percorre as oito posições ao redor e chama a si mesma para cada uma delas:

```c
for (int i = -1; i <= 1; i++)
{
    for (int j = -1; j <= 1; j++)
    {
        if (i != 0 || j != 0)
        {
            abrirCasa(linha + i, coluna + j);
        }
    }
}
```

A condição `i != 0 || j != 0` exclui a própria casa da lista de vizinhos. Cada nova chamada repete as verificações: casas de valor zero continuam a expansão, enquanto casas numeradas são reveladas e interrompem a expansão naquele ponto.

### Pilha de chamadas e término

Ao realizar uma chamada recursiva, a função atual aguarda o processamento do vizinho. Suas coordenadas e o estado dos laços ficam preservados na pilha de chamadas. Quando o vizinho termina, a chamada anterior retoma a execução e segue para a próxima posição.

A casa é marcada como aberta **antes** da visita aos vizinhos. Dessa forma, se outra chamada alcançar a mesma posição, encontrará uma condição de parada. Isso evita ciclos e garante o término da expansão em um tabuleiro finito. As casas reveladas permanecem abertas após o retorno das chamadas.

Considerando um tabuleiro com `L` linhas e `C` colunas, a expansão tem custo de tempo `O(L × C)` no pior caso, pois cada casa é processada uma vez e possui no máximo oito vizinhos. A pilha de chamadas pode ocupar `O(L × C)` no pior caso.

## Fluxo de execução

O programa inicializa o gerador pseudoaleatório, prepara as matrizes, distribui as minas e calcula os números das casas seguras. Em seguida, exibe o tabuleiro e recebe as coordenadas de cada jogada.

Após validar a posição, verifica se existe uma mina. Caso a casa seja segura, executa a abertura e verifica se todas as casas sem minas já foram reveladas. Esse processo se repete até a vitória ou a derrota, quando o campo é exibido com as minas visíveis.

## Limitações atuais

A versão atual utiliza um tabuleiro fixo e não possui marcação de minas com bandeiras nem proteção para a primeira jogada. Como a inicialização do sorteio utiliza `time(NULL)`, partidas iniciadas no mesmo segundo podem apresentar a mesma disposição de minas.

A entrada de coordenadas espera números inteiros. O retorno de `scanf` ainda não é verificado, portanto letras, símbolos e fim de entrada não são tratados adequadamente e podem causar comportamento incorreto. Durante o uso, devem ser informados apenas números inteiros, preferencialmente entre 0 e 4.
