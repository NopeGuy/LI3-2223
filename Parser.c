#define MAX_BUFFER 4096;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data
{
    int public_repos, id, followers, public_gists, following, num_linhas;
    char *follower_list[1024], *following_list[1024];
    char *type, *date, *login;

    // falta o "tipo" created_at;
    // falta o "tipo" login (char,ints,"-")
} * Data;

//sanitizeInt
//sanitize char

int *sanitizearray(int followers, char *tempid)
{
    //se tiver char vai merdar
    int *final = malloc(sizeof(int) * followers);
    tempid++;
    tempid[strlen(tempid) - 2] = '\0';
    for (int i = 0; i < followers; i++)
    {
        final[i] = atoi(strsep(&tempid, ","));
        printf("%d\n", final[i]);
    }
    return final;
}

void sendStruct(Data values, char buff[], FILE *fr1)
{
    char *output, *line, *tempid;
    //em vez de ter while aqui, tem na call da função
    fgets(buff, 4096, fr1);
    output = strdup(buff);

    values->id = atoi(strsep(&output, ";"));
    values->login = strsep(&output, ";");
    values->type = strsep(&output, ";");
    values->date = strsep(&output, ";");
    values->followers = atoi(strsep(&output, ";"));

    line = strsep(&output, ";");

    printf("id - %d\n", values->id);

    if (values->followers > 0 && strlen(line) > 0)
    {
        tempid = strsep(&line, "\0");
        printf("followers - %s\n", tempid);
        sanitizearray(values->followers, tempid);
    }
    values->following = atoi(strsep(&output, ";"));
    line = strsep(&output, ";");

    if (values->following > 0 && strlen(line) > 0)
    {
        tempid = strsep(&line, "\0");
        printf("following - %s\n", tempid);
        sanitizearray(values->following, tempid);
    }
    values->public_gists = atoi(strsep(&output, ";"));
    values->public_repos = atoi(strsep(&output, ";"));
}

int main()
{
    //abrir em read mode
    FILE *fr1 = fopen("entrada/users.csv", "r");
    FILE *fr2 = fopen("entrada/commits.csv", "r");
    FILE *fr3 = fopen("entrada/repos.csv", "r");
    //abrir em write mode
    FILE *fw1 = fopen("saida/users-ok.csv", "w+");
    FILE *fw2 = fopen("saida/commits-ok.csv", "w+");
    FILE *fw3 = fopen("saida/repos-ok.csv", "w+");

    char buff[4096];                           //buffer
    Data values = malloc(sizeof(struct data)); //array para dar store a valores

    //while fr1 != NULL{
    for (int i = 0; i < 40; i++)
    {
        sendStruct(values, buff, fr1);
    }
    //validateStructValues();
    //structToFile();
    //}

    //abrir outros ficheiros
    /*
    while (fgets(buff, 4096, fr2))
    {
        printf("%s\n", buff);
    }
    while (fgets(buff, 4096, fr3))
    {
        printf("%s\n", buff);
    }
    */

    fclose(fr1);
    fclose(fr2);
    fclose(fr3);
    fclose(fw1);
    fclose(fw2);
    fclose(fw3);
}
