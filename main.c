/*
 * CAMPO MINADO RECURSIVO
 * Estrutura de Dados - ADS - UTFPR Cornélio Procópio - 2026/2
 * Professor: Dr. Clayton Kossoski
 *
 * Integrantes:
 * João Victor Queiroz de Lima           - RA 2051524
 * Micael Marinho Souza                  - RA 2819457
 * Wagner Lourenço de Oliveira Junior    - RA 2819473
 * Leonardo Di Camargo Rodrigues         - RA 2809028
 * Luiz Gustavo Mendes Lemes             - RA 2618028
 *
 * Objetivo: abrir todas as casas sem minas de um campo 5 x 5.
 * A função abrirCasa usa recursividade para expandir regiões de zeros
 * e revelar os números que delimitam essas regiões (flood fill).
 *
 * Esta versão acrescenta documentação ao código fornecido pela equipe,
 * preservando suas instruções e seu comportamento. Consulte o README
 * para compilar, jogar e compreender as limitações da entrada com scanf.
 */

/* stdio.h: printf e scanf; stdlib.h: rand e srand; time.h: time. */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Estas três variáveis globais estão presentes no código original,
 * mas não são utilizadas. O tamanho e a quantidade de minas são
 * definidos pelas constantes LINHAS, COLUNAS e NUM_MINAS abaixo. */
int linhas;
int colunas;
int numMinas;

/* Constantes inteiras: 25 casas no total, sendo 7 minas e 18 seguras.
 * Para o sorteio terminar, NUM_MINAS não pode superar LINHAS * COLUNAS.
 * Mantenha dimensões positivas e ao menos uma casa segura. */
enum {
    LINHAS = 5,
    COLUNAS = 5,
    NUM_MINAS = 7
};

// -1 = mina
//  0 a 8 = quantidade de minas ao redor
int campo[LINHAS][COLUNAS];

// 0 = fechado
// 1 = aberto
int aberto[LINHAS][COLUNAS];


// ---------------------------------------------------------
// Inicializa o jogo
// ---------------------------------------------------------

/* Percorre todas as linhas e colunas para preparar uma nova partida.
 * campo guarda o conteúdo; aberto guarda o que já foi revelado.
 * Zerar as duas matrizes evita reaproveitar dados de uma partida anterior. */
void inicializarJogo()
{
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            campo[i][j] = 0;
            aberto[i][j] = 0;
        }
    }
}


// ---------------------------------------------------------
// Coloca as minas aleatoriamente
// ---------------------------------------------------------

/* Sorteia linha e coluna com rand e usa o resto da divisão para
 * obter índices válidos. A mesma posição pode ser sorteada novamente;
 * nesse caso, ela é ignorada e o contador não aumenta.
 * O processo continua até distribuir sete minas em posições distintas. */
void colocarMinas()
{
    int minasColocadas = 0;

    while (minasColocadas < NUM_MINAS)
    {
        int linha = rand() % LINHAS;
        int coluna = rand() % COLUNAS;

        // Só coloca se ainda não existir uma mina
        if (campo[linha][coluna] != -1)
        {
            campo[linha][coluna] = -1;
            minasColocadas++;
        }
    }
}


// ---------------------------------------------------------
// Verifica se uma posição está dentro do campo
// ---------------------------------------------------------

/* Retorna 1 se os dois índices pertencem à matriz, ou 0 caso contrário.
 * Esta verificação precisa ocorrer antes de acessar uma casa vizinha,
 * pois posições de borda podem produzir índices como -1 ou LINHAS. */
int posicaoValida(int linha, int coluna)
{
    return linha >= 0 &&
           linha < LINHAS &&
           coluna >= 0 &&
           coluna < COLUNAS;
}


// ---------------------------------------------------------
// Conta quantas minas existem ao redor
// ---------------------------------------------------------

/* Os deslocamentos -1, 0 e 1 formam uma região 3 x 3 ao redor da casa,
 * incluindo diagonais. Somente posições válidas são consultadas.
 * Os laços também examinam o centro (deslocamento 0, 0), mas a função
 * é chamada por calcularNumeros apenas para casas sem mina; portanto,
 * o centro não aumenta a contagem nesse uso. */
int contarMinasAoRedor(int linha, int coluna)
{
    int quantidade = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            int novaLinha = linha + i;
            int novaColuna = coluna + j;

            if (posicaoValida(novaLinha, novaColuna))
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


// ---------------------------------------------------------
// Calcula os números do campo
// ---------------------------------------------------------

/* Depois de distribuir as minas, calcula os valores das casas seguras.
 * As minas continuam com -1. As demais recebem um valor de 0 a 8.
 * Alterar números já calculados não prejudica as próximas contagens,
 * porque contarMinasAoRedor procura apenas valores iguais a -1. */
void calcularNumeros()
{
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            if (campo[i][j] != -1)
            {
                campo[i][j] = contarMinasAoRedor(i, j);
            }
        }
    }
}


// ---------------------------------------------------------
// FUNÇÃO RECURSIVA
// Abre uma posição e suas vizinhas quando não há minas perto
// ---------------------------------------------------------

