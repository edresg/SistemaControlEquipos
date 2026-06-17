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

void cargar_equipos(void) {
    FILE *fp = fopen(ARCHIVO_DATOS, "rb");
    if (fp == NULL) return;
    total_equipos = fread(inventario, sizeof(Equipo), MAX_EQUIPOS, fp);
    fclose(fp);
}

void guardar_equipos(void) {
    FILE *fp = fopen(ARCHIVO_DATOS, "wb");
    if (fp != NULL) {
        fwrite(inventario, sizeof(Equipo), total_equipos, fp);
        fclose(fp);
    }
}

void leer_cadena_obligatoria(const char *prompt, char *dest, size_t tam) {
    while (1) {
        printf("%s", prompt);
        fflush(stdout);
        if (fgets(dest, tam, stdin)) {
            dest[strcspn(dest, "\n")] = '\0';
            if (strlen(dest) > 0) return;
        }
        printf("   ❌ ERROR: Este campo es obligatorio.\n");
    }
}

int existe_codigo(const char *codigo_buscar) {
    for (int i = 0; i < total_equipos; i++) {
        if (strcmp(inventario[i].codigo, codigo_buscar) == 0) return 1;
    }
    return 0;
}

void registrar_equipo(void) {
    if (total_equipos >= MAX_EQUIPOS) { printf("⚠️ Límite de registros alcanzado.\n"); return; }
    Equipo nuevo;
    char buffer[20];
    printf("\n📝 REGISTRO DE EQUIPO (Validación Estricta)\n");
    
    while (1) {
        leer_cadena_obligatoria("Código del equipo: ", nuevo.codigo, sizeof(nuevo.codigo));
        if (existe_codigo(nuevo.codigo)) printf("   ❌ ERROR: El código '%s' YA EXISTE.\n", nuevo.codigo);
        else break;
    }
    leer_cadena_obligatoria("Nombre del equipo: ", nuevo.nombre, sizeof(nuevo.nombre));
    leer_cadena_obligatoria("Marca: ", nuevo.marca, sizeof(nuevo.marca));
    leer_cadena_obligatoria("Responsable asignado: ", nuevo.responsable, sizeof(nuevo.responsable));
    leer_cadena_obligatoria("Estado (Activo/Reparación): ", nuevo.estado, sizeof(nuevo.estado));

    while (1) {
        leer_cadena_obligatoria("Precio: ", buffer, sizeof(buffer));
        if (sscanf(buffer, "%f", &nuevo.precio) == 1 && nuevo.precio >= 0) break;
        printf("   ❌ ERROR: Ingrese un precio válido (>= 0).\n");
    }

    inventario[total_equipos] = nuevo;
    total_equipos++;
    guardar_equipos();
    printf("\n✅ Equipo registrado exitosamente.\nPresione Enter para continuar..."); getchar();
}

void cargar_equipos(void) {
    FILE *fp = fopen(ARCHIVO_DATOS, "rb");
    if (fp == NULL) return;
    total_equipos = fread(inventario, sizeof(Equipo), MAX_EQUIPOS, fp);
    fclose(fp);
}

void guardar_equipos(void) {
    FILE *fp = fopen(ARCHIVO_DATOS, "wb");
    if (fp != NULL) {
        fwrite(inventario, sizeof(Equipo), total_equipos, fp);
        fclose(fp);
    }
}

void leer_cadena_obligatoria(const char *prompt, char *dest, size_t tam) {
    while (1) {
        printf("%s", prompt);
        fflush(stdout);
        if (fgets(dest, tam, stdin)) {
            dest[strcspn(dest, "\n")] = '\0';
            if (strlen(dest) > 0) return;
        }
        printf("   ❌ ERROR: Este campo es obligatorio.\n");
    }
}

int existe_codigo(const char *codigo_buscar) {
    for (int i = 0; i < total_equipos; i++) {
        if (strcmp(inventario[i].codigo, codigo_buscar) == 0) return 1;
    }
    return 0;
}

void registrar_equipo(void) {
    if (total_equipos >= MAX_EQUIPOS) { printf("⚠️ Límite de registros alcanzado.\n"); return; }
    Equipo nuevo;
    char buffer[20];
    printf("\n📝 REGISTRO DE EQUIPO (Validación Estricta)\n");
    
    while (1) {
        leer_cadena_obligatoria("Código del equipo: ", nuevo.codigo, sizeof(nuevo.codigo));
        if (existe_codigo(nuevo.codigo)) printf("   ❌ ERROR: El código '%s' YA EXISTE.\n", nuevo.codigo);
        else break;
    }
    leer_cadena_obligatoria("Nombre del equipo: ", nuevo.nombre, sizeof(nuevo.nombre));
    leer_cadena_obligatoria("Marca: ", nuevo.marca, sizeof(nuevo.marca));
    leer_cadena_obligatoria("Responsable asignado: ", nuevo.responsable, sizeof(nuevo.responsable));
    leer_cadena_obligatoria("Estado (Activo/Reparación): ", nuevo.estado, sizeof(nuevo.estado));

    while (1) {
        leer_cadena_obligatoria("Precio: ", buffer, sizeof(buffer));
        if (sscanf(buffer, "%f", &nuevo.precio) == 1 && nuevo.precio >= 0) break;
        printf("   ❌ ERROR: Ingrese un precio válido (>= 0).\n");
    }

    inventario[total_equipos] = nuevo;
    total_equipos++;
    guardar_equipos();
    printf("\n✅ Equipo registrado exitosamente.\nPresione Enter para continuar..."); getchar();
}

