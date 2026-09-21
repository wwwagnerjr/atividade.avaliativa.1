# Campo Minado Recursivo em C

Projeto desenvolvido para a disciplina de **Estrutura de Dados**, do curso de **Tecnologia em Análise e Desenvolvimento de Sistemas da Universidade Tecnológica Federal do Paraná — UTFPR, Câmpus Cornélio Procópio**, no segundo semestre de 2026, sob orientação do **Prof. Dr. Clayton Kossoski**.

## Sobre o projeto

O projeto consiste no desenvolvimento de uma versão do jogo **Campo Minado**, executada diretamente pelo terminal e implementada em linguagem C.

O objetivo do jogador é abrir todas as casas seguras do tabuleiro sem selecionar uma posição que contenha uma mina. As casas abertas apresentam a quantidade de minas existentes ao seu redor, permitindo que o jogador utilize essas informações para escolher suas próximas jogadas.

Uma das principais características do projeto é a utilização de **recursividade** para realizar a abertura automática das regiões vazias do campo.

Quando o jogador seleciona uma casa que não possui minas ao redor, o programa verifica automaticamente as posições vizinhas e continua realizando novas chamadas da função de abertura enquanto encontrar outras casas vazias.

Dessa forma, o funcionamento do Campo Minado permite visualizar na prática conceitos estudados na disciplina, como:

* chamadas recursivas;
* condições de parada;
* pilha de chamadas;
* matrizes;
* controle de posições visitadas;
* verificação de limites;
* organização do programa através de funções.

---

## Integrantes

| **Nome**                           | **Registro Acadêmico (RA)** |
| ---------------------------------- | --------------------------: |
| João Victor Queiroz de Lima        |                     2051524 |
| Leonardo Di Camargo Rodrigues      |                     2809028 |
| Luiz Gustavo Mendes Lemes          |                     2618028 |
| Micael Marinho Souza               |                     2819457 |
| Wagner Lourenço de Oliveira Junior |                     2819473 |

---

## Objetivo

O principal objetivo do projeto é aplicar conceitos de **recursividade e estruturas de dados** através da implementação de um jogo funcional.

Além da recursividade, o desenvolvimento também trabalha com matrizes bidimensionais para representar o campo, funções para dividir as responsabilidades do programa e estruturas de repetição e decisão para controlar as diferentes etapas do jogo.

A implementação permite observar de forma prática como uma função recursiva pode percorrer posições relacionadas dentro de uma matriz, interrompendo sua execução quando determinadas condições são encontradas.

---

## Funcionalidades

O programa possui as seguintes funcionalidades:

* escolha personalizada da quantidade de linhas;
* escolha personalizada da quantidade de colunas;
* tabuleiro configurável entre **2 × 2 e 20 × 20**;
* escolha da quantidade de minas;
* validação da dimensão do campo;
* validação da quantidade de minas;
* distribuição pseudoaleatória das minas;
* prevenção de minas duplicadas na mesma posição;
* cálculo da quantidade de minas nas oito posições vizinhas;
* abertura automática de regiões vazias utilizando recursividade;
* controle das casas que já foram abertas;
* validação das coordenadas informadas pelo jogador;
* identificação da condição de vitória;
* identificação da condição de derrota;
* exibição de todas as minas ao final da partida.

---

## Tecnologias utilizadas

O projeto foi desenvolvido utilizando apenas a linguagem **C** e bibliotecas pertencentes à biblioteca padrão da linguagem.

| Biblioteca | Utilização                                                        |
| ---------- | ----------------------------------------------------------------- |
| `stdio.h`  | Entrada e saída de dados através de `printf()` e `scanf()`        |
| `stdlib.h` | Utilização das funções `rand()` e `srand()`                       |
| `time.h`   | Utilização de `time()` para inicializar o gerador pseudoaleatório |

Não é necessária a instalação de nenhuma biblioteca externa para executar o programa.

---

## Configuração do campo

O programa permite que o próprio jogador determine o tamanho do tabuleiro antes de iniciar a partida.

Os limites definidos no código são:

```c
#define MIN_LINHAS 2
#define MIN_COLUNAS 2
#define MAX_LINHAS 20
#define MAX_COLUNAS 20
```

Dessa forma, é possível utilizar desde um pequeno campo de:

```text
2 × 2
```

até um campo de:

```text
20 × 20
```

A quantidade de minas também é definida pelo jogador.

O programa exige que exista pelo menos uma mina e uma casa segura. Portanto, a quantidade máxima permitida corresponde ao total de posições do tabuleiro menos uma.

