#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <glib.h>
#include <ctype.h>

#include "catalogo-users.h"
#include "catalogo-drivers.h"
#include "catalogo-rides.h"
#include "queries.h"
#include "constructors.h"


void executeQueries(char *line,GTree *users,GTree *rides,GTree *drivers, int query);

#endif //MAIN_H
