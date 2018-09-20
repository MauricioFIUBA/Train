#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Subway.h"

/*printf("LINEA: %c\tESTACION: %s\n", Line, stat->name);*/

size_t NumberLine(FILE **archive)
{
    size_t numberLine = 0;
    char search = '#';
    if( ((*archive) = fopen("Unix_lineas_de_subte.txt","rt")) == NULL)
    {
        fprintf(stderr, "%s\n", ERR);
    }
    while (!feof((*archive)))
    {
        if(search == getc((*archive)))
        {
            numberLine++;
        }
    }
    fclose((*archive));
    return numberLine;
}

void FreeSubway(station_t ***subway, size_t amount)
{
    size_t line;
    station_t *clean, *iteration;
    for (line = 0; line < amount; line++)
    {
        clean = (*subway)[line];
        while(clean)
        {
            iteration = clean->next;
            free(clean);
            clean = iteration;
        }
    }
    free(*subway);
}
void FillSubway(station_t ***subway, FILE **archive,size_t amount)
{
    size_t i;
    int line;
    char letterLine;
    char check = EMPTY;
    (*subway)= (station_t**)malloc(sizeof(station_t*)*amount);
    for (i = 0; i < amount; i++) {
        (*subway)[i]= (station_t*)malloc(sizeof(station_t));
    }
    if( ((*archive) = fopen("Unix_lineas_de_subte.txt","rt")) == NULL)
    {
        fprintf(stderr, "%s\n", ERR);
    }
    else
    {
        for(line = 0;!feof((*archive)); line++)
        {
            if(check == EMPTY) check=getc((*archive));
            if(check == '#')
            {
                fscanf((*archive), "%c", &letterLine);
                printf("%s%c\n", PASL,letterLine);
                while(getc((*archive)) != '\n' && !feof((*archive)));
            }
            check=getc((*archive));
            FillStations(&((*subway)[line]), archive, &check, letterLine);
            printf("%i\n", feof((*archive)));
        }
        fclose((*archive));
    }
}
void FillStations(station_t **subway, FILE **archive, char *check, char letterLine)
{
    station_t *iteration;
    for (iteration = (*subway) ; (*check) != '#' && !feof((*archive)) ; )
    {
        if((*check) == '*')
        {
            fgets(iteration->name, 50, (*archive));
            /*
            UnixCorrection();*/
            printf("%s%s", PASE,iteration->name);
            iteration->line = letterLine;
            iteration->next = (station_t*)malloc(sizeof(station_t));
            iteration = iteration->next;
        }
        (*check)=getc((*archive));
    }
    iteration->next = NULL;
}

station_t* SerchStation(station_t **subway, char line, char* station, size_t amount)
{
    station_t* search;
    size_t iterator;
    for (iterator = 0; iterator < amount && subway[iterator]->line != line; iterator++);
    if(iterator > amount)
    {
        fprintf(stderr, "%s\n", ERR_SEARCH_LINE);
    }
    search = subway[iterator];
    while(search && strcmp(search->name,station))
    {
        search = search->next;

    }

    return search;
}
int main(void)
{
    int amount;
    station_t **subway, *buscado;
    FILE* archive;
    char lineSeek;
    char seek[50];

    amount = NumberLine(&archive);
    printf("%i\n", amount);
    FillSubway(&subway, &archive, amount);
    printf("%s\n", "En que linea del subte esta buscando?:");
    scanf("%c", &lineSeek);
    while(getchar() != '\n');
    printf("%s\n", "Cual es el nombre de la estacion?:");
    fgets(seek, 50,stdin); /*Tengo que arreglar esto O arreglar el flujo de informacion superior*/
    if((buscado = SerchStation(subway, lineSeek, seek, amount)) == NULL)
    {
        fprintf(stderr, "%s\n", "No se pudo encontrar la estacion buscada");
        return EXIT_FAILURE;
    }
    else
    {
        printf("La estacion encontrada es de la linea: %c y tienen de nombre: %s", buscado->line, buscado->name);
    }




    FreeSubway(&subway, amount);
    return EXIT_SUCCESS;
}
