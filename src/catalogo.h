#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <glib.h>



typedef struct catalogo *CATALOGO;

GTree* getUsers(CATALOGO cat);
GTree* getRides(CATALOGO cat);
GTree* getDrivers(CATALOGO cat);
void setUsers(CATALOGO cat, GTree* t);
void setRides(CATALOGO cat, GTree* t);
void setDrivers(CATALOGO cat, GTree* t);
CATALOGO iniciarCatalogo();