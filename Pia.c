#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // para la función sleep
#define true 1
#define false 0

bool eliminacion_previa = false; // Variable global
int n=0;

typedef struct {
    int clave;
    char nombre[100];
    float precio;
    int cantidad;
    struct {
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
int buscar_clave_en_archivo(int clave, const char* nombre_archivo);
void EliminarProducto();
void ModificarProducto();
void ReporteCompleto(Producto productos[], int n,int clave_productos[]);
int comparar_fechas(const void *p1, const void *p2);
void ImprimirProductosCaducidad(Producto productos[], int n,int clave_productos[]);
void ImprimirProductosCaducidadOrdenados(Producto productos[], int n,int clave_productos[]);
void generarticket();
int leer_productos_archivo(char *nombre_archivo, Producto *productos);
void imprimir_fechas_caducidad_ordenadas();
void modificarProductoCantidad(int clave_producto_a_modificar, int cantidad);
void modificarProducto2();
void modificarProducto3();
void ImprimirVentasDia();

int main() {
    	
    
    Producto productos[50];
    int i;
    int opcion=0;
    int opcion1;
    int opcion2;
    int opcion3;
    int clave_productos[50];
    // Llenar la matriz clave_productos con las claves de los productos ordenadas de forma ascendente
    for (i = 0; i < n; i++) {
        clave_productos[i] = productos[i].clave;
    }
    
    
    
    do {
        printf("\t\t\t1.INVENTARIO\t\t\t2.VENTA DEL DIA\t\t\t3.Listado\n");
        printf("\n\t\t\tIngresa una opcion por favor: ");
        scanf("%d",&opcion);
        switch(opcion){
            case 1:
                system("cls");
                do {
                    printf("1.Agregar Producto\n2.Eliminar Producto\n3.Modificar Producto\n4.Reporte\n5.Salir\n");
                    printf("\t\t\tIngresa una opcion por favor: \n");
                    scanf("%d",&opcion1);
                    switch(opcion1){
                        case 1:
                            system("cls");
                            AgregarProducto();
                            system("pause");
                            system("cls");
                            break;
                        case 2:
                            system("cls"); 
                            EliminarProducto();
                            system("pause");
                            system("cls"); 
                            break;
                        case 3:
                            system("cls");
                           // ModificarProducto();
                           modificarProducto2();
                            system("pause");
                            system("cls");
                            break;
                        case 4:
                        	system("cls");
                        	do{
                        	printf("\n1.Reporte Completo.\n2.Reporte por Caducidad.\n3.Reporte por Ordenes de Compra.\n4.Reporte de ventas del dia.\n5.Reporte de Ventas del Dia\n6.Salir");
                        	printf("\nIngresa una opcion: ");
                        	scanf("%d",&opcion2);
                        	switch(opcion2){
                        		case 1:
                        		
                        		system("cls");
                        		ImprimirProductos();
                        		system("cls");
                        		
                        		
                        			break;
                        			case 2:
                        			system("cls");
									imprimir_fechas_caducidad_ordenadas("productos.txt");

                        			
                        			system("cls");
                        				break;
                        			case 3:
							 
    		
    									break;

                        					case 4:
                        						ImprimirVentasDia(); 
                        						break;
                        						case 5:
                        							break;
                        							case 6:
                        								break;
                        							default: 
                        							break;
							}
							}while(opcion2!=6);
							system("cls");
                            break;
                        case 5: 
                            break;
                        default:
                            break;
                    }
                } while (opcion1!=5);
                system("cls");
                break;
            case 2:
            	system("cls");
            do{
            	printf("\n1.Generar una compra.\n2.Ordenes de compra.\n3.Reporte de ventas del dia\n\n4.Salir");
            	printf("\nIngrese una opcion: ");
            	scanf("%d",&opcion3);
            	switch(opcion3){
            			case 1:
            		system("cls");
            		generarticket();
            		break;
            		case 2:
            			modificarProducto3();
            			break;
            			case 3:
            		VentasdelDia();
            				break;
            				default:
            					break;
				}
            
			}while(opcion3!=4);
            	system("cls");
                break;
            case 3:
               	
                
                break;
            case 4:
                break;
            default:
                break;
        }
    } while (opcion != 4);
     
    return 0;
}

void AgregarProducto() {
    FILE *fp;
    fp = fopen("productos.txt", "a");  // Se abre en modo "a" (append) para agregar al final del archivo existente
    Producto producto;
    int validar_clave;

    printf("\nIngrese los datos para el producto:\n");


      do {
        printf("\nClave: ");
        scanf("%d", &producto.clave);

        // Validar si la clave ya existe en el archivo
        int linea = buscar_clave_en_archivo(producto.clave, "productos.txt");
        if (linea != -1) {
            printf("Ya existe un producto con esa clave en la linea %d del archivo. Intente de nuevo.\n", linea);
        } else {
            break;
        }
    } while (1);
	
	getchar();
    printf("\nNombre: ");
    fgets(producto.nombre,100, stdin);
	producto.nombre[strcspn(producto.nombre, "\n")] = 0;
	
	
    do {
        printf("\nPrecio: ");
        if (scanf("%f", &producto.precio) != 1 || producto.precio <= 0) {
            printf("Debes ingresar un precio mayor que cero.\n");
        }
    } while (producto.precio <= 0);

    do {
        printf("\nCantidad: ");
        if (scanf("%d", &producto.cantidad) != 1 || producto.cantidad <= 0) {
            printf("Debes ingresar una cantidad mayor que cero.\n");
        }
    } while (producto.cantidad <= 0);

    printf("\nFecha de ingreso (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &producto.fecha_ingreso.dia, &producto.fecha_ingreso.mes, &producto.fecha_ingreso.anio);

    printf("\nFecha de caducidad (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &producto.fecha_caducidad.dia, &producto.fecha_caducidad.mes, &producto.fecha_caducidad.anio);
    
	getchar();
	
   printf("\nNombre del proveedor: ");
  fgets(producto.nombre_proveedor, sizeof(producto.nombre_proveedor), stdin);
	producto.nombre_proveedor[strcspn(producto.nombre_proveedor, "\n")] = 0;

    
    printf("\nTelefono del proveedor: ");
    scanf("%s", producto.telefono_proveedor);

    printf("\nCorreo del proveedor: ");
    scanf("%s", producto.correo_proveedor);
	

   fprintf(fp, "Clave: %d,\tNombre: %s,\tPrecio: %.2f,\tCantidad: %d,\tFecha de ingreso: %d/%d/%d,\tFecha de caducidad: %d/%d/%d,\tNombre del proveedor: %s,\tTelefono del proveedor: %s,\tCorreo del proveedor: %s\n",
        producto.clave, producto.nombre, producto.precio, producto.cantidad,
        producto.fecha_ingreso.dia, producto.fecha_ingreso.mes, producto.fecha_ingreso.anio,
        producto.fecha_caducidad.dia, producto.fecha_caducidad.mes, producto.fecha_caducidad.anio,
        producto.nombre_proveedor, producto.telefono_proveedor, producto.correo_proveedor);

printf("\nProducto agregado exitosamente.\n\n\n");
    fclose(fp);
    sleep(3);
}

void ModificarProducto() {
    FILE* archivo = fopen("productos.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    int clave_producto_a_modificar, encontrado = 0;
    printf("Ingrese la clave del producto a modificar: ");
    scanf("%d", &clave_producto_a_modificar);

    int linea_producto_a_modificar = buscar_clave_en_archivo(clave_producto_a_modificar, "productos.txt");

    if (linea_producto_a_modificar != -1) {
        FILE* archivo_temporal = fopen("productos_temp.txt", "w");
        if (archivo_temporal == NULL) {
            printf("Error al crear archivo temporal.\n");
            return;
        }
        char linea[500];
        int linea_actual = 1;
        while (fgets(linea, sizeof(linea), archivo)) {
            if (linea_actual == linea_producto_a_modificar) {
                encontrado = 1;
                Producto producto;
                sscanf(linea, "Clave: %d,\tNombre: %[^,],\tPrecio: %f,\tCantidad: %d,\tFecha de ingreso: %d/%d/%d,\tFecha de caducidad: %d/%d/%d,\tNombre del proveedor: %[^\t],\tTelefono del proveedor: %s,\tCorreo del proveedor: %s",
                       &producto.clave, producto.nombre, &producto.precio, &producto.cantidad,
                       &producto.fecha_ingreso.dia, &producto.fecha_ingreso.mes, &producto.fecha_ingreso.anio,
                       &producto.fecha_caducidad.dia, &producto.fecha_caducidad.mes, &producto.fecha_caducidad.anio,
                       producto.nombre_proveedor, producto.telefono_proveedor, producto.correo_proveedor);
                       
                       
                producto.precio=producto.precio;       
                fflush(stdin);
                printf("Ingresa el nuevo telefono del proveedor: ");
                scanf("%s",&producto.telefono_proveedor);
                printf("Ingresa el nuevo correo del proveedor: ");
                scanf("%s",&producto.correo_proveedor);
                fflush(stdin);
                printf("Ingrese la nueva cantidad: ");
                scanf("%d", &producto.cantidad);
                printf("Ingrese el nuevo nombre del proveedor: ");
                fflush(stdin);
                fgets(producto.nombre_proveedor, sizeof(producto.nombre_proveedor), stdin);
                producto.nombre_proveedor[strcspn(producto.nombre_proveedor, "\n")] = 0;
                fprintf(archivo_temporal, "Clave: %d,\tNombre: %s,\tPrecio: %.2f,\tCantidad: %d,\tFecha de ingreso: %d/%d/%d,\tFecha de caducidad: %d/%d/%d,\tNombre del proveedor: %s,\tTelefono del proveedor: %s,\tCorreo del proveedor: %s\n",
                        producto.clave, producto.nombre, producto.precio, producto.cantidad,
                        producto.fecha_ingreso.dia, producto.fecha_ingreso.mes, producto.fecha_ingreso.anio,
                        producto.fecha_caducidad.dia, producto.fecha_caducidad.mes, producto.fecha_caducidad.anio,
                        producto.nombre_proveedor, producto.telefono_proveedor, producto.correo_proveedor);
                printf("Producto modificado exitosamente.\n");
            } else {
                fprintf(archivo_temporal, "%s", linea);
            }
            linea_actual++;
        }

        fclose(archivo);
        fclose(archivo_temporal);

        remove("productos.txt");
        rename("productos_temp.txt", "productos.txt");
    }
}

void generarticket() {
    char respuesta;
    int i, j;
    int num_articulos;
    int clave_producto;
    int cantidad_venta;
    float precio_venta;
    float precio_total = 0;
    // Obtener información del producto a partir de la clave
    Producto productos[50];
    printf("¿Cuántos artículos deseas agregar al ticket?: ");
    scanf("%d", &num_articulos);
    FILE* archivo_productos = fopen("productos.txt", "r");
    if (archivo_productos == NULL) {
        printf("Error al abrir el archivo de productos.\n");
        return;
    }
    int num_productos = leer_productos_archivo("productos.txt", productos);
    fclose(archivo_productos);

    FILE* archivo_ticket = fopen("tickets.txt", "a");
    if (archivo_ticket == NULL) {
        printf("Error al abrir el archivo de tickets.\n");
        return;
    }

    for (j = 0; j < num_articulos; j++) {
        printf("Artículo #%d\n", j+1);
        printf("Ingresa la clave del producto: ");
        scanf("%d", &clave_producto);
        int indice_producto = -1;
        for (i = 0; i < num_productos; i++) {
            if (productos[i].clave == clave_producto) {
                indice_producto = i;
                break;
            }
        }
        if (indice_producto == -1) {
            printf("No se encontró el producto con clave %d.\n", clave_producto);
            return;
        }
        printf("Ingresa la cantidad: ");
        scanf("%d", &cantidad_venta);
        if (cantidad_venta <= 0 || cantidad_venta > productos[indice_producto].cantidad) {
    printf("La cantidad ingresada no es válida.\n");
    return;
}

        // Calcular precio de venta
        precio_venta = productos[indice_producto].precio * 0.3+productos[indice_producto].precio;
        precio_total = precio_total + precio_venta * cantidad_venta;
        // Actualizar cantidad de producto en el array
        productos[indice_producto].cantidad = (productos[indice_producto].cantidad - cantidad_venta);
     	printf("%d\n",productos[indice_producto].cantidad);   
        fprintf(archivo_ticket, "Clave del producto: %d,\tNombre del producto: %s,\tCantidad vendida: %d,\tPrecio de venta: %.2f,",
                productos[indice_producto].clave, productos[indice_producto].nombre, cantidad_venta, precio_venta);
       
    }

    

    // Actualizar cantidad de producto en el archivo
archivo_productos = fopen("productos.txt", "w");
if (archivo_productos == NULL) {
printf("Error al abrir el archivo de productos.\n");
return;
}

for (i = 0; i < num_productos; i++) {
/*if (productos[i].clave == clave_producto) {
productos[i].cantidad -= cantidad_venta; // Restar cantidad vendida
}*/
fprintf(archivo_productos, "Clave: %d,\tNombre: %s,\tPrecio: %.2f,\tCantidad: %d,\tFecha de ingreso: %d/%d/%d,\tFecha de caducidad: %d/%d/%d,\tNombre del proveedor: %s,\tTelefono del proveedor: %s,\tCorreo del proveedor: %s\n",
productos[i].clave, productos[i].nombre, productos[i].precio,
productos[i].cantidad, productos[i].fecha_ingreso.dia,
productos[i].fecha_ingreso.mes, productos[i].fecha_ingreso.anio,
productos[i].fecha_caducidad.dia, productos[i].fecha_caducidad.mes,
productos[i].fecha_caducidad.anio, productos[i].nombre_proveedor,
productos[i].telefono_proveedor, productos[i].correo_proveedor);
}
fclose(archivo_productos);
// Generar ticket de venta
time_t now = time(NULL);
struct tm* t = localtime(&now);
char fecha_actual[80];
strftime(fecha_actual, 80, "%d/%m/%Y %H:%M:%S", t);

// Generar ticket de venta

fprintf(archivo_ticket, "\tTotal a pagar: $%.2f,", precio_total);
fprintf(archivo_ticket, "\tFecha de venta: %s\n", fecha_actual);
fclose(archivo_ticket);


printf("Venta realizada con éxito.\n");
}



int buscar_clave_en_archivo(int clave, const char* nombre_archivo) {
    FILE* archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return -1;
    }
    
    char linea[500];
    int i = 0;
    int encontrado = 0;
    while (fgets(linea, sizeof(linea), archivo)) {
        int clave_actual;
        sscanf(linea, "Clave: %d,", &clave_actual);
        if (clave_actual == clave) {
            encontrado = 1;
            break;
        }
        i++;
    }
    
    fclose(archivo);
    
    if (encontrado) {
        return i + 1;
    } else {
        printf("La clave %d no se encontro en el archivo.\n", clave);
        return -1;
    }
}



void EliminarProducto() {
    FILE* archivo = fopen("productos.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    int clave_producto_a_eliminar, encontrado = 0;
    printf("Ingrese la clave del producto a eliminar: ");
    scanf("%d", &clave_producto_a_eliminar);

    int linea_producto_a_eliminar = buscar_clave_en_archivo(clave_producto_a_eliminar, "productos.txt");

    if (linea_producto_a_eliminar != -1) {
        FILE* archivo_temporal = fopen("productos_temp.txt", "w");
        if (archivo_temporal == NULL) {
            printf("Error al crear archivo temporal.\n");
            return;
        }
        char linea[1000];
        int linea_actual = 1;
        while (fgets(linea, sizeof(linea), archivo)) {
            if (linea_actual == linea_producto_a_eliminar) {
                encontrado = 1;
            } else {
                fprintf(archivo_temporal, "%s", linea);
            }
            linea_actual++;
        }

        fclose(archivo);
        fclose(archivo_temporal);
        remove("productos.txt");
        rename("productos_temp.txt", "productos.txt");

        if (encontrado) {
            printf("El producto ha sido eliminado exitosamente.\n");
        } else {
            printf("El producto con la clave %d no se encontró en el inventario.\n", clave_producto_a_eliminar);
        }
    } else {
        printf("El producto con la clave %d no se encontró en el inventario.\n", clave_producto_a_eliminar);
    }
}



void ImprimirProductosCaducidad(Producto productos[], int n,int clave_productos[]) {
	int i;
	
	printf("\nClave\tNombre\tFecha Caducidad\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%s\t%d/ %d/ %d\n",
           productos[i].clave,productos[i].nombre,productos[i].fecha_caducidad.dia, productos[i].fecha_caducidad.mes, productos[i].fecha_caducidad.anio
               );
           }
           sleep(5);
}




int comparar_fechas(const void *p1, const void *p2) {
    Producto *prod1 = (Producto*)p1;
    Producto *prod2 = (Producto*)p2;
    
    if (prod1->fecha_caducidad.anio != prod2->fecha_caducidad.anio) {
        return prod1->fecha_caducidad.anio - prod2->fecha_caducidad.anio;
    }
    if (prod1->fecha_caducidad.mes != prod2->fecha_caducidad.mes) {
        return prod1->fecha_caducidad.mes - prod2->fecha_caducidad.mes;
    }
    return prod1->fecha_caducidad.dia - prod2->fecha_caducidad.dia;
}

void ImprimirProductosCaducidadOrdenados(Producto productos[], int n,int clave_productos[]) {
	int i;
	qsort(productos, n, sizeof(Producto), comparar_fechas);
	printf("\n\n\t\t\tProductos ordenados por caducidad\n\n");
    printf("\nClave\tNombre\tFecha Caducidad\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%s\t%d/%d/%d\n",
               productos[i].clave, productos[i].nombre, 
               productos[i].fecha_caducidad.dia, productos[i].fecha_caducidad.mes, productos[i].fecha_caducidad.anio
               );
           }
           sleep(5);
}





void ImprimirProductos() {
	FILE *fp;
	fp = fopen("productos.txt", "r");  // Se abre en modo "r" read.
    printf("\n\n\t\t\tTodos los productos\n\n");
    printf("%-6s %-12s %-8s %-8s %-16s %-16s %-20s\n", "Clave", "Nombre", "Precio", "Cantidad", "Fecha Ingreso", "Fecha Caducidad", "Proveedor");
    
    char buffer[2000]; // Buffer para leer cada línea del archivo
    while (fgets(buffer, sizeof(buffer), fp)) {
        Producto producto;
        sscanf(buffer, "Clave: %d,\tNombre: %[^,],\tPrecio: %f,\tCantidad: %d,\tFecha de ingreso: %d/%d/%d,\tFecha de caducidad: %d/%d/%d,\tNombre del proveedor: %[^,],\tTelefono del proveedor: %[0-9],\tCorreo del proveedor: %[^\n]",
               &producto.clave, producto.nombre, &producto.precio, &producto.cantidad,
               &producto.fecha_ingreso.dia, &producto.fecha_ingreso.mes, &producto.fecha_ingreso.anio,
               &producto.fecha_caducidad.dia, &producto.fecha_caducidad.mes, &producto.fecha_caducidad.anio,
               producto.nombre_proveedor, producto.telefono_proveedor, producto.correo_proveedor);
        
        printf("%-6d %-12s $%-8.2f %-8d %02d/%02d/%4d\t %02d/%02d/%4d \t%-20s\n",
            producto.clave, producto.nombre, producto.precio, producto.cantidad,
            producto.fecha_ingreso.dia, producto.fecha_ingreso.mes, producto.fecha_ingreso.anio,
            producto.fecha_caducidad.dia, producto.fecha_caducidad.mes, producto.fecha_caducidad.anio,
            producto.nombre_proveedor);
    }
    
    sleep(5);
    fclose(fp);
}


int leer_productos_archivo(char nombre_archivo[], Producto productos[]) {
    FILE* archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        printf("Error al abrir el archivo\n");
        return -1;
    }
    
    int i = 0;
    char buffer[1000];
    while (fgets(buffer, sizeof(buffer), archivo)) {
        Producto producto;
        int result = sscanf(buffer, "Clave: %d,\tNombre: %[^,],\tPrecio: %f,\tCantidad: %d,\tFecha de ingreso: %d/%d/%d,\tFecha de caducidad: %d/%d/%d,\tNombre del proveedor: %[^,],\tTelefono del proveedor: %[0-9],\tCorreo del proveedor: %[^\n]",
               &producto.clave, producto.nombre, &producto.precio, &producto.cantidad,
               &producto.fecha_ingreso.dia, &producto.fecha_ingreso.mes, &producto.fecha_ingreso.anio,
               &producto.fecha_caducidad.dia, &producto.fecha_caducidad.mes, &producto.fecha_caducidad.anio,
               producto.nombre_proveedor, producto.telefono_proveedor, producto.correo_proveedor);
        
        if (result != 13) {
            printf("Error de formato en la linea: %s", buffer);
            continue;
        }
        
        productos[i++] = producto;
    }
    
    fclose(archivo);
    return i;
    
}



void imprimir_fechas_caducidad_ordenadas(char nombre_archivo[]) {
	int i;
    FILE* archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        printf("Error al abrir el archivo\n");
        return;
    }
    
    // Leer todos los productos del archivo y almacenarlos en un arreglo
    Producto productos[50];
    int num_productos = leer_productos_archivo(nombre_archivo, productos);
    if (num_productos == -1) {
        printf("Error al leer los productos del archivo\n");
        fclose(archivo);
        return;
    }
    
    fclose(archivo);
    printf("Numero de productos leidos: %d\n", num_productos);
    // Ordenar el arreglo de productos por fecha de caducidad
    qsort(productos, num_productos, sizeof(Producto), comparar_fechas);
    
    // Imprimir las fechas de caducidad ordenadas
    	printf("\n\n\t\t\tProductos ordenados por caducidad\n\n");
    printf("\nClave\tNombre\tFecha Caducidad\n");
    for (i = 0; i < num_productos; i++) {
        printf("%d\t%s\t%d/%d/%d\n",
               productos[i].clave, productos[i].nombre, 
               productos[i].fecha_caducidad.dia, productos[i].fecha_caducidad.mes, productos[i].fecha_caducidad.anio
               );
           }
           sleep(5);
   
    
    
}

void modificarProducto2() {
    int clave,i;
    printf("Ingrese la clave del producto que desea modificar: ");
    scanf("%d", &clave);
    getchar(); // Consumir el salto de línea después del scanf

    char nombre_archivo[] = "productos.txt";
    int indice = buscar_clave_en_archivo(clave, nombre_archivo);
    if (indice == -1) {
        return;
    }

    Producto productos[50];
    int num_productos = leer_productos_archivo(nombre_archivo, productos);

    Producto producto_modificado = productos[indice - 1];

    printf("Ingrese el nuevo nombre del proveedor: ");
    fgets(producto_modificado.nombre_proveedor, sizeof(producto_modificado.nombre_proveedor), stdin);
    producto_modificado.nombre_proveedor[strcspn(producto_modificado.nombre_proveedor, "\n")] = '\0';

    printf("Ingrese el nuevo telefono del proveedor: ");
    fgets(producto_modificado.telefono_proveedor, sizeof(producto_modificado.telefono_proveedor), stdin);
    producto_modificado.telefono_proveedor[strcspn(producto_modificado.telefono_proveedor, "\n")] = '\0';

    printf("Ingrese el nuevo correo del proveedor: ");
    fgets(producto_modificado.correo_proveedor, sizeof(producto_modificado.correo_proveedor), stdin);
    producto_modificado.correo_proveedor[strcspn(producto_modificado.correo_proveedor, "\n")] = '\0';

    printf("Ingrese la cantidad de productos que llegan: ");
    scanf("%d", &producto_modificado.cantidad);
    getchar(); // Consumir el salto de línea después del scanf
    producto_modificado.cantidad += productos[indice - 1].cantidad;

    productos[indice - 1] = producto_modificado;

    FILE* archivo = fopen(nombre_archivo, "w");
    if (!archivo) {
        printf("Error al abrir el archivo\n");
        return;
    }

    for (i = 0; i < num_productos; i++) {
        fprintf(archivo, "Clave: %d,\tNombre: %s,\tPrecio: %.2f,\tCantidad: %d,\tFecha de ingreso: %d/%d/%d,\tFecha de caducidad: %d/%d/%d,\tNombre del proveedor: %s,\tTelefono del proveedor: %s,\tCorreo del proveedor: %s\n",
                    productos[i].clave, productos[i].nombre, productos[i].precio,
                    productos[i].cantidad, productos[i].fecha_ingreso.dia, productos[i].fecha_ingreso.mes, productos[i].fecha_ingreso.anio,
                    productos[i].fecha_caducidad.dia, productos[i].fecha_caducidad.mes, productos[i].fecha_caducidad.anio,
                    productos[i].nombre_proveedor, productos[i].telefono_proveedor, productos[i].correo_proveedor);
    }

    fclose(archivo);

    printf("El producto con clave %d ha sido modificado exitosamente.\n", clave);
}


void modificarProducto3() {
int clave,i;
printf("Ingrese la clave del producto que desea modificar: ");
scanf("%d", &clave);
getchar(); // Consumir el salto de línea después del scanf


char nombre_archivo[] = "productos.txt";
int indice = buscar_clave_en_archivo(clave, nombre_archivo);
if (indice == -1) {
    return;
}

Producto productos[50];
int num_productos = leer_productos_archivo(nombre_archivo, productos);

Producto producto_modificado = productos[indice - 1];

printf("Ingrese el nuevo nombre del proveedor: ");
fgets(producto_modificado.nombre_proveedor, sizeof(producto_modificado.nombre_proveedor), stdin);
producto_modificado.nombre_proveedor[strcspn(producto_modificado.nombre_proveedor, "\n")] = '\0';

printf("Ingrese el nuevo telefono del proveedor: ");
fgets(producto_modificado.telefono_proveedor, sizeof(producto_modificado.telefono_proveedor), stdin);
producto_modificado.telefono_proveedor[strcspn(producto_modificado.telefono_proveedor, "\n")] = '\0';

printf("Ingrese el nuevo correo del proveedor: ");
fgets(producto_modificado.correo_proveedor, sizeof(producto_modificado.correo_proveedor), stdin);
producto_modificado.correo_proveedor[strcspn(producto_modificado.correo_proveedor, "\n")] = '\0';

printf("Ingrese la cantidad de productos que llegan: ");
scanf("%d", &producto_modificado.cantidad);
getchar(); // Consumir el salto de línea después del scanf
producto_modificado.cantidad += productos[indice - 1].cantidad;

productos[indice - 1] = producto_modificado;

FILE* archivo = fopen(nombre_archivo, "w");
if (!archivo) {
    printf("Error al abrir el archivo\n");
    return;
}

for (i = 0; i < num_productos; i++) {
    fprintf(archivo, "Clave: %d,\tNombre: %s,\tPrecio: %.2f,\tCantidad: %d,\tFecha de ingreso: %d/%d/%d,\tFecha de caducidad: %d/%d/%d,\tNombre del proveedor: %s,\tTelefono del proveedor: %s,\tCorreo del proveedor: %s\n",
                productos[i].clave, productos[i].nombre, productos[i].precio,
                productos[i].cantidad, productos[i].fecha_ingreso.dia, productos[i].fecha_ingreso.mes, productos[i].fecha_ingreso.anio,
                productos[i].fecha_caducidad.dia, productos[i].fecha_caducidad.mes, productos[i].fecha_caducidad.anio,
                productos[i].nombre_proveedor, productos[i].telefono_proveedor, productos[i].correo_proveedor);
}

fclose(archivo);

FILE* orden_archivo = fopen("OrdendeCompra.txt", "a");
if (!orden_archivo) {
    printf("Error al abrir el archivo\n");
    return;
}
time_t now = time(NULL);
    struct tm* t = localtime(&now);
    char fecha_actual[80];
    strftime(fecha_actual, 80, "%d/%m/%Y %H:%M:%S", t);
    
fprintf(orden_archivo, "Fecha de la orden: %s,\tNombre del producto: %s,\tClave: %d,\tCantidad Ordenada: %d,\tNombre del proveedor: %s,\tTelefono del proveedor: %s,\tCorreo del proveedor: %s\n",
        fecha_actual,producto_modificado.nombre, producto_modificado.clave,producto_modificado.cantidad, producto_modificado.nombre_proveedor, producto_modificado.telefono_proveedor, producto_modificado.correo_proveedor);

fclose(orden_archivo);
}



void VentasdelDia() {
    FILE* archivo = fopen("Ventas_Dia.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    time_t tiempo = time(0);
    struct tm* tlocal = localtime(&tiempo);
    char fecha[128];
    strftime(fecha, 128, "%d/%m/%Y %H:%M:%S", tlocal);
    fprintf(archivo, "Ventas del dia %s:\n", fecha);

    FILE* tickets = fopen("tickets.txt", "r");
    if (tickets == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    char linea[1024];
    char* resultado = fgets(linea, 1024, tickets); // leer la primera línea
    while (resultado != NULL) {
        fprintf(archivo, "%s", linea);
		resultado = fgets(linea, 1024, tickets); // leer la siguiente línea

        }
    
    fclose(tickets);
    fclose(archivo);
    printf("Las ventas del dia han sido guardadas en el archivo Ventas_Dia.txt\n");
}

void ImprimirVentasDia() {
    FILE* archivo = fopen("Ventas_Dia.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    char linea[1024];
    while (fgets(linea, 1024, archivo) != NULL) {
        printf("%s", linea);
    }
    fclose(archivo);
}









