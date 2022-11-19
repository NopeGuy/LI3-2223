//catalogo-users
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>

#include "catalogo-rides.h"
#include "constructors.h"
#include "catalogo.h"        //ver isto
#include "main.h"

struct user {
	char* username;
	char* name;
	// f for femenine, m for masculine
	char gender;
	struct tm birth_date;
	struct tm account_creation;
	// c for cash, d for debit card, r for credit card
	char pay_method;
	// a for active i for inactive
	char account_status;
};

char *getUsername(USER u){
    return strdup(u->username);
}

char *getName(USER u){
	/*
    char* copy = malloc(sizeof(char)*400000);
    strcpy(copy, u->name);*/
    return strdup(u->name);
}

char gender(USER u){
	return u->gender;
}

struct tm getBirth_date(USER u){
	return u->birth_date;
}


struct tm getAccount_creation(USER u){
	return u->birth_date;
}

char getPay_method(USER u){
	return u->pay_method;
}

char getAccount_status(USER u){
	return u->account_status;
}


USER buildUserWithoutTree(char* line, int id_user) {
    char* buff2 = line;
    char* id = strsep(&buff2, ";\n");
    int id_actual = atoi(id);

    if(id_user != id_actual){
        return NULL;
    }

    USER temp = malloc(sizeof(struct user));

    char* name = strsep(&buff2, ";\n");
    temp->login = malloc(sizeof(char)*strlen(name));
    temp->typeUser = genTypeUser(strsep(&buff2, ";\n"));

    strcpy(temp->login, name);
    temp->id = id_user;

    return temp;
}


// falta acabar build users
void buildUsers(char* line, CATALOGO cat) {
    GTree* t = NULL;
    t = getUsers(cat);

    char* buff2 = line;
    USER temp = malloc(sizeof(struct user));

    char* id = strsep(&buff2, ";\n");
    char* name = strsep(&buff2, ";\n");
    int id_user = atoi(id);
    //int* id_key = GINT_TO_POINTER(id_user);




    //temp->login = malloc(sizeof(char)*strlen(name));

    temp->typeUser = genTypeUser(strsep(&buff2, ";\n"));

    //strcpy(temp->login, name);
    temp->id = id_user;


    struct tm data = verifyTime(strsep(&buff2, ";\n"));
    temp->created_at = data;
    if(id_user < 0 || temp->typeUser == -1 || data.tm_mday == 0){
        free(temp);
        return;
    }

    if(temp->typeUser == 1)
        setNumUsers(cat, getNumUsers(cat)+1);
    if(temp->typeUser == 2)
        setNumBots(cat, getNumBots(cat)+1);
    if(temp->typeUser == 3)
        setNumOrganizations(cat, getNumOrganizations(cat)+1);


    g_tree_insert(t, toIntAsterix(id_user), temp);
}

USER loadCompleteUSER(char* filename, int id_user){
    int max_len = 400000;
    int count = 0;
    char buff[max_len];

    FILE *f = fopen(filename, "r");
    if(f == NULL){
        printf("Ficheiro não encontrado: %s\n", filename);
        return NULL;
    }
    char line[400000]; /* or other suitable maximum line size */
    fgets(line, sizeof line, f);
    while (fgets(line, sizeof line, f) != NULL) /* read a line */
    {
        USER u = buildUserWithoutTree(line, id_user);
        if(u != NULL)
        {
            fclose(f);
            return u;
        }
    }
    fclose(f);
}

void loadUsers(char *fileName, CATALOGO cat) {
    int max_len = 400000;
    char buff[max_len];

    FILE *file = fopen(fileName, "r");
    if(file == NULL)
    {
        printf("Ficheiro não encontrado: %s\n", fileName);
        return;
    }

    fgets(buff, max_len, file);
    while(fgets(buff, max_len, file))
    {
        buildUsers(buff, cat);
    }

    fclose(file);
}
