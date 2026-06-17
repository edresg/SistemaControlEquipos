/* ==============================================================================
 * Proyecto    : SistemaControlEquipos
 * Archivo     : sistema_control_equipos.c
 * Descripción : Gestión de inventario.
 * Autor       : Edwin René Soto González
 * Versión     : 5.0.0 
 * Fecha       : 10/06/2026
 * ============================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EQUIPOS 100
#define ARCHIVO_DATOS "equipos.dat"
#define ARCHIVO_REPORTE "reporte_equipos.txt"

/* Estructura de datos */
typedef struct {
    char codigo[20];
    char nombre[50];
    char marca[30];
    char responsable[50];
    char estado[20]; /* Activo, Inactivo, En reparación */
    float precio;
} Equipo;

/* Variables globales */
Equipo inventario[MAX_EQUIPOS];
int total_equipos = 0;

/* ==============================================================================
 * UTILIDADES DEL SISTEMA
 * ============================================================================== */

void limpiar_pantalla(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void limpiar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void imprimir_listado(void) {
    if (total_equipos == 0) {
        printf("\n⚠️ No hay equipos registrados en el sistema.\n");
        return;
    }

    printf("\n LISTADO DE EQUIPOS DISPONIBLES\n");
    printf("==================================================================================\n");
    printf("| %-8s | %-18s | %-14s | %-19s | %-12s | %-10s |\n", 
           "Código", "Nombre", "Marca", "Responsable", "Estado", "Precio");
    printf("==================================================================================\n");

    for (int i = 0; i < total_equipos; i++) {
        printf("| %-8s | %-18s | %-14s | %-19s | %-12s | $%-9.2f |\n",
               inventario[i].codigo,
               inventario[i].nombre,
               inventario[i].marca,
               inventario[i].responsable,
               inventario[i].estado,
               inventario[i].precio);
    }
    printf("==================================================================================\n");
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

int leer_cadena_opcional(const char *prompt, char *dest, size_t tam) {
    char temp[100];
    printf("%s", prompt);
    fflush(stdout);
    if (fgets(temp, sizeof(temp), stdin)) {
        temp[strcspn(temp, "\n")] = '\0';
        if (strlen(temp) > 0) {
            strncpy(dest, temp, tam - 1);
            dest[tam - 1] = '\0';
            return 1;
        }
    }
    return 0;
}

int existe_codigo(const char *codigo_buscar) {
    for (int i = 0; i < total_equipos; i++) {
        if (strcmp(inventario[i].codigo, codigo_buscar) == 0) {
            return 1;
        }
    }
    return 0;
}

/* ==============================================================================
 * GESTIÓN DE ARCHIVOS
 * ============================================================================== */
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

/* ==============================================================================
 * NUEVA FUNCIÓN: GENERAR REPORTE EN ARCHIVO DE TEXTO
 * ============================================================================== */
void generar_reporte_txt(void) {
    if (total_equipos == 0) {
        printf("\n️ No hay datos para generar el reporte.\n");
        return;
    }

    FILE *fp = fopen(ARCHIVO_REPORTE, "w");
    if (fp == NULL) {
        printf("❌ Error: No se pudo crear el archivo de reporte.\n");
        return;
    }

    fprintf(fp, "================================================================================\n");
    fprintf(fp, "             REPORTE DE INVENTARIO DE EQUIPOS - SISTEMA CONTROL EQUIPOS           \n");
    fprintf(fp, "================================================================================\n\n");
    fprintf(fp, "Total de equipos registrados: %d\n\n", total_equipos);
    
    fprintf(fp, "%-10s %-20s %-15s %-20s %-12s %-10s\n", 
            "CÓDIGO", "NOMBRE", "MARCA", "RESPONSABLE", "ESTADO", "PRECIO");
    fprintf(fp, "--------------------------------------------------------------------------------\n");

    for (int i = 0; i < total_equipos; i++) {
        fprintf(fp, "%-10s %-20s %-15s %-20s %-12s $%-9.2f\n",
                inventario[i].codigo,
                inventario[i].nombre,
                inventario[i].marca,
                inventario[i].responsable,
                inventario[i].estado,
                inventario[i].precio);
    }
    
    fprintf(fp, "--------------------------------------------------------------------------------\n");
    fprintf(fp, "Generado el: 10/06/2026\n");
    fclose(fp);

    printf("\n✅ Reporte generado exitosamente en '%s'.\n", ARCHIVO_REPORTE);
    printf("Presione Enter para continuar..."); getchar();
}

/* ==============================================================================
 * OPERACIONES CRUD
 * ============================================================================== */

void registrar_equipo(void) {
    if (total_equipos >= MAX_EQUIPOS) {
        printf("️ Límite de registros alcanzado.\n");
        return;
    }

    Equipo nuevo;
    char buffer[20];

    printf("\n📝 REGISTRO DE EQUIPO (Validación Estricta)\n");
    printf("─────────────────────────────────────────────\n");

    while (1) {
        leer_cadena_obligatoria("Código del equipo: ", nuevo.codigo, sizeof(nuevo.codigo));
        if (existe_codigo(nuevo.codigo)) {
            printf("   ❌ ERROR: El código '%s' YA EXISTE.\n", nuevo.codigo);
        } else {
            break;
        }
    }

    leer_cadena_obligatoria("Nombre del equipo: ", nuevo.nombre, sizeof(nuevo.nombre));
    leer_cadena_obligatoria("Marca: ", nuevo.marca, sizeof(nuevo.marca));
    leer_cadena_obligatoria("Responsable asignado: ", nuevo.responsable, sizeof(nuevo.responsable));
    leer_cadena_obligatoria("Estado (Activo/Reparación): ", nuevo.estado, sizeof(nuevo.estado));

    while (1) {
        leer_cadena_obligatoria("Precio: ", buffer, sizeof(buffer));
        if (sscanf(buffer, "%f", &nuevo.precio) == 1 && nuevo.precio >= 0) {
            break;
        }
        printf("   ❌ ERROR: Ingrese un precio válido (>= 0).\n");
    }

    inventario[total_equipos] = nuevo;
    total_equipos++;
    guardar_equipos();

    printf("\n✅ Equipo registrado exitosamente.\n");
    printf("Presione Enter para continuar..."); getchar();
}

void mostrar_equipos(void) {
    imprimir_listado();
    if (total_equipos > 0) {
        printf("\nPresione Enter para continuar..."); getchar();
    }
}

void buscar_equipo(void) {
    char codigo[20];
    printf("\n🔍 BUSCAR EQUIPO\n");
    leer_cadena_obligatoria("Código a buscar: ", codigo, sizeof(codigo));

    int encontrado = 0;
    for (int i = 0; i < total_equipos; i++) {
        if (strcmp(inventario[i].codigo, codigo) == 0) {
            printf("\n✅ EQUIPO ENCONTRADO:\n");
            printf("   Código     : %s\n", inventario[i].codigo);
            printf("   Nombre     : %s\n", inventario[i].nombre);
            printf("   Marca      : %s\n", inventario[i].marca);
            printf("   Responsable: %s\n", inventario[i].responsable);
            printf("   Estado     : %s\n", inventario[i].estado);
            printf("   Precio     : $%.2f\n", inventario[i].precio);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) printf(" No se encontró ningún equipo con el código: %s\n", codigo);
    printf("\nPresione Enter para continuar..."); getchar();
}

void modificar_equipo(void) {
    if (total_equipos == 0) {
        printf("\n️ No hay equipos disponibles para modificar.\n");
        return;
    }

    imprimir_listado();

    char codigo[20];
    printf("\n✏️ MODIFICAR EQUIPO\n");
    leer_cadena_obligatoria("Ingrese el CÓDIGO del equipo a modificar: ", codigo, sizeof(codigo));

    for (int i = 0; i < total_equipos; i++) {
        if (strcmp(inventario[i].codigo, codigo) == 0) {
            printf("\n📦 DATOS ACTUALES DEL EQUIPO SELECCIONADO:\n");
            printf("   Código     : %s\n", inventario[i].codigo);
            printf("   Nombre     : %s\n", inventario[i].nombre);
            printf("   Marca      : %s\n", inventario[i].marca);
            printf("   Responsable: %s\n", inventario[i].responsable);
            printf("   Estado     : %s\n", inventario[i].estado);
            printf("   Precio     : $%.2f\n", inventario[i].precio);

            printf("\n¿Desea modificar este equipo? (S/N): ");
            char resp;
            scanf(" %c", &resp);
            limpiar_buffer();

            if (toupper(resp) == 'S') {
                printf("\n--- INGRESE NUEVOS DATOS (Presione Enter para mantener el actual) ---\n");
                printf("   Código: %s (No modificable)\n", inventario[i].codigo);

                leer_cadena_opcional("   Nuevo Nombre      : ", inventario[i].nombre, sizeof(inventario[i].nombre));
                leer_cadena_opcional("   Nueva Marca       : ", inventario[i].marca, sizeof(inventario[i].marca));
                leer_cadena_opcional("   Nuevo Responsable : ", inventario[i].responsable, sizeof(inventario[i].responsable));
                leer_cadena_opcional("   Nuevo Estado      : ", inventario[i].estado, sizeof(inventario[i].estado));

                char buffer_precio[20];
                printf("   Nuevo Precio      : ");
                fflush(stdout);
                if (fgets(buffer_precio, sizeof(buffer_precio), stdin)) {
                    buffer_precio[strcspn(buffer_precio, "\n")] = '\0';
                    float nuevo_precio;
                    if (strlen(buffer_precio) > 0 && sscanf(buffer_precio, "%f", &nuevo_precio) == 1 && nuevo_precio >= 0) {
                        inventario[i].precio = nuevo_precio;
                    }
                }

                guardar_equipos();
                printf("\n✅ Equipo modificado exitosamente.\n");
            } else {
                printf("❌ Operación cancelada.\n");
            }
            break;
        }
    }
    printf("\nPresione Enter para continuar..."); getchar();
}

void eliminar_equipo(void) {
    if (total_equipos == 0) {
        printf("\n⚠️ No hay equipos disponibles para eliminar.\n");
        return;
    }

    imprimir_listado();

    char codigo[20];
    printf("\n🗑️ ELIMINAR EQUIPO\n");
    leer_cadena_obligatoria("Ingrese el CÓDIGO del equipo a eliminar: ", codigo, sizeof(codigo));

    for (int i = 0; i < total_equipos; i++) {
        if (strcmp(inventario[i].codigo, codigo) == 0) {
            printf("\n⚠️ DATOS DEL EQUIPO QUE SERÁ ELIMINADO:\n");
            printf("   Código     : %s\n", inventario[i].codigo);
            printf("   Nombre     : %s\n", inventario[i].nombre);
            printf("   Marca      : %s\n", inventario[i].marca);
            printf("   Responsable: %s\n", inventario[i].responsable);
            printf("   Estado     : %s\n", inventario[i].estado);
            printf("   Precio     : $%.2f\n", inventario[i].precio);

            printf("\n¿Está SEGURO que desea eliminar este equipo permanentemente? (S/N): ");
            char resp;
            scanf(" %c", &resp);
            limpiar_buffer();

            if (toupper(resp) == 'S') {
                for (int j = i; j < total_equipos - 1; j++) {
                    inventario[j] = inventario[j + 1];
                }
                total_equipos--;
                guardar_equipos();
                printf("✅ Equipo eliminado correctamente del inventario.\n");
            } else {
                printf("❌ Eliminación cancelada por el usuario.\n");
            }
            break;
        }
    }
    printf("\nPresione Enter para continuar..."); getchar();
}

/* ==============================================================================
 * MENÚ PRINCIPAL
 * ============================================================================== */
int main(void) {
    int opcion;
    cargar_equipos(); 

    do {
        limpiar_pantalla();
        
        printf("╔══════════════════════════════════════════════════════╗\n");
        printf("║        SISTEMA DE CONTROL DE EQUIPOS (v5.0)          ║\n");
        printf("╠══════════════════════════════════════════════════════╣\n");
        printf("║  1. Registrar equipo                                 ║\n");
        printf("║  2. Mostrar equipos registrados                      ║\n");
        printf("║  3. Buscar equipo por código                         \n");
        printf("║  4. Modificar información de equipo                  ║\n");
        printf("║  5. Eliminar equipo                                  ║\n");
        printf("║  6. Generar reporte en archivo de texto              ║\n");
        printf("║  7. Salir                                            ║\n");
        printf("╚══════════════════════════════════════════════════════╝\n");
        printf("Seleccione una opción: ");

        if (scanf("%d", &opcion) != 1) {
            limpiar_buffer();
            opcion = -1;
        }
        limpiar_buffer();

        switch (opcion) {
            case 1: registrar_equipo(); break;
            case 2: mostrar_equipos(); break;
            case 3: buscar_equipo(); break;
            case 4: modificar_equipo(); break;
            case 5: eliminar_equipo(); break;
            case 6: generar_reporte_txt(); break;
            case 7: printf("\n👋 Saliendo del sistema. ¡Hasta pronto!\n"); break;
            default: printf("❌ Opción no válida. Seleccione del 1 al 7.\n"); getchar(); break;
        }

    } while (opcion != 7);

    return 0;
}