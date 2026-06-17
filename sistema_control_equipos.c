/* ==============================================================================
 * Proyecto    : SistemaControlEquipos
 * Archivo     : sistema_control_equipos.c
 * Descripción : Gestión completa de inventario (Versión Inicial)
 * Autor       : Edwin René Soto González
 * Versión     : 1.0.0
 * Fecha       : 17/06/2026
 * ============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EQUIPOS 100
#define ARCHIVO_DATOS "equipos.dat"

typedef struct {
    char codigo[20];
    char nombre[50];
    char marca[30];
    char responsable[50];
    char estado[20];
    float precio;
} Equipo;

Equipo inventario[MAX_EQUIPOS];
int total_equipos = 0;

int main(void) {
    printf("Sistema de Control de Equipos v1.0.0 iniciado.\n");
    return 0;
}