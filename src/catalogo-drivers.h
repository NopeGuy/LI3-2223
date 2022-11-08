#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>
#include "catalogo.h"


typedef struct drivers* DRIVERS;

int getRepos(DRIVERS c);

struct tm getDate(DRIVERS c);

void buildDrivers(char* line, int lineNumber, CATALOGO cat);

void loadDrivers(char* filename, CATALOGO cat);