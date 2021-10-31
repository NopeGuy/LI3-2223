#define MAX_BUFFER 4096;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct data
{
    int public_repos, id, followers, public_gists, following, num_linhas;
    int follower_list[1024], following_list[1024];
    char *date, *login;
    enum type
    {
        Bot,
        Organization,
        User
    } type;

    // falta o "tipo" created_at;
    // falta o "tipo" login (char,ints,"-")
} * Data;

//sanitizeInt
//sanitize char

int *sanitizearray(int follow, char *tempid)
{
    //se tiver char vai merdar
    int *final = malloc(sizeof(int) * follow);
    tempid++;
    tempid[strlen(tempid) - 2] = '\0';
    for (int i = 0; i < follow; i++)
    {
        final[i] = atoi(strsep(&tempid, ","));
        if (final[i] < 0)
            return 0;
    }
    return final;
}

int sendStruct(Data values, char buff[], FILE *fr1)
{
    char *temptype, *output, *line, *tempid;
    fgets(buff, 4096, fr1);
    output = strdup(buff);

    values->id = atoi(strsep(&output, ";"));
    if (values->id < 0)
        return 0;
    printf("id - %d\n", values->id);

    values->login = strsep(&output, ";");

    //verificação e obtenção type
    temptype = strsep(&output, ";");
    if (strcmp(temptype, "Organization") == 0)
    {
        values->type = Organization;
    }
    else if ((strcmp(temptype, "User")) == 0)
    {
        values->type = User;
    }
    else if ((strcmp(temptype, "Bot")) == 0)
    {
        values->type = Bot;
    }
    else
        return 0;

    char *timetype = strsep(&output, ";");
    int year, month, day, hour, minute, second;
    if (strlen(timetype) == 19)
    {
        if (sscanf(timetype, "%4d-%2d-%2d %2d:%2d:%2d", &year, &month, &day, &hour, &minute, &second) != EOF)
        {
            if (year <= 2005 && month <= 4 && day <= 7)
            {
                if (2005 < year || year < 2020 || month > 0 || month < 13 || day > 0 || day < 32 || hour >= 0 || hour < 24 || minute >= 0 || minute < 61 || second >= 0 || second < 61)
                {
                    values->date = timetype;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    values->followers = atoi(strsep(&output, ";"));
    if (values->followers < 0)
        return 0;

    line = strsep(&output, ";");

    //enviar followers para a lista
    if (values->followers > 0 && strlen(line) > 0)
    {
        tempid = strsep(&line, "\0");
        int *followers = sanitizearray(values->followers, tempid);
        for (int j = 0; j < values->followers; j++)
        {
            values->follower_list[j] = followers[j];
            printf("follower - %d\n", values->follower_list[j]);
        }
    }
    values->following = atoi(strsep(&output, ";"));
    if (values->following < 0)
        return 0;

    line = strsep(&output, ";");

    //enviar following para a lista
    if (values->following > 0 && strlen(line) > 0)
    {
        tempid = strsep(&line, "\0");
        int *following = sanitizearray(values->following, tempid);
        for (int k = 0; k < values->following; k++)
        {
            values->following_list[k] = following[k];
            printf("following - %d\n", values->following_list[k]);
        }
    }
    if (values->public_gists < 0)
        return 0;
    values->public_gists = atoi(strsep(&output, ";"));

    if (values->public_repos < 0)
        return 0;
    values->public_repos = atoi(strsep(&output, ";"));
    /*
    if (validateStruct)
    {
        fputs(buff, fw1);
    }
    */
    return 1;
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
    for (int i = 0; i < 100000; i++)
    {
        if (sendStruct(values, buff, fr1))
        {
            fputs(buff, fw1);
        }
        memset(values, 0, sizeof(values));
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
