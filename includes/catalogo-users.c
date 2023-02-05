//catalogo-users
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>

#include "../includes/catalogo-users.h"
#include "../includes/constructors.h"      //ver isto
#include "../includes/main.h"

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
    return u->username;
}

char *getName(USER u){
	/*
    char* copy = malloc(sizeof(char)*400000);
    strcpy(copy, u->name);*/
    return strdup(u->name);
}

char getGender(USER u){
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

void buildUsers(char* line, GTree *users) {
    GTree* t = NULL;
    t = users;

    char* buff2 = line;
    USER temp = malloc(sizeof(struct user));


    char* username = strsep(&buff2, ";\n");
    char* name = strsep(&buff2, ";\n");
    
    char gender;
    if (strcmp(strsep(&buff2, ";\n"), "M") == 0)
    {
        gender = 'm';
    } else{
        gender = 'f';
    }
    
    struct tm birth_date = verifyTime(strsep(&buff2, ";\n"));
    struct tm account_creation = verifyTime(strsep(&buff2, ";\n"));
    
    char pay_method;
    char* temp_pay_method = strsep(&buff2, ";\n");
    if (strcmp(temp_pay_method, "cash") == 0)
    {
        pay_method = 'c';
    } else if (strcmp(temp_pay_method, "debit_card") == 0)
    {
        pay_method = 'd';
    } else if(strcmp(temp_pay_method, "credit_card") == 0){
        pay_method = 'r';
    }

    char account_status;
    char* temp_account_status = strsep(&buff2, ";\n");
    if (strcmp(temp_account_status, "active") == 0)
    {
        account_status = 'a';
    } else if(strcmp(temp_account_status, "inactive") == 0){
        account_status = 'i';
    }

    temp->username = strdup(username);
    temp->name = strdup(name);
    temp->gender = gender;
    temp->birth_date = birth_date;
    temp->account_creation = account_creation;
    temp->pay_method = pay_method; //pay_method may be initialized
    temp->account_status = account_status; //account_status may be unitialized

    g_tree_insert(t, temp->username, temp);
}


void loadUsers(char *fileName, GTree* users) {
    int max_len = 2000;
    char buff[max_len];

    FILE *file = fopen(fileName, "r");
    if(file == NULL)
    {
        printf("Ficheiro não encontrado: %s\n", fileName);
        return;
    }

    fgets(buff, max_len, file); //primeira linha
    while(fgets(buff, max_len, file)!=NULL)
    {
        buildUsers(buff, users);
    }

    fclose(file);
}