/* NÚCLEO RECURSIVO: abre uma casa e, se ela for zero, visita os vizinhos.
 *
 * 1. Retorna imediatamente se estiver fora do campo.
 * 2. Retorna se a casa já foi aberta, evitando ciclos entre vizinhos.
 * 3. Marca a casa como aberta ANTES de iniciar novas chamadas.
 * 4. Se o conteúdo for diferente de zero, encerra esta expansão.
 * 5. Se for zero, chama abrirCasa para cada um dos oito vizinhos.
 *
 * Cada chamada mantém suas coordenadas e seus laços na pilha. Quando
 * um vizinho retorna, a chamada anterior continua no próximo vizinho.
 * As casas abertas permanecem abertas: não há desfazer de jogadas.
 * A técnica é preenchimento de região (flood fill) por busca recursiva.
 *
 * No fluxo do jogo, main detecta a mina antes de chamar esta função.
 * Uma casa zero também não possui minas vizinhas, por definição.
 * A função isoladamente não impede abrir uma mina: se receber uma,
 * marcará a casa como aberta e retornará no teste de valor não zero. */
void abrirCasa(int linha, int coluna)
{
    // CASO BASE 1:
    // posição está fora do campo
    if (!posicaoValida(linha, coluna))
    {
        return;
    }

    // CASO BASE 2:
    // casa já foi aberta
    if (aberto[linha][coluna] == 1)
    {
        return;
    }

    // Abre a casa
    aberto[linha][coluna] = 1;

    // Um valor diferente de zero encerra a expansão desta chamada.
    if (campo[linha][coluna] != 0)
    {
        return;
    }

    // Se chegou aqui, a casa possui ZERO minas ao redor.
    // Então abre recursivamente todas as casas vizinhas.

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
}


// ---------------------------------------------------------
// Mostra o campo
// ---------------------------------------------------------

/* Os índices impressos vão de 0 a 4 e orientam a escolha do jogador.
 * mostrarMinas = 0 oculta as minas durante a partida.
 * mostrarMinas = 1 revela todas as minas no encerramento.
 * Casas seguras ainda fechadas continuam como # mesmo no final.
 * A impressão não altera o conteúdo nem o estado das matrizes. */
void mostrarCampo(int mostrarMinas)
{
    printf("\n     CAMPO MINADO\n\n");

    printf("   ");

    for (int j = 0; j < COLUNAS; j++)
    {
        printf("%d ", j);
    }

    printf("\n");

    for (int i = 0; i < LINHAS; i++)
    {
        printf("%d  ", i);

        for (int j = 0; j < COLUNAS; j++)
        {
            if (mostrarMinas && campo[i][j] == -1)
            {
                printf("* ");
            }
            else if (aberto[i][j] == 0)
            {
                printf("# ");
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


// ---------------------------------------------------------
// Verifica se o jogador venceu
// ---------------------------------------------------------

/* Basta encontrar uma casa segura fechada para saber que a partida
 * ainda não foi vencida. Só retorna 1 se todas as 18 casas seguras
 * estiverem abertas. Não é preciso abrir nem marcar as sete minas. */
int verificarVitoria()
{
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            // Existe uma casa sem mina que ainda não foi aberta
            if (campo[i][j] != -1 && aberto[i][j] == 0)
            {
                return 0;
            }
        }
    }

    return 1;
}


// ---------------------------------------------------------
// MAIN
// ---------------------------------------------------------

/* Coordena a partida: prepara o tabuleiro, recebe jogadas e verifica
 * derrota ou vitória. O laço principal é iterativo; a recursividade
 * está concentrada em abrirCasa, na expansão das regiões vazias. */
int main()
{
    int linha;
    int coluna;
    int perdeu = 0;

    /* Inicializa a sequência pseudoaleatória com o horário atual.
     * Execuções iniciadas no mesmo segundo podem produzir o mesmo campo.
     * Não existe proteção especial para a primeira jogada. */
    srand(time(NULL));

    inicializarJogo();
    colocarMinas();
    calcularNumeros();

    while (1)
    {
        mostrarCampo(0);

        printf("Digite a linha: ");
        /* Espera um número inteiro. O código original não verifica o
         * retorno de scanf: letras e fim de entrada não são tratados.
         * Para jogar esta versão, forneça somente coordenadas inteiras. */
        scanf("%d", &linha);

        printf("Digite a coluna: ");
        /* A mesma limitação de leitura da linha também vale aqui. */
        scanf("%d", &coluna);

        // Verifica posição inválida
        if (!posicaoValida(linha, coluna))
        {
            printf("\nPosicao invalida!\n");
            continue;
        }

        // Jogador clicou em uma mina
        if (campo[linha][coluna] == -1)
        {
            perdeu = 1;
            break;
        }

        // Abre a posição
        abrirCasa(linha, coluna);

        // Verifica vitória
        if (verificarVitoria())
        {
            break;
        }
    }

    // -----------------------------------------------------
    // Final do jogo
    // -----------------------------------------------------

    /* Após qualquer término normal, revela a localização das minas. */
    mostrarCampo(1);

    if (perdeu)
    {
        printf("=========================\n");
        printf("       BOOOOM!!!\n");
        printf("   VOCE PISOU EM UMA MINA\n");
        printf("=========================\n");
    }
    else
    {
        printf("=========================\n");
        printf("       VOCE VENCEU!\n");
        printf("=========================\n");
    }

    return 0;
}
