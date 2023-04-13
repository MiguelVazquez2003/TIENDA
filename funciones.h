#ifndef FUNCIONES_H
#define FUNCIONES_H
typedef struct
{
    int clave;
    char nombre[100];
    float precio;
    int cantidad;
    struct
    {
        int dia;
        int mes;
        int anio;
    } fecha_ingreso, fecha_caducidad;
    char nombre_proveedor[50];
    char telefono_proveedor[20];
    char correo_proveedor[100];
} Producto;

void VentasdelDia();
void AgregarProducto();
void ImprimirProductos();
int buscar_clave_en_archivo(int clave, const char *nombre_archivo);
void EliminarProducto();
int comparar_fechas(const void *p1, const void *p2);
void generarticket();
int leer_productos_archivo(char *nombre_archivo, Producto *productos);
void imprimir_fechas_caducidad_ordenadas();
void modificarProductoCantidad(int clave_producto_a_modificar, int cantidad);
void modificarProducto2();
void modificarProducto3();
void ImprimirVentasDia();
void ImprimirOrdenesCompra();
int validar_correo(char *correo_proveedor);
void imprimir_cantidad_disponible_ordenadas(char nombre_archivo[]);
int comparar_cantidad_disponible(const void *p1, const void *p2);
void guardar_productos_ordenados_por_cantidad(char nombre_archivo[]);
void imprimir_clave_ordenadas(char nombre_archivo[]);
int comparar_clave(const void *a, const void *b);
void guardar_productos_ordenados_por_clave_en_archivo_binario(char nombre_archivo[]);

#endif
