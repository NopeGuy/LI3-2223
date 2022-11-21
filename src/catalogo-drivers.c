#define _XOPEN_SOURCE
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>

#include "catalogo-drivers.h"
#include "catalogo.h"

struct drivers
{
    int id;
    char *name;
    struct tm birth_day;
    char gender;
    char *car_class;
    char *license_plate;
    char *city;
    
    struct tm account_creation;
    char account_status;
};

// getters

int getDriversId(DRIVERS c)
{
    return c->id;
}

char* getDriversName(DRIVERS c)
{
    return strdup(c->name);
}

struct tm getDriversBirthDay(DRIVERS c)
{
    return c->birth_day;
}

char getDriversGender(DRIVERS c)
{
    return (c->gender);
}

char *getDriversCarClass(DRIVERS c)
{
    return strdup(c->car_class);
}

char *getDriversLicensePlate(DRIVERS c)
{
    return strdup(c->license_plate);
}

char *getDriversCity(DRIVERS c)
{
    return strdup(c->city);
}

struct tm getDriversAccCreation(DRIVERS c)
{
    return c->account_creation;
}

char getDriversAccountStatus(DRIVERS c)
{
    return (c->account_status);
}

//Build and Load

void buildDrivers(char *line, int lineNumber, CATALOGO cat)
{
    GTree *t = NULL;
    t = getDrivers(cat);

    char *buff2 = line;
    DRIVERS temp = malloc(sizeof(struct drivers));

    // Get the info
    int id = atoi(strsep(&buff2, ";")); //";\n"
    char *name = strsep(&buff2, ";");

    char *datestr = strsep(&buff2, ";");
    struct tm birth_dayst;
    strptime(datestr, "%d-%m-%Y", &birth_dayst);

    char gender = strsep(&buff2, ";")[0]; // verify later
    char *car_class = strsep(&buff2, ";");
    char *license_plate = strsep(&buff2, ";");
    char *city = strsep(&buff2, ";");

    char *datestr2 = strsep(&buff2, ";");
    struct tm account_creationst;
    strptime(datestr2, "%d-%m-%Y", &account_creationst);

    char account_status = strsep(&buff2, ";")[0]; // verify later

    // verifier
    if (id == 0)
        return;

    // Send the info
    temp->id = id;
    temp->name = name;
    temp->birth_day = birth_dayst;
    temp->gender = gender;
    temp->car_class = car_class;
    temp->license_plate = license_plate;
    temp->city = city;
    temp->account_creation = account_creationst;
    temp->account_status = account_status;

    g_tree_insert(t, GINT_TO_POINTER(id), temp);
}

void loadDrivers(char *filename, CATALOGO cat)
{
    int max_len = 200000;
    char buff[max_len];

    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Ficheiro não encontrado: %s\n", filename);
        return;
    }
    fgets(buff, max_len, f);
    int line = 0;
    while (fgets(buff, max_len, f))
    {
        buildDrivers(buff, line, cat);
        line++;
    }
    fclose(f);
}