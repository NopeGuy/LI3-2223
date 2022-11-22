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

char* profileThroughId(CATALOGO cat,int id_condutor);
