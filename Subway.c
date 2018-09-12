#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct station{
    char line;
    char name[50];
    struct station *next;
} station_t;
#define EMPTY '0'
#define  ERR "Error: No se pudo abrir el archivo."
/*Constantes de soporte*/
#define PASL "PASO POR ACA LA LINEA: "
#define PASE "PASO POR ACA LA ESTACION: "
/**********************/

void FreeStations(station_t ***subway)
{
    int line;
    station_t *clean, *iteration;
    for (line = 0; line < 2; line++)
    {
        clean = (*subway)[line];
        while(clean)
        {
            iteration = clean->next;
            free(clean);
            clean = iteration;
        }
    }
}
void FillStations(station_t ***subway, FILE **archive)
{
    size_t i;
    int line;
    char Line;
    char check = EMPTY;
    station_t *iteration;
    (*subway)= (station_t**)malloc(sizeof(station_t*)*2);
    for (i = 0; i < 2; i++) {
        (*subway)[i]= (station_t*)malloc(sizeof(station_t));
    }
    if( ((*archive) = fopen("archivo.txt","rt")) == NULL)
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
                fscanf((*archive), "%c", &Line);
                printf("%s%c\n", PASL,Line);
                while(getc((*archive)) != '\n' && !feof((*archive)));
            }
            check=getc((*archive));
            for (iteration = (*subway)[line] ; check != '#' && !feof((*archive)) ; )
            {
                if(check == '*')
                {
                    fgets((*subway)[line]->name, 50, (*archive));

                    printf("%s%s", PASE,(*subway)[line]->name);
                    iteration->next = (station_t*)malloc(sizeof(station_t));
                    iteration = iteration->next;
                }
                check=getc((*archive));
            }
            iteration->next = NULL;
            /*printf("LINEA: %c\tESTACION: %s\n", Line, stat->name);*/
            printf("%i\n", feof((*archive)));
        }
    }
}
int main(void)
{
    station_t **subway;
    FILE* archive;

    FillStations(&subway, &archive);
    FreeStations(&subway);
    fclose(archive);

    return EXIT_SUCCESS;
}
