//catalogo-rides
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>

#include "../includes/catalogo-rides.h"
#include "../includes/constructors.h"      //ver isto
#include "../includes/main.h"

//id;date;driver;user;city;distance;score_user;score_driver;tip;comment

struct ride {
    int id;
    struct tm date;
    int driver; //id condutor
    char *user; //nome do utilizador
    char *city; //nome da cidade
    double distance; //distancia da viagem arredondada a 3 casas decimais
    double score_user; //score do utilizador
    double score_driver; //score do condutor
    double tip; // gorjeta que o utlizador deixa
    char *comment;
    int lnNumber; //linha da rides.csv
};

//getters


int getRidesid(RIDES a){
    return a->id;
}

struct tm getRidesDate(RIDES a){
    return a->date;
}

int getRidesDriver(RIDES a){
    return a->driver;
}

char *getRidesUser(RIDES a){
    return a->user;
}

char *getRidesCity(RIDES a){
    return a->city;
}

double getRidesDistance(RIDES a){
    return a->distance;
}

double getRidesScoreUser(RIDES a){
    return a->score_user;
}

double getRidesScoreDriver(RIDES a){
    return a->score_driver;
}

double getRidesTip(RIDES a){
    return a->tip;
}

char *getRidesComment(RIDES a){
    return strdup(a->comment);
}


void buildRides (char* line, GTree *rides, int nLinha){
GTree* t = NULL;
t = rides;                          
char* buffR = line;
RIDES temp = malloc(sizeof(struct ride));
//struct tm date = {0};

int id_temp = atoi(strsep(&buffR,";\n"));
struct tm date_temp = verifyTime(strsep(&buffR, ";\n"));
int driver_temp = atoi(strsep(&buffR,";\n"));
char *user_temp = strsep(&buffR,";\n");
char *city_temp = strsep(&buffR,";\n");
double distance_temp = atof(strsep(&buffR,";\n"));
double score_user_temp = atof(strsep(&buffR,";\n"));
double score_driver_temp = atof(strsep(&buffR,";\n"));
double tip_temp = atof(strsep(&buffR,";\n"));

//verificações
if(id_temp == 0) return;
if(driver_temp == 0) return;
if(user_temp == 0) return;
if(city_temp == 0) return;
if(date_temp.tm_year==0) return;

//Passar para tree temporária
temp->id = id_temp;
temp->date = date_temp;
temp->driver = driver_temp;
temp->user = strdup(user_temp);
temp->city = strdup(city_temp);
temp->distance = distance_temp;
temp->score_user = score_user_temp;
temp->score_driver = score_driver_temp;
temp->tip = tip_temp;
//temp->comment = malloc(sizeof(char)*400000);
temp->lnNumber = nLinha;
//inserir na glib

g_tree_insert(t, GINT_TO_POINTER(id_temp), temp);
}

void loadRides(char* filename, GTree* rides){
    int max_len = 2000;
    char buff[max_len];
    FILE *f = fopen(filename, "r");
    if(f == NULL){
        printf("Ficheiro não encontrado: %s\n", filename);
        return;
    }
    fgets(buff,max_len,f); //primeira linha
    int line=0;
    while(fgets(buff,max_len, f)!=NULL){
        buildRides(buff,rides,line);
        line++;
    }
    fclose(f);
}

