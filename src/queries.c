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

//structs auxiliares

struct query4
{
    GTree* temp_drivers;
    char* cidade;
    char* message;
    int n_cidade;
    int n_Basic;
    int n_Green;
    int n_Premium;
    int nnodes;
    int nodoatual;
};
typedef struct query4* QUERY4;
//funcoes auxiliares

//balanceia a tree
gint inteiros(gconstpointer a, gconstpointer b)
{
    if (a > b)
        return 1;
    if (a < b)
        return -1;
    if (a == b)
        return 0;
}

gint CompareNames (gconstpointer name1, gconstpointer name2)
{
    return (strcmp (name1, name2));
}

//funcoes_aux Query4

int verificaCidade(char cidade,CATALOGO cat,int id_driver){
    GTree *temp=NULL;
    temp=getDrivers(cat);
    int* idDriver = toIntAsterix(id_driver);
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
    int* idDriver = toIntAsterix(id_driver);
    int* alvo = g_tree_lookup(temp,idDriver);
    char* tarifa = getDriversCarClass(alvo);
    g_tree_destroy(temp);
    return tarifa;
}

//funcao que remove todos os nodos que não são daquela cidade (para ser usada numa g_tree_foreach())
//(q4->temp_drivers,removePorCidade,q4)
gboolean removePorCidade (gpointer key, gpointer cidade, gpointer q4){

QUERY4 aux = (QUERY4) q4;
    if(aux->nodoatual>aux->nnodes) return TRUE; //Para parar a travessia na arvore
    int id = asterixToInt(key);
    //if(aux->cidade != )

aux->nodoatual++;
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

float getTripPrice(DRIVERS* treeDrivers, int driver_id, int km){
    DRIVERS driver = g_tree_lookup(treeDrivers, driver_id);
    int carClass = getDriversCarClass(driver);

    if(carClass == 1){
        return 4.00 + 0.79*km;
    }
    if(carClass == 0){
        return 3.25 + 0.62*km;
    }
    if(carClass == 2){
        return 5.20 + 0.94*km;
    }
}


//Query 1
struct trip_iter {
    CATALOGO cat;
    char* username;
    double price_sum;
    double ranking_sum;
    int total_drives;
};

typedef struct trip_iter* TRIP_ITER;


gboolean conta_viagens(gpointer key, gpointer value, gpointer data) {
    TRIP_ITER trip_iterator = (TRIP_ITER) data;
    RIDES ride = (RIDES) value;
    GTree* driversTree = getDrivers(trip_iterator->cat);

    if(strcmp(getRidesUser(ride), trip_iterator->username) == 0){
        float tripPrice = getTripPrice(driversTree, getRidesDriver(ride), getRidesDistance(ride));
        trip_iterator->price_sum += tripPrice;
        trip_iterator->total_drives++;
        trip_iterator->ranking_sum += getRidesScoreUser(ride);
    }

    return FALSE;
}

char* profilefromUsername(CATALOGO cat,char* username, FILE* dest)
{
    USER* u = g_tree_lookup(getUsers(cat), username);
    TRIP_ITER trip = malloc(sizeof(struct trip_iter));
    trip->username = username;
    trip->cat = cat;
    trip->total_drives = 0.000;
    trip->ranking_sum = 0;
    trip->price_sum = 0.000;

    g_tree_foreach(getRides(cat), conta_viagens, trip);

    if(u == NULL) {
        fprintf(dest, "%s", "Utilizador nao encontradoo.");
    }

    fprintf(dest, "%s", getUsername(u));
    fprintf(dest, ";");
    fprintf(dest, "%c", getGender(u));
    fprintf(dest, ";");
    fprintf(dest, "%s","DATA");
    fprintf(dest, ";");
    fprintf(dest, "%d", trip->ranking_sum/trip->total_drives);
    fprintf(dest, ";");
    fprintf(dest, "%d", trip->total_drives);
    fprintf(dest, ";");
    fprintf(dest, "%0.3f", trip->price_sum);




    free(trip);


    return "";
}

char* profileThroughId(CATALOGO cat,int id_condutor)
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
    //inicialização da struct aux query4
    QUERY4 q4 = malloc(sizeof(struct query4));
    q4->temp_drivers=getDrivers(cat);
    q4->cidade=cidade;
    q4->n_Basic=0;
    q4->n_Green=0;
    q4->n_Premium=0;
    q4->n_cidade=0;
    q4->nodoatual=0;
    q4->nnodes=g_tree_nnodes(q4->temp_drivers);

    g_tree_foreach(q4->temp_drivers,removePorCidade,q4);
   

    free(q4);
}
