#ifndef _SUBWAY_H_
#define _SUBWAY_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct station{
    char line;
    char name[50];
    struct station *next;
} station_t;

#define EMPTY '0'
#define ERR "Error: No se pudo abrir el archivo."
#define ERR_SEARCH_LINE "Error: No se pudo encontrar la linea desada"
#define ERR_SEARCH_STATION "Error: No se pudo encontrar la estacion desada"
/*Constantes de soporte*/
#define PASL "PASO POR ACA LA LINEA: "
#define PASE "PASO POR ACA LA ESTACION: "
/**********************/

size_t NumberLine(FILE **);
void FreeSubway(station_t ***, size_t);
void FillSubway(station_t ***, FILE **, size_t);
void FillStations(station_t**, FILE**, char*, char);
station_t* SerchStation(station_t **, char, char*,int);
#endif
