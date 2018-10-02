#ifndef _SUBWAY_H_
#define _SUBWAY_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct station{
    char line;
    char name[50];
    struct station *next;
    struct station *combination1;
    struct station *combination2;
} station_t;
typedef enum{
    FALSE,
    TRUE
}bool_t;

#define EMPTY '0'
#define ERR "Error: No se pudo abrir el archivo."
#define ERR_SEARCH_LINE "Error: No se pudo encontrar la linea desada"
#define ERR_SEARCH_STATION "Error: No se pudo encontrar la estacion desada"
/*Constantes de soporte*/
#define PASL "PASO POR ACA LA LINEA: "
#define PASE "PASO POR ACA LA ESTACION: "
/**********************/

/*Constantes de busqueda*/
#define SEARCH_LINE '#'
#define SEARCH_STATION '*'
#define SEARCH_COMBINATION_LINE '+'
#define SEARCH_COMBINATION_STATION '@'

size_t NumberLine(FILE **);
void SetStation(station_t *);
void FreeSubway(station_t ***, size_t);
void FillSubway(station_t ***, FILE **, size_t);
void FillStations(station_t**, FILE**, char*, char);
void FillCombination(station_t ***,  FILE **, size_t);
station_t* SearchStation(station_t **, char, char*, size_t);
#endif
