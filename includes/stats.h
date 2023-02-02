//stats
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>

typedef struct statd* STATSDRIVERS;
typedef struct statu* STATSUSERS;
double calcula_media(int total_r, double total_a);
int getId(STATSDRIVERS d);
void setDist(STATSDRIVERS d, int id);
int getTotalr(STATSDRIVERS d);
void setTotalr(STATSDRIVERS d, int tr);
double getTotala(STATSDRIVERS d);
void setTotala(STATSDRIVERS d, double ta);
char* getCity(STATSDRIVERS d);
double getDist(STATSUSERS u);
void setDist(STATSUSERS u, double d);