#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <glib.h>
#include "catalogo.h"

struct catalogo
{
    GTree* users;
    GTree* drivers;
    GTree* rides;
// int numOfX;
// float averageX;

};

CATALOGO iniciarCatalogo(){
    CATALOGO c = malloc(sizeof(struct catalogo));
    c->drivers = NULL;
    c->users = NULL;
    c->rides = NULL;
    return c;
}

GTree* getUsers(CATALOGO cat){
    return cat->users;
}
GTree* getDrivers(CATALOGO cat){
    return cat->drivers;
}
GTree* getRep(CATALOGO cat){
    return cat->rides;
}

void setUsers(CATALOGO cat, GTree* t){
    cat->users = t;
}
void setDrivers(CATALOGO cat, GTree* t){
    cat->drivers = t;
}
void setRep(CATALOGO cat, GTree* t){
    cat->rides = t;
}