#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>
#include "catalogo.h"

//Queries
typedef struct query* QUERY;

void freeQuery(QUERY c);


gint inteiros(gconstpointer a, gconstpointer b);
