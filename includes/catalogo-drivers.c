#define _XOPEN_SOURCE
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>

#include "../includes/catalogo-drivers.h"
#include "../includes/constructors.h"

struct drivers
{
    int id;
    char *name;
    struct tm birth_day;
    char gender;
    int car_class;
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

int getDriversCarClass(DRIVERS c)
{
    return c->car_class;
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

void buildDrivers(char *line, int lineNumber, GTree* drivers)
{
    GTree *t = NULL;
    t = drivers;

    char *buff2 = line;
    DRIVERS temp = malloc(sizeof(struct drivers));

    // Get the info
    int id = atoi(strsep(&buff2, ";\n"));
    printf("%d",id);
    char *name = strsep(&buff2, ";\n");
    printf("%s",name);
    struct tm birth_dayst = verifyTime(strsep(&buff2, ";\n"));

    char gender = strsep(&buff2, ";\n")[0];
    printf("%s",gender);
    char *car_class = strsep(&buff2, ";\n");
    printf("%s",car_class);
    char *license_plate = strsep(&buff2, ";\n");
    printf("%s",license_plate);
    char *city = strsep(&buff2, ";\n");
    printf("%s",city);
    struct tm account_creationst = verifyTime(strsep(&buff2, ";\n"));

    char account_status = strsep(&buff2, ";\n")[0]; // verify later

    // verifier
    if (id == 0)
        return;

    int car_class_int = 0;
    if(strcmp(car_class, "green")) car_class_int = 1;
    if(strcmp(car_class, "premium")) car_class_int = 2;
    // Send the info
    temp->id = id;
    temp->name = strdup(name);
    temp->birth_day = birth_dayst;
    temp->gender = gender;
    temp->car_class = car_class_int;
    //printf("%d",temp->car_class);
    temp->license_plate = license_plate;
    temp->city = strdup(city);
    temp->account_creation = account_creationst;
    temp->account_status = account_status;
    g_tree_insert(t, GINT_TO_POINTER(id), temp);
}

void loadDrivers(char *filename, GTree* drivers)
{
    int max_len = 2000;
    char buff[max_len];
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Ficheiro não encontrado: %s \n", filename);
        return;
    }
    fgets(buff, max_len, f);
    int line = 0;
    while (fgets(buff, max_len, f)!=NULL)
    {
        buildDrivers(buff, line, drivers);
        line++;
    }
    fclose(f);
}