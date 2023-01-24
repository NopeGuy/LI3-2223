#define _XOPEN_SOURCE
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <glib-2.0/glib.h>
#include <ctype.h>
#include "../includes/queries.h"
#include "../includes/constructors.h"

//tirar catalogo de funçoes do interpretador e ver o que é STDOUT_FILENO e TIOCGWINSZ

void interpreter(CATALOGO cat, int writeToFile)
{
    int terminated = 0;
    char *userInput = ' ';
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    char *imprimir = ""
                     "--------------------------------------------------------------------\n"
                     "|1| Listar Resumo de perfil (User ou Driver), <ID>                  |\n"
                     "--------------------------------------------------------------------\n"
                     "|2| 'N' condutores com a maior avaliação média, <N>                 |\n"
                     "--------------------------------------------------------------------\n"
                     "|3| 'N' utilizadores com maior distância viajada, <N>               |\n"
                     "--------------------------------------------------------------------\n"
                     "|4| Preço médio de viagem (sem gorjetas) por cidade, <cidade>       |\n"
                     "--------------------------------------------------------------------\n"
                     "|5| Preço médio das viagens (sem gorjetas) num intervalo de tempo,  |\n"
                     "<data A> <data B>                                                   |\n"
                     "--------------------------------------------------------------------\n"
                     "|6| Distância média percorrida numa determinada cidade num intervalo|\n"
                     "de tempo, <cidade> <data A> <data B>                                |\n"
                     "--------------------------------------------------------------------\n"
                     "|7| Top 'N' condutores de uma determinada cidade, <N> <cidade>      |\n"
                     "--------------------------------------------------------------------\n"
                     "|8| Todas as viagens nas quais o User e o Driver são do género      |\n"
                     "inserido (M/F) e têm perfis com 'X' ou mais anos, <gender> <X>      |\n"
                     "--------------------------------------------------------------------\n"
                     "|9| Listar viagens nas quais o passageiro deu gorjeta no intervalo  |\n"
                     "de tempo inserido, <data A> <data B>                                |\n"
                     "--------------------------------------------------------------------\n"
                     "| 99 | Fechar programa                                              |\n"
                     "--------------------------------------------------------------------\n";
    while (terminated == 0)
    {
        system("clear");
        int queryNum = 0;
        int validez;
        char arg1[300000];
        int argInt1 = 0;
        int argInt2 = 0;
        char arg3[300000], arg4[300000];

        printf("%s", imprimir);
        if (validez == 0)
            printf("Opção inválida, introduza outra: ");
        else
            printf("Introduz uma opção: ");
        scanf("%d", &userInput);
        if (userInput >= 0 && userInput <= 9)
        {
            validez = 1;
            if (userInput == 1)
            {
                printf("Introduza o ID: ");
                scanf("%s", arg1);
                queryNum = 1;
            }
            if (userInput == 2)
            {
                printf("Introduza o N: ");
                scanf("%d", &argInt1);
                queryNum = 2;
            }
            if (userInput == 3)
            {
                printf("Introduza o N: ");
                scanf("%d", &argInt1);
                queryNum = 3;
            }
            if (userInput == 4)
            {
                printf("Introduza a cidade: ");
                scanf("%s", arg1);
                queryNum = 4;
            }
            if (userInput == 5)
            {
                printf("Introduza a data A: ");
                scanf("%s", arg1);
                printf("Introduza a data B: ");
                scanf("%s", arg3);
                queryNum = 5;
            }
            if (userInput == 6)
            {
                printf("Introduza a cidade: ");
                scanf("%s", arg1);
                printf("Introduza a data A: ");
                scanf("%s", arg3);
                printf("Introduza a data B: ");
                scanf("%s", arg4);
                queryNum = 6;
            }
            if (userInput == 7)
            {
                printf("Introduza o N: ");
                scanf("%d", &argInt1);
                printf("Introduza a cidade: ");
                scanf("%s", arg3);
                queryNum = 7;
            }
            if (userInput == 8)
            {
                printf("Introduza o género: ");
                scanf("%s", arg1);
                printf("Introduza a idade: ");
                scanf("%d", &argInt1);
                queryNum = 8;
            }
            if (userInput == 9)
            {
                printf("Introduza a data A: ");
                scanf("%s", arg1);
                printf("Introduza a data B: ");
                scanf("%s", arg3);
                queryNum = 9;
            }
        }
        if (userInput == 99)
        {
            printf("A fechar...\n");
            terminated = 1;
        }
        if (userInput > 9 && userInput < 99)
        {
            validez = 0;
        }
    }
}

void commandInterpreter(CATALOGO cat, char *filename)
{
    int max_len = 200000;
    int query = 1;
    char buff[max_len];
    char *commandFile = filename;
    FILE *file = fopen(commandFile, "r");

    if (file == NULL)
    {
        printf("Ficheiro não encontrado, introduza ficheiro em: ./entrada/commands.txt e escreva o PATH completo\n");
        return 0;
    }

    // correr commands
    while (fgets(buff, max_len, file))
    {
        printf("A executar a query %d...\n", query);
        executeQueries(buff, cat, query);
        query++;
    }
    fclose(file);
}