Por exemplo, em um campo `5 × 5`, existem 25 posições. Nesse caso, o jogador poderá escolher entre **1 e 24 minas**.

---

## Como compilar e executar

É necessário possuir um compilador C instalado no computador, como o **GCC**.

Abra o terminal na pasta em que o código-fonte está localizado.

### Windows — PowerShell

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o campo_minado.exe
.\campo_minado.exe
```

### Linux

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o campo_minado
./campo_minado
```

Também é possível utilizar uma IDE compatível com C, como Visual Studio Code, Code::Blocks ou outras ferramentas utilizadas durante as aulas.

---

## Como jogar

Ao executar o programa, inicialmente será solicitado o tamanho desejado para o campo.

Exemplo:

```text
Quantidade de linhas (2 a 20): 5
Quantidade de colunas (2 a 20): 5
Quantidade de minas: 5
```

Após essas informações, o Campo Minado será gerado.

Exemplo de um tabuleiro `5 × 5`:

```text
     CAMPO MINADO

   0 1 2 3 4
0  # # # # #
1  # # # # #
2  # # # # #
3  # # # # #
4  # # # # #
```

O jogador deverá informar primeiro a linha e depois a coluna da posição que deseja abrir.

```text
Digite a linha: 2
Digite a coluna: 3
```

Nesse exemplo, será selecionada a posição localizada na linha `2` e coluna `3`.

Como as minas são distribuídas aleatoriamente a cada execução, o resultado da escolha poderá ser diferente em cada partida.

---

## Símbolos utilizados

Durante a partida, alguns símbolos são utilizados para representar o estado das casas.

| Símbolo          | Significado                                          |
| ---------------- | ---------------------------------------------------- |
| `#`              | Casa ainda fechada                                   |
| Espaço em branco | Casa aberta sem minas ao redor                       |
| `1` a `8`        | Quantidade de minas existentes nas posições vizinhas |
| `*`              | Mina revelada ao final da partida                    |

Os números levam em consideração até oito posições vizinhas:

```text
↖ ↑ ↗
← X →
↙ ↓ ↘
```

A posição `X` representa a casa que está sendo analisada.

---

# Organização do código

Para facilitar a organização e a leitura do programa, as diferentes responsabilidades foram divididas em funções.

## `escolherDificuldade()`

Responsável por receber:

* quantidade de linhas;
* quantidade de colunas;
* quantidade de minas.

A função também verifica se os valores estão dentro dos limites permitidos.

Caso sejam informados valores inválidos, o programa solicita novamente os dados.

---

## `inicializarJogo()`

Inicializa as duas matrizes utilizadas pelo programa:

```c
campo
aberto
```

Todas as posições começam com valor `0`.

---

## `colocarMinas()`

Distribui as minas aleatoriamente pelo campo.

As coordenadas são geradas utilizando:

```c
rand() % linhas
rand() % colunas
```

Uma mina é representada internamente pelo valor:

```c
-1
```

Antes de adicionar uma nova mina, o programa verifica se já existe outra naquela posição.

Isso impede que duas minas sejam contabilizadas na mesma casa.

---

## `posicaoValida()`

Verifica se uma determinada coordenada está dentro dos limites atuais do campo.

```c
int posicaoValida(int linha, int coluna)
```

A função retorna verdadeiro somente quando:

```text
0 <= linha < quantidade de linhas
0 <= coluna < quantidade de colunas
```

Essa verificação é importante tanto para as jogadas realizadas pelo usuário quanto para o funcionamento da recursividade.

---

## `contarMinasAoRedor()`

Analisa as posições próximas de cada casa e calcula quantas minas existem ao seu redor.

São consideradas as posições:

* acima;
* abaixo;
* esquerda;
* direita;
* diagonais.

Cada posição é verificada antes de acessar a matriz para evitar acessos fora dos seus limites.

---

## `calcularNumeros()`

Percorre todas as casas do tabuleiro.

Caso uma posição não contenha uma mina, é utilizada a função `contarMinasAoRedor()` para determinar o número que deverá ser armazenado naquela posição.

Dessa forma, internamente uma casa pode possuir:

```text
-1 = mina
 0 = nenhuma mina ao redor
 1 a 8 = quantidade de minas ao redor
```

---

## `mostrarCampo()`

Responsável por apresentar o tabuleiro no terminal.

Durante a partida, somente as casas já abertas são apresentadas.

As demais permanecem representadas por:

```text
#
```

Quando a partida termina, a função também pode apresentar as posições onde estavam as minas.

---

## `verificarVitoria()`

