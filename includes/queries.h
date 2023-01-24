#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>


//Queries


//void freeQuery(QUERY c);


gint inteiros(gconstpointer a, gconstpointer b);
gint CompareNames (gconstpointer name1, gconstpointer name2);
char* profilefromUsername(char* username, GTree *users, GTree *rides, FILE* dest);
char* profilefromID(int id_condutor,GTree *drivers,GTree *rides, FILE* dest);
void medianPrice(GTree* rides, char* cidade, FILE *f);
void medianPriceBetween(GTree *rides, struct tm date1, struct tm date2, FILE *f);
