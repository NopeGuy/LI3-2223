#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <glib.h>
#include <ctype.h>

#include "main.h"
#include "catalogo-users.h"
#include "catalogo-drivers.h"
#include "catalogo-rides.h"
#include "queries.h"
#include "constructors.h"
#include "catalogo.h"

void executeQueries(char *line,CATALOGO cat, int query);

#endif //MAIN_H