Percorre o campo procurando alguma posição segura que ainda não tenha sido aberta.

Se encontrar uma casa segura fechada, a partida deve continuar.

Caso todas as posições que não possuem minas tenham sido abertas, o jogador vence.

---

## `main()`

A função `main()` controla o fluxo principal da partida.

A sequência inicial é:

```text
Inicializar o gerador aleatório
          ↓
Escolher dimensões e minas
          ↓
Inicializar matrizes
          ↓
Distribuir minas
          ↓
Calcular números do campo
          ↓
Iniciar as jogadas
```

Durante cada jogada:

```text
Exibir campo
      ↓
Receber linha
      ↓
Receber coluna
      ↓
Validar posição
      ↓
Verificar se existe uma mina
      ↓
Abrir a posição
      ↓
Verificar vitória
```

---

# Aplicação da recursividade

A principal aplicação de recursividade do projeto está na função:

```c
void abrirCasa(int linha, int coluna)
```

Ela é responsável por abrir a posição selecionada e, quando necessário, continuar a abertura automaticamente pelas posições vizinhas.

Esse comportamento é semelhante ao algoritmo conhecido como **Flood Fill**, utilizado para percorrer regiões conectadas.

---

## Condições de parada

Para que uma função recursiva funcione corretamente, é necessário possuir condições que interrompam novas chamadas.

No projeto existem três verificações principais.

### 1. Posição fora do campo

```c
if (!posicaoValida(linha, coluna))
{
    return;
}
```

Essa condição impede que a recursão tente acessar uma posição inexistente da matriz.

---

### 2. Casa já aberta

```c
if (aberto[linha][coluna] == 1)
{
    return;
}
```

Uma mesma posição pode ser alcançada através de diferentes casas vizinhas.

Por isso, o programa verifica se ela já foi aberta antes de continuar.

Essa verificação é importante para evitar que a recursividade fique visitando repetidamente as mesmas posições.

---

### 3. Casa com número

Depois que uma casa válida é marcada como aberta:

```c
aberto[linha][coluna] = 1;
```

o programa verifica seu valor.

```c
if (campo[linha][coluna] != 0)
{
    return;
}
```

Caso exista pelo menos uma mina ao redor, a casa é apresentada ao jogador, mas a expansão recursiva não continua a partir dela.

---

# Expansão recursiva

Quando uma casa possui valor `0`, significa que não existem minas diretamente ao seu redor.

Nesse caso, o programa percorre as oito posições vizinhas:

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

A condição:

```c
i != 0 || j != 0
```

serve para evitar que a função faça uma chamada para a própria posição que está sendo processada.

Cada posição vizinha executa novamente a mesma função e passa pelas condições de parada.

Assim:

* casas vazias continuam a expansão;
* casas numeradas são abertas;
* casas já abertas são ignoradas;
* posições fora do campo são ignoradas.

---

# Pilha de chamadas

Durante uma chamada recursiva, cada execução da função `abrirCasa()` fica temporariamente armazenada na **pilha de chamadas**.

Por exemplo:

```text
abrirCasa(2, 2)
    └── abrirCasa(1, 1)
            └── abrirCasa(0, 0)
```

Quando a chamada mais interna termina, o programa retorna para a chamada anterior e continua verificando as outras posições vizinhas.

Um detalhe importante da implementação é que uma posição é marcada como aberta **antes** da chamada das casas vizinhas:

```c
aberto[linha][coluna] = 1;
```

Com isso, caso outra chamada recursiva encontre novamente a mesma posição, ela será imediatamente interrompida.

Isso evita ciclos durante a expansão.

---

# Uso das matrizes

O programa utiliza duas matrizes globais de tamanho máximo:

```c
int campo[MAX_LINHAS][MAX_COLUNAS];
int aberto[MAX_LINHAS][MAX_COLUNAS];
```

Cada uma possui uma responsabilidade diferente.

| Matriz   | Responsabilidade                                                        |
| -------- | ----------------------------------------------------------------------- |
| `campo`  | Armazena minas e números correspondentes à quantidade de minas próximas |
| `aberto` | Controla quais posições já foram abertas pelo jogador                   |

A matriz `campo` representa os dados internos do jogo.

A matriz `aberto` controla aquilo que já pode ser apresentado ao jogador.

Essa separação permite esconder o conteúdo das casas enquanto elas ainda não foram selecionadas.

---

# Geração pseudoaleatória das minas

Antes de gerar as posições das minas, o programa utiliza:

```c
srand(time(NULL));
```

A função `time(NULL)` fornece um valor relacionado ao horário atual.

