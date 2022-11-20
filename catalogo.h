#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <glib.h>



typedef struct catalogo *CATALOGO;


//Getters


//Main

GTree* getUsers(CATALOGO cat);
GTree* getRides(CATALOGO cat);
GTree* getDrivers(CATALOGO cat);

//Q4

void getCidade(CATALOGO cat);
void getBasic(CATALOGO cat);
void getGreen(CATALOGO cat);
void getPremium(CATALOGO cat);


//Setters


//Main

void setUsers(CATALOGO cat, GTree* t);
void setRides(CATALOGO cat, GTree* t);

//Q4
void setCidade(CATALOGO cat,int value);
void setDrivers(CATALOGO cat, GTree* t);
void setUsers(CATALOGO cat, GTree* t);
void setDrivers(CATALOGO cat, GTree* t);
void setRep(CATALOGO cat, GTree* t);

//Funcoes

CATALOGO iniciarCatalogo();