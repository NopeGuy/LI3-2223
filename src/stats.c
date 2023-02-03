//stats
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>
#include "../includes/catalogo.h"
#include "../includes/stats.h"

struct stat2{
    int id;
    int total_rides;
    double total_a;
    char* city;
};

struct stat3{
    char* name;
    double dist;
};

int getId(STATSDRIVERS d){
    return d->id;
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


