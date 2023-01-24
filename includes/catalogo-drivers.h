#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>


typedef struct drivers* DRIVERS;


int getDriversId(DRIVERS c);
char* getDriversName(DRIVERS c);
struct tm getDriversBirthDay(DRIVERS c);
char getDriversGender(DRIVERS c);
char* getDriversCarClass(DRIVERS c);
char* getDriversLicensePlate(DRIVERS c);
char* getDriversCity(DRIVERS c);
struct tm getDriversAccCreation(DRIVERS c);
char getDriversAccountStatus(DRIVERS c);


void buildDrivers(char *line, int lineNumber, GTree* drivers);
void loadDrivers(char *filename, GTree* drivers);

