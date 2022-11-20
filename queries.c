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

typedef struct query4{

} STRUCT_QUERY4;
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

int verificaCidade(char cidade,CATALOGO cat,int id_driver){
    GTree *temp=NULL;
    temp=getDrivers(cat);
    int* idDriver = GINT_TO_POINTER(id_driver);
    int* alvo = g_tree_lookup(temp,idDriver);
    if(cidade == getDriversCity(alvo)) {
        g_tree_destroy(temp);
        return 1;
    }
    g_tree_destroy(temp);
    return 0;
}

char* verificaClasse(int id_driver,CATALOGO cat)
{
    GTree *temp=NULL;
    temp=getDrivers(cat);
    int* idDriver = GINT_TO_POINTER(id_driver);
    int* alvo = g_tree_lookup(temp,idDriver);
    char* tarifa = getDriversCarClass(alvo);
    g_tree_destroy(temp);
    return tarifa;
}

//funcao que remove todos os nodos que não são daquela cidade (para ser usada numa g_tree_foreach())
gboolean removePorCidade (gpointer key, gpointer cidade, gpointer data){




}


int calculaBasic(int dist)
{
double preco=0;
preco += 0.62*dist;
return preco;
}

int calculaGreen(int dist)
{
double preco=0;
preco += 0.79*dist;
return preco;
}

int calculaPremium(int dist)
{
double preco=0;
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



void q4(char* cidade,CATALOGO cat)
{
    GTree *temp_drivers = NULL;
    temp_drivers=getDrivers(cat);


    g_tree_foreach(temp_drivers,removePorCidade,cat);
    setCidade(cat,g_tree_nnodes(temp_drivers));
    

}
