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



void escolherDificuldade() // Para escolher o tamanho do campo de a quantidade de minas
{
    do
    {
        printf("Quantidade de linhas (%d a %d): ",MIN_LINHAS, MAX_LINHAS); // Define linhas
        scanf("%d", &linhas);

        printf("Quantidade de colunas (%d a %d): ",MIN_COLUNAS, MAX_COLUNAS); // Define colunas 
        scanf("%d", &colunas);

        if (linhas < 2 || linhas > MAX_LINHAS || // Limita o tamanho do campo 
            colunas < 2 || colunas > MAX_COLUNAS)
        {
            printf("\nTamanho invalido!\n\n");
        }

    } while (linhas < 2 || linhas > MAX_LINHAS ||
             colunas < 2 || colunas > MAX_COLUNAS);


    do
    {
        printf("Quantidade de minas: "); // Para definir a quantidade de minas 
        scanf("%d", &numMinas);

        if (numMinas < 1 || numMinas >= linhas * colunas)
        {
            printf("\nQuantidade de minas invalida!\n");
            printf("Escolha entre 1 e %d minas.\n\n",
                   linhas * colunas - 1);
        }

    } while (numMinas < 1 || numMinas >= linhas * colunas);
}




void inicializarJogo() // Inicializa o jogo. 
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            campo[i][j] = 0;
            aberto[i][j] = 0;
        }
    }
}




void colocarMinas() // Coloca a quantidade de minas escolhida aleatoriamente no campo 
{
    int minasColocadas = 0;

    while (minasColocadas < numMinas)
    {
        int linha = rand() % linhas; // Aleatorio
        int coluna = rand() % colunas; // Aleatorio

        if (campo[linha][coluna] != -1)
        {
            campo[linha][coluna] = -1;
            minasColocadas++; // Adiciona a uma mina colocada ate chegar ao numero escolhido
        }
    }
}



int posicaoValida(int linha, int coluna)// Verifica se uma posição está dentro do campo
{
    return linha >= 0 &&
           linha < linhas &&
           coluna >= 0 &&
           coluna < colunas;
}



int contarMinasAoRedor(int linha, int coluna)// Conta quantas minas existem ao redor
{
    int quantidade = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++) 
        {
            int novaLinha = linha + i;
            int novaColuna = coluna + j;

            if (posicaoValida(novaLinha, novaColuna)) // Certifica que o lugar esta vago para mina
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



void calcularNumeros() // Calcula os números do campo 
{
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



void abrirCasa(int linha, int coluna) // Funcao recursiva**
{
    if (!posicaoValida(linha, coluna))// Verifica se a posição escolhida é valida
    {                                // Caso seja válida, empilha a posição desejada
        return;
    }

    if (aberto[linha][coluna] == 1)// Verifica se a posicao ja foi escolhida(Se ja está na pilha).
    {
        return;
    }

    aberto[linha][coluna] = 1; // Monstra que a posicao ja está selecionada 

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




void mostrarCampo(int mostrarMinas) // Mostra o campo gerado após o jogo finalizado 
{
    printf("\n     CAMPO MINADO\n\n");

    printf("   ");

    for (int j = 0; j < colunas; j++) // mostra todas as colucas
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
                printf("* ");
            }
            else if (aberto[i][j] == 0)
            {
                printf("# "); // local sem mina 
            }
            else if (campo[i][j] == 0)
            {
                printf("  ");
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




int verificarVitoria() // Verifica vitória
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (campo[i][j] != -1 && aberto[i][j] == 0)
            {
                return 0;
            }
        }
    }

    return 1;
}




int main() // Função principal
{
    int linha;
    int coluna;
    int perdeu = 0;

    srand(time(NULL)); // Gerar Aleatorio

    escolherDificuldade();
    inicializarJogo();
    colocarMinas();
    calcularNumeros();

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