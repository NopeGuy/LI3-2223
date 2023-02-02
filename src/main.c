#define _XOPEN_SOURCE
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <glib-2.0/glib.h>
#include <ctype.h>
#include "../includes/queries.h"
#include "../includes/catalogo.h"
#include "../includes/constructors.h"
#include "../includes/stats.h"

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
    //array com os top50 drivers
    STATSDRIVERS d[50];
    //array top50 users
    u[50]

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
    fileUsers = malloc(sizeof(char)*300);
    fileDrivers = malloc(sizeof(char)*300);
    fileRides = malloc(sizeof(char)*300);


    strcat(fileUsers, "entrada/users.csv");
    strcat(fileDrivers, "entrada/drivers.csv");
    strcat(fileRides, "entrada/rides.csv");

    loadRides(fileRides, cat);  
    loadUsers(fileUsers, cat);
    loadDrivers(fileDrivers, cat);



    //correr commands
    while (fgets(buff, max_len, file))
    {
        printf("A executar a query %d...\n", query);
        executeQueries(buff,cat,query);
        query++;
    }


    //unload
    fclose(file);

    g_tree_destroy(getUsers(cat));
    g_tree_destroy(getDrivers(cat));
    g_tree_destroy(getRides(cat));
    free(cat);
    //free(buff);

    return 1;
}