Esse valor é utilizado como semente para:

```c
srand()
```

Posteriormente, `rand()` é utilizado para escolher as posições das minas.

Isso faz com que o campo normalmente apresente uma distribuição diferente a cada nova execução.

---

# Condições de vitória e derrota

## Derrota

Após o jogador informar uma posição, o programa verifica:

```c
if (campo[linha][coluna] == -1)
```

Caso a posição contenha uma mina, a partida é encerrada.

O programa apresenta:

```text
BOOOOM!!!
VOCE PISOU EM UMA MINA
```

---

## Vitória

Depois de uma jogada segura, a função:

```c
verificarVitoria()
```

analisa todo o tabuleiro.

Caso não exista nenhuma casa segura ainda fechada, a partida termina com:

```text
VOCE VENCEU!
```

---

# Conceitos trabalhados

Durante o desenvolvimento deste projeto foram utilizados diferentes conceitos da linguagem C e da disciplina de Estrutura de Dados:

* recursividade;
* pilha de chamadas;
* matrizes bidimensionais;
* controle de estados;
* funções;
* passagem de parâmetros;
* estruturas condicionais;
* estruturas de repetição;
* validação de índices;
* geração pseudoaleatória;
* decomposição de um problema em funções menores;
* condições de parada;
* exploração de posições vizinhas.

---

# Complexidade da abertura recursiva

Considerando um tabuleiro com `L` linhas e `C` colunas, no pior caso a expansão pode visitar praticamente todas as posições seguras.

Como cada posição é marcada como aberta e não precisa ser processada novamente, a complexidade da expansão pode ser considerada aproximadamente:

```text
O(L × C)
```

Cada posição verifica no máximo oito casas vizinhas, o que representa uma quantidade constante de operações para cada posição.

A utilização da pilha de chamadas também pode atingir, no pior cenário:

```text
O(L × C)
```

dependendo da disposição do campo e da sequência das chamadas recursivas.

Como o projeto limita o campo a no máximo `20 × 20`, o tamanho máximo trabalhado é de 400 posições.

---

# Limitações atuais

A versão atual foi desenvolvida com foco principalmente na aplicação dos conceitos estudados em sala de aula.

Algumas funcionalidades existentes em versões tradicionais do Campo Minado ainda não foram implementadas:

* não existe sistema de bandeiras para marcar possíveis minas;
* a primeira jogada não possui proteção contra minas;
* não existe opção de reiniciar diretamente pelo menu;
* para iniciar uma nova partida é necessário executar o programa novamente;
* o programa trabalha apenas pelo terminal;
* a entrada realizada através de `scanf()` pressupõe que o usuário informe valores numéricos inteiros.

Também é possível que duas partidas iniciadas no mesmo segundo apresentem uma distribuição semelhante das minas, pois a semente pseudoaleatória utiliza:

```c
time(NULL)
```

Esses pontos podem ser utilizados como possibilidades de melhoria em futuras versões.

---

# Possíveis melhorias futuras

Algumas funcionalidades que poderiam ser adicionadas futuramente são:

* sistema de bandeiras;
* proteção da primeira jogada;
* opção de iniciar uma nova partida sem fechar o programa;
* níveis de dificuldade predefinidos;
* contador de minas;
* contador de jogadas;
* cronômetro;
* tratamento de entradas inválidas com letras ou símbolos;
* interface gráfica;
* organização do código em diferentes arquivos `.c` e `.h`.

---

## Considerações finais

O desenvolvimento do Campo Minado possibilitou aplicar diferentes conteúdos estudados durante a disciplina em um programa interativo.

A recursividade teve papel importante na implementação, principalmente na abertura automática das regiões vazias do tabuleiro. A utilização das condições de parada e da matriz responsável por controlar as posições já abertas permitiu evitar chamadas repetidas e tornar a expansão finita.

Além disso, o projeto permitiu trabalhar de forma conjunta conceitos como matrizes, funções, estruturas de repetição, condicionais, geração pseudoaleatória e validação de posições.

Com isso, o trabalho apresenta uma aplicação prática da recursividade em um problema conhecido, tornando mais fácil observar o funcionamento das chamadas recursivas e da pilha durante a execução do programa.

---

## Instituição

**Universidade Tecnológica Federal do Paraná — UTFPR**
**Câmpus Cornélio Procópio**

Curso: **Tecnologia em Análise e Desenvolvimento de Sistemas**
Disciplina: **Estrutura de Dados**
Professor: **Prof. Dr. Clayton Kossoski**
Período: **2º semestre de 2026**
