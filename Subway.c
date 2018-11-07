#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Subway.h"

/*printf("LINEA: %c\tESTACION: %s\n", Line, stat->name);*/
void SetStation(station_t *station)
{
    station->combination1 = NULL;
    station->combination2 = NULL;
}
size_t NumberLine(FILE **archive)
{
    size_t numberLine = 0;
    char search = SEARCH_LINE;
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
    size_t iteration;
    int line;
    char letterLine;
    char check = EMPTY;
    (*subway)= (station_t**)malloc(sizeof(station_t*)*amount);
    for (iteration = 0; iteration < amount; iteration++)
    {
        (*subway)[iteration]= (station_t*)malloc(sizeof(station_t));
        SetStation((*subway)[iteration]);
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

            if(check == SEARCH_LINE)
            {
                fscanf((*archive), "%c", &letterLine);
                /*printf("%s%c\n", PASL,letterLine);*/
                while(getc((*archive)) != '\n' && !feof((*archive)));
            }
            check=getc((*archive));
            FillStations(&((*subway)[line]), archive, &check, letterLine);
            /*printf("%i\n", feof((*archive)));*/
        }
        fclose((*archive));
    }
}
void FillStations(station_t **subway, FILE **archive, char *check, char letterLine)
{
    station_t *iteration;
    for (iteration = (*subway) ; (*check) != SEARCH_LINE && !feof((*archive)) ; )
    {
        if((*check) == SEARCH_STATION)
        {
            fgets(iteration->name, 50, (*archive));
            /*
            UnixCorrection();*/
            /*printf("%s%s", PASE,iteration->name);*/
            iteration->line = letterLine;
            iteration->next = (station_t*)malloc(sizeof(station_t));
            SetStation(iteration);
            iteration = iteration->next;
        }
        (*check)=getc((*archive));
    }
    iteration->next = NULL;
}

void FillCombination(station_t ***subway,  FILE **archive, size_t amount)
{
    bool_t firstStation = FALSE;
    station_t *iteration;
    size_t itera;
    char check = EMPTY;
    char lineSearch, line;
    char stationSearch[50] = "";
    if( ((*archive) = fopen("Unix_lineas_de_subte.txt","rt")) == NULL)
    {
        fprintf(stderr, "%s\n", ERR);
    }
    else
    {
        while (!feof((*archive)))
        {
            if(check == EMPTY) check=getc((*archive)); /*Si se inicia, check debe agarrar el primer valor*/


            /*Busco La rama que aparece en la linea, en el ejemplo que consitrui el texto esta igual (una detras de otra),
            Pero esto no tiene que ser mandatorio como lo es ahora*/
            if(check == SEARCH_LINE)
            {
                fscanf((*archive), "%c", &line);
                for(itera = 0; itera < amount && line != (*subway)[itera]->line;itera++);
                while(check != '\n' && !feof((*archive))) check = getc((*archive));

                if(itera >= amount)
                {
                    printf("%s\n", "No se encontro la linea pedida");
                }
                check=getc((*archive));
                if(check == '\n')
                {
                    check=getc((*archive));
                }
                iteration = (*subway)[itera];
                firstStation = TRUE;
            }

            if(check == SEARCH_STATION)
            {
                while(check != '\n' && !feof((*archive))) check = getc((*archive));
                while(check == '\n')
                {
                    check=getc((*archive));
                }
                if(!firstStation)
                {
                    iteration = iteration->next;
                }
                firstStation = FALSE;
            }

            if(check == SEARCH_COMBINATION_STATION && !feof((*archive)))
            {
                fgets(stationSearch, 50, (*archive));
                check=getc((*archive));

                if(check == SEARCH_COMBINATION_LINE)
                {
                    lineSearch =  getc((*archive));
                    while(check != '\n' && !feof((*archive))) check = getc((*archive));
                    while(check == '\n')
                    {
                        check=getc((*archive));
                    }
                }
                else
                {
                    fprintf(stderr, "%s\n", "ERROR FATAL: Falta la linea de subte de la combinacion");
                }
                if(iteration->combination1 == NULL)
                {
                    iteration->combination1 = SearchStation((*subway), lineSearch, stationSearch, amount);
                }
                else if(iteration->combination2 == NULL)
                {
                    iteration->combination2 = SearchStation((*subway), lineSearch, stationSearch, amount);
                }
                else
                {
                    printf("%s, LINEA: %c. ESTACION: %s, COMBINACION 1: %s. COMBINACION 2: %s\n", "Error: El programa no esta preparado para que una estacion tiene mas de 2 combinaciones", iteration->line, iteration->name, iteration->combination1->name, iteration->combination2->name);
                }
            }
        }
    }


    fclose((*archive));
}


station_t* SearchStation(station_t **subway, char line, char* station, size_t amount)
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

void AskForStation(station_t ***subway)
{

    /*char lineSeek;
    char seek[50];*/

    /******Busqueda de una estacion y prueba de SearchStation (SOLO ES UNA PRUEBA)*****/
    /*printf("%s\n", "En que linea del subte esta buscando?:");
    scanf("%c", &lineSeek);
    while(getchar() != '\n');
    printf("%s\n", "Cual es el nombre de la estacion?:");
    fgets(seek, 50,stdin);
    if((buscado = SearchStation(subway, lineSeek, seek, amount)) == NULL)
    {
        fprintf(stderr, "%s\n", "No se pudo encontrar la estacion buscada");
        return EXIT_FAILURE;
    }
    else
    {
        printf("La estacion encontrada es de la linea: %c y tienen de nombre: %s", buscado->line, buscado->name);
    }*/
    /*************************************************************/
    /*FindShortWay(subway); Para el futuro*/
}
int main(void)
{
    int amount;
    station_t **subway/*, *buscado*/;
    FILE* archive;

    amount = NumberLine(&archive);
    FillSubway(&subway, &archive, amount);

    FillCombination(&subway, &archive, amount);

    /*BusquedaDeCaminoMasCorto()*/




    FreeSubway(&subway, amount);
    return EXIT_SUCCESS;
}
