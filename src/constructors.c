#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <glib.h>
#include <ctype.h>
#include <time.h>
#include <malloc.h>
#include <sys/resource.h>

char* intToString(int i){
    char* buff = malloc(sizeof(char)*20000);
    sprintf(buff, "%d", i);
    return buff;
}

int stringNotInArray(char* arr[], int iMaxArr, char* palavra){
    for(int i = 0; i<iMaxArr; i++)
        if(strcmp(palavra, arr[i]) == 0)
            return 1;
    return 0;
}

char* removeXChars(char* str, int removeN){
    char* newString = malloc(sizeof(char)*400000);
    int nI = 0;
    for(int i = 0;i<strlen(str);i++){
        if(i >= removeN){
            newString[nI++] = str[i];
        }
    }

    free(str);
    return newString;
}

char* toUppercase(char* buff){
    char * name;
    name = strtok(buff,"");

    // Convert to upper case
    char *s = name;
    while (*s) {
        *s = toupper((unsigned char) *s);
        s++;
    }
}

struct tm verifyTime (char* str)
{
//     //nn/nn/nnnn
//     //printf("%s", str);
//     time_t rawtime;
//     struct tm * c;
//     struct tm tempo = {0};
//     strptime(str, "%Y-%m-%d %H:%M:%S", &tempo);

//     if(strlen(str) != 19) tempo.tm_mday = 0;

//     // tempo.tm_year = tempo.tm_year+1900;
//     // tempo.tm_mon = tempo.tm_mon+1;


//     time ( &rawtime );
//     c = localtime ( &rawtime );
//     //   c->tm_year = c->tm_year+1900;

//     //printf("%d-%d-%d %d:%d:%d\n", c->tm_year, c->tm_mon, c->tm_mday, c->tm_hour, c->tm_min, c->tm_sec);

//     if(tempo.tm_year == 2005 && tempo.tm_mon < 4) tempo.tm_mday = 0;
//     if(tempo.tm_year == 2005 && tempo.tm_mon == 4 && tempo.tm_mday < 7) tempo.tm_mday = 0;
//     if(tempo.tm_year > c->tm_year || tempo.tm_year < 2005) tempo.tm_mday = 0;
//     if(tempo.tm_year == c->tm_year && tempo.tm_mon > c->tm_mon) tempo.tm_mday = 0;
//     if(tempo.tm_year == c->tm_year && tempo.tm_mon == c->tm_mon && tempo.tm_mday > c->tm_mday) tempo.tm_mday = 0;
//     if(tempo.tm_year == c->tm_year && tempo.tm_mon == c->tm_mon && tempo.tm_mday == c->tm_mday
//        && tempo.tm_hour > c->tm_hour) tempo.tm_mday = 0;
//     if(tempo.tm_year == c->tm_year && tempo.tm_mon == c->tm_mon && tempo.tm_mday == c->tm_mday
//        && tempo.tm_hour == c->tm_hour && tempo.tm_min > c->tm_min) tempo.tm_mday = 0;



//     return tempo;

}

int asterixToInt(int* i){
    return *i;
}

int* toIntAsterix(int i){
    int* ret = malloc(sizeof(int*));
    *ret = i;
    return ret;
}

void saveToFile(char* fileName, char* write, int firstTime) {
    FILE *f = fopen(fileName, "a");
    if(firstTime == 1) f = fopen(fileName, "w");

    if (f == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro: %s\n", fileName);
        return;
    }

    fprintf(f, "%s", write);

    fclose(f);

    printf("%s alterado com sucesso !\n", fileName);
}

void writeLineToFile(char* fileName, char* write, int firstTime) {
   
    FILE *f = fopen(fileName, "a");
    if(firstTime == 1) f = fopen(fileName, "w");

    if (f == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro: %s\n", fileName);
        return;
    }

    fprintf(f, "%s", write);
    fclose(f);

}