void imprimir_listado(void) {
    if (total_equipos == 0) { printf("\n⚠️ No hay equipos registrados en el sistema.\n"); return; }
    printf("\n LISTADO DE EQUIPOS DISPONIBLES\n");
    printf("==================================================================================\n");
    printf("| %-8s | %-18s | %-14s | %-19s | %-12s | %-10s |\n", "Código", "Nombre", "Marca", "Responsable", "Estado", "Precio");
    printf("==================================================================================\n");
    for (int i = 0; i < total_equipos; i++) {
        printf("| %-8s | %-18s | %-14s | %-19s | %-12s | $%-9.2f |\n",
               inventario[i].codigo, inventario[i].nombre, inventario[i].marca,
               inventario[i].responsable, inventario[i].estado, inventario[i].precio);
    }
    printf("==================================================================================\n");
}

void mostrar_equipos(void) {
    imprimir_listado();
    if (total_equipos > 0) { printf("\nPresione Enter para continuar..."); getchar(); }
}

void buscar_equipo(void) {
    char codigo[20];
    printf("\n🔍 BUSCAR EQUIPO\n");
    leer_cadena_obligatoria("Código a buscar: ", codigo, sizeof(codigo));
    int encontrado = 0;
    for (int i = 0; i < total_equipos; i++) {
        if (strcmp(inventario[i].codigo, codigo) == 0) {
            printf("\n✅ EQUIPO ENCONTRADO:\n   Código: %s\n   Nombre: %s\n   Marca: %s\n   Responsable: %s\n   Estado: %s\n   Precio: $%.2f\n",
                   inventario[i].codigo, inventario[i].nombre, inventario[i].marca,
                   inventario[i].responsable, inventario[i].estado, inventario[i].precio);
            encontrado = 1; break;
        }
    }
    if (!encontrado) printf("❌ No se encontró ningún equipo con el código: %s\n", codigo);
    printf("\nPresione Enter para continuar..."); getchar();
}

int leer_cadena_opcional(const char *prompt, char *dest, size_t tam) {
    char temp[100];
    printf("%s", prompt); fflush(stdout);
    if (fgets(temp, sizeof(temp), stdin)) {
        temp[strcspn(temp, "\n")] = '\0';
        if (strlen(temp) > 0) { strncpy(dest, temp, tam - 1); dest[tam - 1] = '\0'; return 1; }
    }
    return 0;
}

void modificar_equipo(void) {
    if (total_equipos == 0) { printf("\n⚠️ No hay equipos disponibles.\n"); return; }
    imprimir_listado();
    char codigo[20];
    printf("\n✏️ MODIFICAR EQUIPO\n");
    leer_cadena_obligatoria("Ingrese el CÓDIGO del equipo a modificar: ", codigo, sizeof(codigo));
    for (int i = 0; i < total_equipos; i++) {
        if (strcmp(inventario[i].codigo, codigo) == 0) {
            printf("\n¿Desea modificar este equipo? (S/N): ");
            char resp; scanf(" %c", &resp); limpiar_buffer();
            if (toupper(resp) == 'S') {
                leer_cadena_opcional("   Nuevo Nombre      : ", inventario[i].nombre, sizeof(inventario[i].nombre));
                leer_cadena_opcional("   Nueva Marca       : ", inventario[i].marca, sizeof(inventario[i].marca));
                leer_cadena_opcional("   Nuevo Responsable : ", inventario[i].responsable, sizeof(inventario[i].responsable));
                leer_cadena_opcional("   Nuevo Estado      : ", inventario[i].estado, sizeof(inventario[i].estado));
                char buffer_precio[20];
                printf("   Nuevo Precio      : "); fflush(stdout);
                if (fgets(buffer_precio, sizeof(buffer_precio), stdin)) {
                    buffer_precio[strcspn(buffer_precio, "\n")] = '\0';
                    float nuevo_precio;
                    if (strlen(buffer_precio) > 0 && sscanf(buffer_precio, "%f", &nuevo_precio) == 1 && nuevo_precio >= 0) {
                        inventario[i].precio = nuevo_precio;
                    }
                }
                guardar_equipos();
                printf("\n✅ Equipo modificado exitosamente.\n");
            } else { printf("❌ Operación cancelada.\n"); }
            break;
        }
    }
    printf("\nPresione Enter para continuar..."); getchar();
}

void eliminar_equipo(void) {
    if (total_equipos == 0) { printf("\n⚠️ No hay equipos disponibles.\n"); return; }
    imprimir_listado();
    char codigo[20];
    printf("\n🗑️ ELIMINAR EQUIPO\n");
    leer_cadena_obligatoria("Ingrese el CÓDIGO del equipo a eliminar: ", codigo, sizeof(codigo));
    for (int i = 0; i < total_equipos; i++) {
        if (strcmp(inventario[i].codigo, codigo) == 0) {
            printf("\n¿Está SEGURO que desea eliminar este equipo permanentemente? (S/N): ");
            char resp; scanf(" %c", &resp); limpiar_buffer();
            if (toupper(resp) == 'S') {
                for (int j = i; j < total_equipos - 1; j++) inventario[j] = inventario[j + 1];
                total_equipos--;
                guardar_equipos();
                printf("✅ Equipo eliminado correctamente.\n");
            } else { printf("❌ Eliminación cancelada.\n"); }
            break;
        }
    }
    printf("\nPresione Enter para continuar..."); getchar();
}