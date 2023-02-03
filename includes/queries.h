#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>
#include "catalogo.h"

//Queries


//void freeQuery(QUERY c);


gint inteiros(gconstpointer a, gconstpointer b);

gint CompareNames (gconstpointer name1, gconstpointer name2);

char* profilefromUsername(CATALOGO cat,char*username, FILE* dest);

char* profilefromID(CATALOGO cat,int id_condutor, FILE* dest);

void medianPrice(CATALOGO cat, char* cidade, FILE *f);

void medianDistBetween(GTree *rides, char* city, struct tm date1, struct tm date2, FILE *f);