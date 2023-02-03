//stats
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>
#include "../includes/catalogo.h"
#include "../includes/stats.h"
#include "../includes/main.h"

struct statcity{
    int total_rides;
    double total_a;
    char* city;
};

struct stat2{
    int id;
    int total_rides;
    GList* cidades_stats; 
    double total_a;
};

struct stat3{
    char* name;
    double dist;
};

int getTotalRidesCity(STATSCITY c){
    return c->total_rides;
}

double getTotalACity(STATSCITY c){
    return c->total_a;
}

char* getCity(STATSCITY c){
    return strdup(c->city);
}

int getId(STATSDRIVERS d){
    return d->id;
}

void setDist(STATSDRIVERS d, int id){
    d->id = id;
}

int getTotalr(STATSDRIVERS d){
    return d->total_rides;
}

void setTotalr(STATSDRIVERS d, int tr){
    d->total_rides = tr;
}

double getTotala(STATSDRIVERS d){
    return d->total_a;
}

void setTotala(STATSDRIVERS d, double ta){
    d->total_a = ta;
}

char* getCity(STATSDRIVERS d){
    return strdup(d->city);
}

double calcula_media(int total_r, double total_a){
    return total_a / (double)total_r;
}

double getDist(STATSUSERS u){
    return u->dist;
}

void setDist(STATSUSERS u, double d){
    u->dist = d;
}

gint compare_statDrivers(gconstpointer a, gconstpointer b)
{
    STATSDRIVERS node_a = (STATSDRIVERS)a;
    STATSDRIVERS node_b = (STATSDRIVERS)b;

    if (node_a->total_a < node_b->total_a)
        return -1;
    else if (node_a->total_a > node_b->total_a)
        return 1;
    else{ //se as avaliacoes forem iguais, ordena por ordem crescente de id
            if (node_a->id < node_b->id)  
                return -1;
            else if (node_a->id > node_b->id)
                return 1;
        }
    return 0;
}

gint compare_statUsers(gconstpointer a, gconstpointer b)
{
    STATSUSERS node_a = (STATSUSERS)a;
    STATSUSERS node_b = (STATSUSERS)b;

    if (node_a->dist < node_b->dist)
        return -1;
    else if (node_a->dist > node_b->dist)
        return 1;
    return (strcmp (node_a->name, node_b->name));
}

gboolean comparecities(gpointer value, gpointer citycmp){
    STATSCITY city= (STATSCITY)value;
    char*citycmp = (char) citycmp;
    if(stcmp(value->city,citycmp)){
        return TRUE;
    }
    return FALSE;
}

void buildEstatDriver(ESTAT estat, int driver, double score, char* city){
    GTree* t = NULL;
    t = getRides(cat);
    STATSDRIVERS tempd = malloc(sizeof(struct stat2));
    STATSCITY tempc = malloc(sizeof(struct statcity));
    tempd->driver = driver;
    tempd->total_a = score;
    tempd->total_rides = 0;
    tempc->driver = driver;
    tempc->total_a = score;
    tempc->city = strdup(city);
    if(g_tree_lookup(t, driver) != NULL){
        tempd = g_tree_lookup(t, driver);
        tempd->total_a += score;
        tempd->total_rides += 1
        GList* tmp = g_list_find_custom(tempd->cidades_stats, tempc->city, comparecities)
        if(tmp != NULL){
            tmp->data->total_rides += 1;
            tmp->data->total_a += tempc->score;
        }else{
            g_list_append(tempd->cidades_stats, tempc);
        }
        g_tree_insert(t,tempd->driver,tempd);
    }
    else{
        g_list_append(tempd->cidades_stats, tempc);
        g_tree_insert(t,tempd->driver,tempd);
    }

    free(tempd);
    free(tempc);

}