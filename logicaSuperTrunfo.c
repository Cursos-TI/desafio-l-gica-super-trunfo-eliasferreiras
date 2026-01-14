#include <stdio.h>
#include <string.h>

// Declaracoes:

typedef struct {
    char nome[40];
    unsigned long int populacao;
    int pontos_turisticos;
    float area, pib, dens_pop, pib_per_capta;
    float poder;
} Carta;

Carta le_carta(void);
float calcula_dens_pop(Carta carta);
float calcula_pib_per_capta(Carta carta);
float calcula_poder(Carta carta);
void imprime_carta(Carta carta);
void menu_inicial(Carta c1, Carta c2);
void imprime_menu();
void escolhe_atributos(Carta c1, Carta c2);
int le_opcao_comparar(int numero);
void imprime_menu_comparar(int numero);
void imprime_resultado(Carta c1, Carta c2, int opcao);
void compara_atributo(
    float atbr1,
    float atbr2,
    char nome_pais1[],
    char nome_pais2[],
    char nome_atbr[],
    int dens_demo
);
float valor_atributo(Carta carta, int opcao);
int imprime_soma(char nome1[], char nome2[], float soma1, float soma2);

// Main:

int main(void) {
    int qtd_cartas = 2;


    Carta cartas[qtd_cartas];

    // Le as cartas
    for (int i = 0; i < qtd_cartas; i++) {
        printf("Adicione os dados da Carta %d:\n", i + 1);
        cartas[i] = le_carta();
        // Calcula Dados
        cartas[i].dens_pop = calcula_dens_pop(cartas[i]);
        cartas[i].pib_per_capta = calcula_pib_per_capta(cartas[i]);
        cartas[i].poder = calcula_poder(cartas[i]);
    }

    // Imprime as cartas
    for (int i = 0; i < qtd_cartas; i++) {
        printf("\nCarta %d:\n", i + 1);
        imprime_carta(cartas[i]);
    }

    menu_inicial(cartas[0], cartas[1]);

    return 0;
}

// Funcoes:

Carta le_carta(void) {
    Carta carta;

    printf("Digite o nome do país:\n");
    scanf(" %s", carta.nome);

    getchar(); // consumir ENTER

    printf("Digite a populacao da cidade:\n");
    scanf("%lu", &carta.populacao);

    printf("Digite a area da cidade:\n");
    scanf("%f", &carta.area);

    printf("Digite o pib da cidade:\n");
    scanf("%f", &carta.pib);

    printf("Digite a quantidade de pontos turisticos:\n");
    scanf("%d", &carta.pontos_turisticos);

    return carta;
}

float calcula_dens_pop(Carta carta) {
    return carta.populacao / carta.area;
}

float calcula_pib_per_capta(Carta carta) {
    return carta.pib / carta.populacao; // PIB per capta em bilhoes de reais.
}

float calcula_poder(Carta carta) {
    return carta.pontos_turisticos +
           carta.populacao +
           carta.area +
           carta.pib +
           carta.pib_per_capta -
           carta.dens_pop;
}

