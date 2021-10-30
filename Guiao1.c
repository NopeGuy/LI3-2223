//Memória da lista arrebenta programa, não chega

#define MAX_BUFFER 4096;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// verificar follower_list com o valor do followers
// verificar following_list(6ยบ campo) com valor do following(9ยบ campo)

typedef struct data
{
    int public_repos, id, followers, public_gists, following, num_linhas;
    char *follower_list[1024], *following_list[1024];
    char *type,*date,*login;

    // falta o "tipo" created_at;
    // falta o "tipo" login (char,ints,"-")
}*Data;

//sanitizeInt
//sanitize char

int *sanitizearray(int followers,char *tempid){
    //se tiver char vai merdar
    int *final = malloc(sizeof(int)*followers);
    tempid ++;
    tempid[strlen(tempid) - 2] = '\0';
    for (int i = 0; i < followers; i++)
    {
        final[i] = atoi(strsep(&tempid, ","));
        printf("%d\n", final[i]);
    }
    return final;
}

int main(){
    //abrir em read mode
    FILE *fr1 = fopen("entrada/users.csv", "r");
    FILE *fr2 = fopen("entrada/commits.csv", "r");
    FILE *fr3 = fopen("entrada/repos.csv", "r");
    //abrir em write mode
    FILE *fw1 = fopen("saida/users-ok.csv", "w+");
    FILE *fw2 = fopen("saida/commits-ok.csv", "w+");
    FILE *fw3 = fopen("saida/repos-ok.csv", "w+");

    char buff[4096]; //buffer

    char *output;
    char *line;
    Data values = malloc(sizeof(struct data)); //array para dar store a valores

    int i=0;
    char *tempid;
    while (fgets(buff, 4096, fr1)){
        output = strdup(buff);

        values->id = atoi(strsep(&output, ";"));
        values->login = strsep(&output, ";");
        values->type = strsep(&output, ";");
        values->date = strsep(&output, ";");
        values->followers = atoi(strsep(&output, ";"));
        
        printf("id - %d\n", values->id);

        line = strsep(&output, ";");

        if(values->followers > 0 && strlen(line)>0)
        {
            tempid = strsep(&line, "\0");
            printf("tempid - %s\n", tempid);
            //sanitizearray não funciona direito
            
            //sanitizearray(values->followers, tempid);
        }

        values->following = atoi(strsep(&output, ";"));
        /*if (values->following > 0)
        {
            tempid = strsep(&line, "\0");
            printf("%s\n", tempid);
            sanitizearray(values->following, tempid);
        }
        */

       strsep(&output, ";");
        values->public_gists = atoi(strsep(&output, ";"));
        values->public_repos = atoi(strsep(&output, ";"));
    }



        
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
