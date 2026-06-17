/* ... (código anterior) ... */

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