# 🖥️ Sistema de Control de Equipos

## 📋 Descripción
El **Sistema de Control de Equipos** es una aplicación de consola desarrollada en lenguaje C, diseñada para la gestión integral, segura y eficiente de inventarios. El sistema permite realizar operaciones CRUD (Crear, Leer, Actualizar, Eliminar) sobre un registro de equipos, garantizando la integridad de los datos mediante validaciones estrictas en tiempo real y previniendo la duplicidad de registros. 

Además, cuenta con mecanismos de persistencia de datos en archivos binarios y un módulo dedicado a la generación de reportes en formato de texto para facilitar la auditoría y el respaldo de la información.

---

## ✨ Características Principales
- **Gestión Completa (CRUD)**: Registro, visualización, búsqueda, modificación y eliminación de equipos.
- **Validación Estricta**: 
  - Campos obligatorios no pueden quedar vacíos.
  - Prevención de registros con códigos de equipo duplicados.
  - Validación de tipos de datos (ej. el precio debe ser un número flotante >= 0).
- **Persistencia de Datos**: La información se guarda y carga automáticamente desde un archivo binario (`equipos.dat`), evitando la pérdida de datos al cerrar el programa.
- **Generación de Reportes**: Exporta el inventario actual a un archivo de texto legible (`reporte_equipos.txt`) con formato tabular.
- **Interfaz de Usuario Limpia**: Menú interactivo en consola con retroalimentación visual clara (uso de emojis, tablas alineadas y mensajes de error descriptivos).

---

## ⚙️ Requisitos Previos
Para compilar y ejecutar este proyecto, necesitas:
- Un sistema operativo: **Windows**, **Linux** o **macOS**.
- Un compilador de C instalado, preferiblemente **GCC** (MinGW en Windows).
- Una terminal o símbolo del sistema.

---

## 🚀 Instalación y Compilación

Sigue estos pasos para poner en marcha el sistema en tu entorno local:

1. **Clona o descarga el repositorio** en tu computadora.
2. Abre tu terminal o símbolo del sistema y navega hasta la carpeta del proyecto:
   ```bash
   cd ruta/a/tu/carpeta/SistemaControlEquipos