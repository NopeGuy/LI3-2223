#define _XOPEN_SOURCE
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <glib-2.0/glib.h>
#include <ctype.h>
#include "../includes/queries.h"
#include "../includes/catalogo-users.h"
#include "../includes/catalogo-drivers.h"
#include "../includes/catalogo-rides.h"
#include "../includes/constructors.h"
#include "../includes/interpreter.h"

char *fileUsers;
char *fileDrivers;
char *fileRides;

int main(int argc, char const *argv[])
{
    GTree *users = g_tree_new(CompareNames);
    GTree *drivers = g_tree_new(inteiros);
    GTree *rides = g_tree_new(inteiros);

    int max_len = 500;
    char *buff = malloc(sizeof(char) * 500);
    int query = 1;


    char *commandFile = "./entrada/commands.txt";
    FILE *file = fopen(commandFile, "r");

    if (file == NULL)
    {
        printf("Ficheiro não encontrado, introduza ficheiro em: ./entrada/commands.txt\n");
        return 0;
    }


    //load de entrada
    fileUsers = malloc(sizeof(char)*300);
    fileDrivers = malloc(sizeof(char)*300);
    fileRides = malloc(sizeof(char)*300);

    //unload

    strcat(fileUsers, "entrada/users.csv");
    strcat(fileDrivers, "entrada/drivers.csv");
    strcat(fileRides, "entrada/rides.csv");

    loadDrivers(fileDrivers, drivers);
    loadUsers(fileUsers, users);
    loadRides(fileRides, rides);

// correr commands
    /*passar isto*/
    if (argc == 1)
    {
        interpreter(users, rides, drivers, 0);
    }


    if (argc == 2)
    {
        commandInterpreter(users, rides, drivers, argv[1]);
    }

    if (strcmp(argv[0], "./testes") == 0)
    {
    }
    //unload
    fclose(file);
    g_tree_destroy(rides);
    g_tree_destroy(users);
    g_tree_destroy(drivers);
    
    //free(buff);

    return 1;
}

void executeQueries(char *line,GTree *users,GTree *rides,GTree *drivers, int query)
{
    char *id = strsep(&line, " ");
    int idInt = atoi(id);
    char *buff = &line;
    char queryToString[30] = "";
    char fileName[2000] = "";
    char*username;
    int topN;
    char* cidade;

    struct tm data1, data2;


    sprintf(queryToString, "%d", query);
    strcat(fileName, "./Resultados/command");
    strcat(fileName, queryToString);
    strcat(fileName, "_output.txt");
    FILE* f = fopen(fileName, "w");
    switch (idInt)
    {
    // chamar ficheiro de queries
    case 1:
        username =strsep(&line,"\n");
        //Query1/ separada se é user ou driver
        if ((username[0] >= 'a' && username[0] <= 'z') || (username[0] >= 'A' && username[0] <= 'Z'))
        {

            if(username!=NULL)
                profilefromUsername(username, users, rides, f);
        }
        else
        {
            int id_condutor = atoi(username);
                profilefromID(id_condutor, rides, drivers, f);
        }

        break;
    case 2:
    //Query2/ N top condutores com maior avaliação média
        topN=atoi(strsep(&line," "));
        //topDrivers(topN);
        break;

    case 3:
        //Query3();
        break;

    case 4:
    //Query4/ Preço médio das viagens (sem considerar gorjetas) numa determinada cidade
        cidade =strsep(&line,"\n");
        medianPrice(rides, drivers, cidade, f);
        break;

    case 5:
        data1 = verifyTime(strsep(&line," "));
        data2 = verifyTime(strsep(&line," "));
        medianPriceBetween(rides, data1, data2, f);
        break;

    case 6:
        //Query6();
        break;

    case 7:
    //Query7/top Rides de uma cidade e não top rides de uma nacionalidade
        //topPerCity();
        break;
    case 8:
        //Query8();
        break;
            
    case 9:
        //Query9();
        break;

    }

    fclose(f);
}