#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <glib.h>



typedef struct catalogo *CATALOGO;


//Getters

GTree* getUsers(CATALOGO cat);
GTree* getRides(CATALOGO cat);
GTree* getDrivers(CATALOGO cat);

//Setters

void setUsers(CATALOGO cat, GTree* t);
void setRides(CATALOGO cat, GTree* t);

//Funcoes

CATALOGO iniciarCatalogo();