void imprime_carta(Carta carta) {
    printf("País: %s\n", carta.nome);
    printf("Populacao: %lu\n", carta.populacao);
    printf("Area: %.2f km² \n", carta.area);
    printf("PIB: %.2f bilhões de reais\n", carta.pib);
    printf("Pontos turisticos: %d\n", carta.pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km²\n", carta.dens_pop);
    printf("PIB per Capita: %.6f bilhões de reais por hab.\n", carta.pib_per_capta);
    printf("Poder: %.2f\n", carta.poder);
}

void menu_inicial(Carta c1, Carta c2) {
    int opcao;

    imprime_menu();

    if (scanf("%d", &opcao) != 1) {
        printf("Entrada inválida!\n");

        // Limpa o buffer de entrada
        while (getchar() != '\n');

        menu_inicial(c1, c2);
        return;
    }

    switch (opcao) {
        case 0:
            printf("Saindo...\n");
            break;

        case 1:
            printf("Cartas: %s e %s\n", c1.nome, c2.nome);
            break;

        case 2:
            escolhe_atributos(c1, c2);
            break;

        default:
            printf("Opção inválida!\n");
            menu_inicial(c1, c2);
            break;
    }
}

void imprime_menu() {
    printf("\nEscolha uma opção (Digite o número correspondente):\n\n");
    printf("1 - Nome do país\n");
    printf("2 - Comparar Atributos\n");
    printf("0 - Sair\n");
}

void escolhe_atributos(Carta c1, Carta c2) {
    int atributos[2];

    for (int i = 0; i < 2; i++) {
        int opcao = le_opcao_comparar(i);

        switch (opcao) {
            case 0:
                menu_inicial(c1, c2);
                return;

            default:
                atributos[i] = opcao;
                break;
        }
    }

    printf("País 1: %s\n", c1.nome);
    printf("País 2: %s\n\n", c2.nome);

    for (int i = 0; i < 2; i++) {
        imprime_resultado(c1, c2, atributos[i]);
    }

    float soma1 = valor_atributo(c1, atributos[0]) + valor_atributo(c1, atributos[1]);
    float soma2 = valor_atributo(c2, atributos[0]) + valor_atributo(c2, atributos[1]);

    imprime_soma(c1.nome,c2.nome, soma1, soma2);
}

int le_opcao_comparar(int numero) {
    int opcao;

    imprime_menu_comparar(numero);

    if (scanf("%d", &opcao) != 1) {
        printf("Entrada inválida!\n");

        // Limpa o buffer de entrada
        while (getchar() != '\n');

        le_opcao_comparar(numero);
        return 0;
    }

    switch (opcao) {
        case 0: case 1: case 2: case 3: case 4: case 5:
            return opcao;

        default:
            printf("Opção inválida!\n");
            le_opcao_comparar(numero);
            break;
    }
}

void imprime_menu_comparar(int numero) {
    printf("\nEscolha o %s atributo (Digite o número correspondente):\n\n", numero == 0 ? "Primeiro" : "Segundo");
    printf("1 - Comparar Atributos\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Número de pontos turísticos\n");
    printf("5 - Densidade demográfica\n");
    printf("0 - Voltar\n");
}

void imprime_resultado(Carta c1, Carta c2, int opcao) {
    switch (opcao) {
        case 1:
            compara_atributo(
                (float) c1.populacao,
                (float) c2.populacao,
                c1.nome,
                c2.nome,
                "Populacao", 0
            );
            break;

        case 2:
            compara_atributo(
                c1.area,
                c2.area,
                c1.nome,
                c2.nome,
                "Área", 0
            );
            break;

        case 3:
            compara_atributo(
                c1.pib,
                c2.pib,
                c1.nome,
                c2.nome,
                "PIB", 0
            );
            break;

        case 4:
            compara_atributo(
                (float) c1.pontos_turisticos,
                (float) c2.pontos_turisticos,
                c1.nome,
                c2.nome,
                "Pontos Turísticos", 0
            );
            break;

        case 5:
            compara_atributo(
                c1.dens_pop,
                c2.dens_pop,
                c1.nome,
                c2.nome,
                "Densidade Demográfica", 1
            );
            break;
    }
}

void compara_atributo(
    float atbr1,
    float atbr2,
    char nome_pais1[],
    char nome_pais2[],
    char nome_atbr[],
    int dens_demo
) {
    printf("Comparando %s:\n", nome_atbr);
    printf("%s do País %s: %.2f\n", nome_atbr, nome_pais1, atbr1);
    printf("%s do País %s: %.2f\n", nome_atbr, nome_pais2, atbr2);

    printf("Resultado: ");
    if (atbr1 == atbr2) {
        printf("Empate!\n\n");
    } else if (atbr1 > atbr2) {
        if (dens_demo) {
            printf("%s venceu!\n\n", nome_pais2);
        } else {
            printf("%s venceu!\n\n", nome_pais1);
        }
    } else {
        if (dens_demo) {
            printf("%s venceu!\n\n", nome_pais1);
        } else {
            printf("%s venceu!\n\n", nome_pais2);
        }
    }
}

float valor_atributo(Carta carta, int opcao) {
    switch (opcao) {
        case 1:
            return (float) carta.populacao;

        case 2:
            return carta.area;

        case 3:
            return carta.pib;

        case 4:
            return (float) carta.pontos_turisticos;

        case 5:
            return carta.dens_pop;
    }
}

int imprime_soma(char nome1[], char nome2[], float soma1, float soma2) {
    printf("Comparando soma de atributos:\n");
    printf("Soma do %s: %.2f\n", nome1, soma1);
    printf("Soma do %s: %.2f\n", nome2, soma2);

    if (soma1 == soma2) {
        printf("Empate!\n\n");
    } else if (soma1 > soma2) {
        printf("Resultado: %s venceu!\n\n", nome1);
    } else {
        printf("Resultado: %s venceu!\n\n", nome2);
    }
}
