#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_LINHAS 2
#define MIN_COLUNAS 2
#define MAX_LINHAS 20
#define MAX_COLUNAS 20

int linhas;
int colunas;
int numMinas;
int campo[MAX_LINHAS][MAX_COLUNAS];
int aberto[MAX_LINHAS][MAX_COLUNAS];

void escolherDificuldade() { // Para escolher o tamanho do campo e a quantidade de minas
    do
    {
        printf("Quantidade de linhas (%d a %d): ", MIN_LINHAS, MAX_LINHAS);
        scanf("%d", &linhas);

        printf("Quantidade de colunas (%d a %d): ", MIN_COLUNAS, MAX_COLUNAS);
        scanf("%d", &colunas);

        if (linhas < MIN_LINHAS || linhas > MAX_LINHAS ||
            colunas < MIN_COLUNAS || colunas > MAX_COLUNAS)
        {
            printf("\nTamanho invalido!\n\n");
        }

    } while (linhas < MIN_LINHAS || linhas > MAX_LINHAS ||
             colunas < MIN_COLUNAS || colunas > MAX_COLUNAS);

    do
    {
        printf("Quantidade de minas: ");
        scanf("%d", &numMinas);

        if (numMinas < 1 || numMinas >= linhas * colunas)
        {
            printf("\nQuantidade de minas invalida!\n");
            printf("Escolha entre 1 e %d minas.\n\n",
                   linhas * colunas - 1);
        }

    } while (numMinas < 1 || numMinas >= linhas * colunas);
}

void inicializarJogo() { // Inicializa o jogo; cria o campo
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            campo[i][j] = 0;
            aberto[i][j] = 0;
        }
    }
}

void colocarMinas(int linhaSegura, int colunaSegura) { // Função que ira gerar as minas
    int minasColocadas = 0;

    while (minasColocadas < numMinas)
    {
        int linha = rand() % linhas; // Geração de posicao aleatoria
         int coluna = rand() % colunas; // Geração de posicao aleatoria

        // Nao permite colocar mina na primeira casa escolhida
        if (linha == linhaSegura && coluna == colunaSegura)
        {
            continue;
        }

        // Evita colocar duas minas na mesma posicao
        if (campo[linha][coluna] != -1)
        {
            campo[linha][coluna] = -1;
            minasColocadas++;
        }
    }
}

int posicaoValida(int linha, int coluna) { // Verifica se uma posição está dentro do campo
    return linha >= 0 &&
           linha < linhas &&
           coluna >= 0 &&
           coluna < colunas;
}

int contarMinasAoRedor(int linha, int coluna) { // Conta quantas minas existem ao redor
    int quantidade = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++) 
        {
            int novaLinha = linha + i;
            int novaColuna = coluna + j;

            if (posicaoValida(novaLinha, novaColuna)) // Verifica se a posicao vizinha esta dentro do campo
            {
                if (campo[novaLinha][novaColuna] == -1)
                {
                    quantidade++;
                }
            }
        }
    }

    return quantidade;
}

void calcularNumeros() { // Calcula os números do campo
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (campo[i][j] != -1)
            {
                campo[i][j] = contarMinasAoRedor(i, j);
            }
        }
    }
}



void abrirCasa(int linha, int coluna) { // Funcao recursiva
    if (!posicaoValida(linha, coluna)) // Verifica se a posição escolhida é valida
    {                                // Caso seja válida, empilha a posição desejada
        return;
    }

    if (aberto[linha][coluna] == 1)// Verifica se a posicao ja foi escolhida(Se ja está na pilha).
    {
        return;
    }

    aberto[linha][coluna] = 1; // Mostra que a posicao ja está selecionada 

    if (campo[linha][coluna] != 0)
    {
        return;
    }

    for (int i = -1; i <= 1; i++) // Caso contrario, está disponivel para escolher 
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i != 0 || j != 0)
            {
                abrirCasa(linha + i, coluna + j);
            }
        }
    }
}

void mostrarCampo(int mostrarMinas)  { // Mostra o campo gerado após o jogo finalizado
    printf("\n     CAMPO MINADO\n\n");

    printf("   ");

    for (int j = 0; j < colunas; j++) // mostra todas as colunas
    {
        printf("%d ", j);
    }

    printf("\n");

    for (int i = 0; i < linhas; i++) // mostra todas as linhas 
    {
        printf("%d  ", i);

        for (int j = 0; j < colunas; j++)
        {
            if (mostrarMinas && campo[i][j] == -1) // local com mina 
            {
                printf("* "); // local com mina
            }
            else if (aberto[i][j] == 0)
            {
                printf("# "); // local sem mina 
            }
            else if (campo[i][j] == 0)
            {
                printf("  "); // local aberto 
            }
            else
            {
                printf("%d ", campo[i][j]);
            }
        }

        printf("\n");
    }

    printf("\n");
}

int verificarVitoria() { // Verifica vitória
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        { // Verifica se existe alguma casa sem mina que ainda nao foi aberta
            if (campo[i][j] != -1 && aberto[i][j] == 0) 
            {
                return 0;
            }
        }
    }

    return 1;
}

int main() { // Funcao principal
    int linha;
    int coluna;
    int perdeu = 0;
    int primeiraJogada = 1;

    srand(time(NULL)); // Gera numeros aleatorios

    escolherDificuldade();
    inicializarJogo();

    while (1)
    {
        mostrarCampo(0);

        printf("Digite a linha: ");
        scanf("%d", &linha);

        printf("Digite a coluna: ");
        scanf("%d", &coluna);

        if (!posicaoValida(linha, coluna))
        {
            printf("\nPosicao invalida!\n");
            continue;
        }

        // As minas sao geradas somente depois da primeira jogada valida
        if (primeiraJogada)
        {
            colocarMinas(linha, coluna);
            calcularNumeros();
            primeiraJogada = 0;
        }

        if (campo[linha][coluna] == -1)
        {
            perdeu = 1;
            break;
        }

        abrirCasa(linha, coluna);

        if (verificarVitoria())
        {
            break;
        }
    }

    mostrarCampo(1);

    if (perdeu)
    {
        printf("       BOOOOM!!!\n");
        printf("   VOCE PISOU EM UMA MINA\n");
    }
    else
    {
        printf("       VOCE VENCEU!\n");
    }

    return 0;
}