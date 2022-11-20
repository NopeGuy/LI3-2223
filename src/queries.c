#define _XOPEN_SOURCE
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>

#include "queries.h"
#include "catalogo-users.h"
#include "catalogo-rides.h"
#include "catalogo-drivers.h"
#include "constructors.h"
#include "catalogo.h"

//funcoes auxiliares
gint inteiros(gconstpointer a, gconstpointer b)
{
    if (a > b)
        return 1;
    if (a < b)
        return -1;
    if (a == b)
        return 0;
}

//funcoes_aux Query4
int verificaTarifa(int userId,GTree *drivers)
{
 
}

int calculaBasic(int dist)
{
double preco=3.25;
preco += 0.62*dist;
return preco;
}

int calculaGreen(int dist)
{
double preco=4.00;
preco += 0.79*dist;
return preco;
}

int calculaPremium(int dist)
{
double preco=5.20;
preco += 0.94*dist;
return preco;
}
// chamadas da main

//Query 1

profilefromUsername(GTree *users,char*username)
{

}

profileThroughId(GTree *drivers,int id_condutor)
{

}

//Query 2
topDrivers(int topN)
{
    // queryCharOut = numTypes(users);
    // // char* writeToFile1 = malloc(sizeof(char)*200);
    // // sprintf(writeToFile1, "%d", queryCharOut);
    // strcat(fileName, queryToString);
    // strcat(fileName, "_output.txt");
    // saveToFile(fileName, queryCharOut, firstTime);

}

//Query 3

//Query 4
med_preco_viagem(char* cidade)
{
    int dist = 0;

}
