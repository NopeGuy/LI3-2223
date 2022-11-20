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
    int n_cidade;
    int n_Basic;
    int n_Green;
    int n_Premium;
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

void getCidade(CATALOGO cat){
    return cat->n_cidade;
}
void getBasic(CATALOGO cat){
    return cat->n_Basic;
}
void getGreen(CATALOGO cat){
    return cat->n_Green;
}
void getPremium(CATALOGO cat){
    return cat->n_Premium;
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

void setCidade(CATALOGO cat,int value){
    cat->n_cidade= value;
}
void setBasic(CATALOGO cat,int value){
    cat->n_Basic= value;
}
void setGreen(CATALOGO cat,int value){
    cat->n_Green= value;
}
void setPremium(CATALOGO cat,int value){
    cat->n_Premium= value;
}