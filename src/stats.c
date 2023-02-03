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

// build and load estat
// quack
void buildTopDrivers(ESTAT estat, GTree* rides)
{
    //input tem de receber de dentro da rides os valores que queremos e somar caso
    //o id do driver seja igual
    GTree *t = NULL;
    t = getTopDrivers(estat);
    STATSDRIVERS temp = malloc(sizeof(struct stat2));


    //int id = iteradorRides(rides);
    
    //temp->id = strdup(id);

    g_tree_insert(t, temp->id, temp);
}

