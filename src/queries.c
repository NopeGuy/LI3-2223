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
    int id;
    double price_sum;
    double ranking_sum;
    int total_drives;
};

typedef struct trip_iter* TRIP_ITER;


gboolean conta_viagens(gpointer key, gpointer value, gpointer data) {
    TRIP_ITER trip_iterator = (TRIP_ITER) data;
    RIDES ride = (RIDES) value;
    GTree* driversTree = getDrivers(trip_iterator->cat);

    if(trip_iterator->id != -1){
        if (getRidesDriver(ride) == trip_iterator->id) {
            float tripPrice = getTripPrice(driversTree, getRidesDriver(ride), getRidesDistance(ride));
            trip_iterator->price_sum += tripPrice;
            trip_iterator->total_drives++;
            trip_iterator->ranking_sum += getRidesScoreUser(ride);
        }
    } else {

        if (strcmp(getRidesUser(ride), trip_iterator->username) == 0) {
            float tripPrice = getTripPrice(driversTree, getRidesDriver(ride), getRidesDistance(ride));
            trip_iterator->price_sum += tripPrice;
            trip_iterator->total_drives++;
            trip_iterator->ranking_sum += getRidesScoreUser(ride);
        }

    }
    return FALSE;
}

char* profilefromUsername(CATALOGO cat,char* username, FILE* dest)
{
    USER u = g_tree_lookup(getUsers(cat), username);

    if(u == NULL) {
        fprintf(dest, "%s", "Utilizador nao encontradoo.");
        return "";
    }

    TRIP_ITER trip = malloc(sizeof(struct trip_iter));
    trip->username = username;
    trip->id = -1;
    trip->cat = cat;
    trip->total_drives = 0;
    trip->ranking_sum = 0.000;
    trip->price_sum = 0.000;

    g_tree_foreach(getRides(cat), conta_viagens, trip);

    fprintf(dest, "%d", getUsername(u));
    fprintf(dest, ";");
    fprintf(dest, "%c", getGender(u));
    fprintf(dest, ";");
    fprintf(dest, "%d", getAge(getBirth_date(u)));
    fprintf(dest, ";");
    fprintf(dest, "%0.3f", trip->ranking_sum/trip->total_drives);
    fprintf(dest, ";");
    fprintf(dest, "%d", trip->total_drives);
    fprintf(dest, ";");
    fprintf(dest, "%0.3f", trip->price_sum);




    free(trip);


    return "";
}

char* profilefromID(CATALOGO cat,int id_condutor, FILE* dest)
{
    DRIVERS d = g_tree_lookup(getDrivers(cat), id_condutor);

    if(d == NULL) {
        fprintf(dest, "%s", "Driver nao encontrado.");
        return "";
    }

    TRIP_ITER trip = malloc(sizeof(struct trip_iter));
    trip->id = id_condutor;
    trip->cat = cat;
    trip->total_drives = 0;
    trip->ranking_sum = 0.000;
    trip->price_sum = 0.000;

    g_tree_foreach(getRides(cat), conta_viagens, trip);

    fprintf(dest, "%s", getDriversName(d));
    fprintf(dest, ";");
    fprintf(dest, "%c", getDriversGender(d));
    fprintf(dest, ";");
    fprintf(dest, "%d", getAge(getDriversBirthDay(d)));
    fprintf(dest, ";");
    fprintf(dest, "%0.3f", trip->ranking_sum/trip->total_drives);
    fprintf(dest, ";");
    fprintf(dest, "%d", trip->total_drives);
    fprintf(dest, ";");
    fprintf(dest, "%0.3f", trip->price_sum);




    free(trip);


    return "";
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

struct cities_iter
{
    CATALOGO cat;
    char* city;
    double preco_total;
};
typedef struct cities_iter* CITIES_ITER;


gboolean city_iter(gpointer key, gpointer value, gpointer data) {
    CITIES_ITER cities_iter = (CITIES_ITER) data;
    RIDES ride = (RIDES) value;
    GTree* driversTree = getDrivers(cities_iter->cat);

    if (strcmp(getRidesCity(ride), cities_iter->city) == 0) {
        float tripPrice = getTripPrice(driversTree, getRidesDriver(ride), getRidesDistance(ride));
        cities_iter->preco_total += tripPrice;
    }
    return FALSE;
}



void medianPrice(CATALOGO cat, char* cidade, FILE *f)
{
    //inicialização da struct aux query4
    CITIES_ITER cities_iter = malloc(sizeof(struct cities_iter));
    cities_iter->cat = cat;
    cities_iter->city = cidade;

    g_tree_foreach(getRides(cat), city_iter,cities_iter);

    double preco_medio = cities_iter->preco_total / g_tree_nnodes(getRides(cat));

    fprintf(f, "%0.3f", preco_medio);

    free(cities_iter);
   

}
