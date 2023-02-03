//stats
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>

typedef struct stat2* STATSDRIVERS;
typedef struct stat3* STATSUSERS;
double calcula_media(int total_r, double total_a);
int getId(STATSDRIVERS d);
int getTotalr(STATSDRIVERS d);
void setTotalr(STATSDRIVERS d, int tr);
double getTotala(STATSDRIVERS d);
void setTotala(STATSDRIVERS d, double ta);
char* getCity(STATSDRIVERS d);
double getDist(STATSUSERS u);
void setDist(STATSUSERS u, double d);

void buildEstatDrivers(ESTAT estat, GTree* rides, int id);