#define _XOPEN_SOURCE
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <glib.h>
#include <ctype.h>
#include "queries.h"
#include "catalogo.h"
#include "constructors.h"

char *fileUsers;
char *fileDrivers;
char *fileRides;

int main(int argc, char const *argv[])
{
    GTree *users = g_tree_new((GCompareFunc)g_ascii_strcasecmp);
    GTree *drivers = g_tree_new(inteiros);
    GTree *rides = g_tree_new(inteiros);

    int max_len = 500;
    char *buff = malloc(sizeof(char) * 500);
    int query = 1;


    CATALOGO cat = iniciarCatalogo();

    setUsers(cat, g_tree_new((GCompareFunc)g_ascii_strcasecmp));
    setDrivers(cat, g_tree_new(inteiros));
    setRides(cat, g_tree_new(inteiros));


    //load de comandos
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
        executeQueries(buff, users, drivers, rides, query);
        query++;
    }


    //unload
    fclose(file);

    g_tree_destroy(getUsers(cat));
    g_tree_destroy(getCommits(cat));
    g_tree_destroy(getRep(cat));
    free(cat);

    return 1;
}

void executeQueries(char *line, GTree *users, GTree *commits, GTree *repos, int query)
{
    char *id = strsep(&line, " ");
    char *buff = &line;
    int idInt = atoi(id);
    int firstTime = 1;
    char queryToString[30] = "";
    char fileName[2000] = "";

    strcat(fileName, "./saida/command");
    sprintf(queryToString, "%d", query);
    switch (idInt)
    {
    case 1:
        //chamar ficheiro de queries ou fazer aqui?

        
        // queryCharOut = numTypes(users);
        // // char* writeToFile1 = malloc(sizeof(char)*200);
        // // sprintf(writeToFile1, "%d", queryCharOut);
        // strcat(fileName, queryToString);
        // strcat(fileName, "_output.txt");
        // saveToFile(fileName, queryCharOut, firstTime);
        break;
    case 2:
    
        break;
    case 3:
    
        break;
    case 4:
    
        break;

    case 5:
    
        break;
    case 6:
    
        break;
    case 7:
    
    }
    
}