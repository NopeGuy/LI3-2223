#define _XOPEN_SOURCE
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <glib-2.0/glib.h>
#include <ctype.h>
#include "queries.h"
#include "catalogo.h"
#include "constructors.h"

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


    CATALOGO cat = iniciarCatalogo();

    setUsers(cat, users);
    setDrivers(cat, drivers);
    setRides(cat, rides);



    char *commandFile = "./entrada/commands.txt";
    FILE *file = fopen(commandFile, "r");

    if (file == NULL)
    {
        printf("Ficheiro não encontrado, introduza ficheiro em: ./entrada/commands.txt\n");
        return 0;
    }


    //load de entrada
    fileUsers = "./entrada/users.csv";
    fileDrivers = "./entrada/drivers.csv";
    fileRides = "./entrada/rides.csv";

    loadUsers(fileUsers, cat);
    loadDrivers(fileDrivers, cat);
    loadRides(fileRides, cat);


    //correr commands
    while (fgets(buff, max_len, file))
    {
        executeQueries(buff,cat,query);
        query++;
    }


    //unload
    fclose(file);

    g_tree_destroy(getUsers(cat));
    g_tree_destroy(getDrivers(cat));
    g_tree_destroy(getRides(cat));
    free(cat);

    return 1;
}

void executeQueries(char *line,CATALOGO cat, int query)
{
    char *id = strsep(&line, " ");
    int idInt = atoi(id);
    char *buff = &line;
    char queryToString[30] = "";
    char fileName[2000] = "";
    char*username;
    int topN;
    char* cidade;




    sprintf(queryToString, "%d", query);
    strcat(fileName, "./Resultados/command");
    strcat(fileName, queryToString);
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
                profilefromUsername(cat,username, f);
        }
        else
        {
            int id_condutor = atoi(username);
                profilefromID(cat,id_condutor, f);
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
        medianPrice(cat, cidade, f);
        break;

    case 5:
        //Query5();
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