#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h> // para la función sleep
#define true 1
#define false 0

bool eliminacion_previa = false; // Variable global
int n=0;

typedef struct {
    int clave;
    char nombre[50];
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

void AgregarProducto(Producto productos[], int *n,int clave_productos[]);
void ImprimirProductos(Producto productos[], int n,int clave_productos[]);
int busqueda_secuencial(int a[], int dato, int n);
void EliminarProducto(Producto productos[], int *n,int clave_productos[]);
void ModificarProducto(Producto productos[], int n,int clave_productos[]);
void ReporteCompleto(Producto productos[], int n,int clave_productos[]);
int comparar_fechas(const void *p1, const void *p2);
void ImprimirProductosCaducidad(Producto productos[], int n,int clave_productos[]);
void ImprimirProductosCaducidadOrdenados(Producto productos[], int n,int clave_productos[]);
void generarTicket(Producto productos[], int n,int clave_productos[]);


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
                            AgregarProducto(productos,&n,clave_productos);
                            system("pause");
                            system("cls");
                            break;
                        case 2:
                            system("cls"); 
                            EliminarProducto(productos,&n,clave_productos);
                            system("pause");
                            system("cls"); 
                            break;
                        case 3:
                            system("cls");
                            ModificarProducto(productos,n,clave_productos);
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
                        		ImprimirProductos(productos,n,clave_productos);
                        		system("cls");
                        		ReporteCompleto(productos,n,clave_productos);
                        		system("cls");
                        			break;
                        			case 2:
                        			system("cls");
                        			ImprimirProductosCaducidad(productos,n,clave_productos);
                        			
                        			ImprimirProductosCaducidadOrdenados(productos,n,clave_productos);
                        			
                        			system("cls");
                        				break;
                        			case 3:
							 
    
    									break;

                        					case 4:
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
            	printf("\n1.Generar una compra.\n2.Ordenes de compra.\n3.Reporte de ventas del dia\n4.Salir");
            	printf("\nIngrese una opcion: ");
            	scanf("%d",&opcion3);
            	switch(opcion3){
            			case 1:
            		system("cls");
            		generarTicket(productos, n,clave_productos) ;
            		break;
            		case 2:
            			break;
            			case 3:
            				break;
            				default:
            					break;
				}
            
			}while(opcion3!=4);
            	system("cls");
                break;
            case 3:
                ImprimirProductos(productos, n,clave_productos);
                
                break;
            case 4:
                break;
            default:
                break;
        }
    } while (opcion != 4);
    return 0;
}

void AgregarProducto(Producto productos[], int *n, int clave_productos[]) {
    int i;
    int validar_clave;
    
    printf("\nIngrese los datos para el producto %d:\n", (*n) + 1);

    // Buscar la primera posición libre en el arreglo
    for (i = 0; i < 50; i++) {
        if (productos[i].clave == 0) {
            break;
        }
    }

    do {
        printf("\nClave: ");
        scanf("%d", &productos[i].clave);
        validar_clave = busqueda_secuencial(clave_productos, productos[i].clave, *n);
        if (validar_clave != -1) {
            printf("Ya existe un producto con esa clave, por favor ingrese otra.\n");
        } else {
            clave_productos[i] = productos[i].clave;
        }
    } while (validar_clave != -1);

    printf("\nNombre: ");
    scanf("%s", productos[i].nombre);

    do {
        printf("\nPrecio: ");
        if (scanf("%f", &productos[i].precio) != 1 || productos[i].precio <= 0) {
            printf("Debes ingresar un precio mayor que cero.\n");
        }
    } while (productos[i].precio <= 0);

    do {
        printf("\nCantidad: ");
        if (scanf("%d", &productos[i].cantidad) != 1 || productos[i].cantidad <= 0) {
            printf("Debes ingresar una cantidad mayor que cero.\n");
        }
    } while (productos[i].cantidad <= 0);

    printf("\nFecha de ingreso (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &productos[i].fecha_ingreso.dia, &productos[i].fecha_ingreso.mes, &productos[i].fecha_ingreso.anio);

    printf("\nFecha de caducidad (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &productos[i].fecha_caducidad.dia, &productos[i].fecha_caducidad.mes, &productos[i].fecha_caducidad.anio);

    printf("\nNombre del proveedor: ");
    scanf("%s", productos[i].nombre_proveedor);

    printf("\nTelefono del proveedor: ");
    scanf("%s", productos[i].telefono_proveedor);

    printf("\nCorreo del proveedor: ");
    scanf("%s", productos[i].correo_proveedor);

    printf("\nProducto agregado exitosamente.\n\n\n");
	
    // Aumenta la cantidad de productos en 1
    (*n)++;
    sleep(3);
}





void ImprimirProductos(Producto productos[], int n,int clave_productos[]) {
	int i;
	printf("\n\n\t\t\tTodos los productos\n\n");
    printf("\nClave\tNombre\tPrecio\tCantidad\tFecha Ingreso\tFecha Caducidad\tProveedor\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%s\t%.2f\t%d\t%d/%d/%d\t%d/%d/%d\t%s (%s, %s)\n",
               productos[i].clave, productos[i].nombre, productos[i].precio, productos[i].cantidad,
               productos[i].fecha_ingreso.dia, productos[i].fecha_ingreso.mes, productos[i].fecha_ingreso.anio,
               productos[i].fecha_caducidad.dia, productos[i].fecha_caducidad.mes, productos[i].fecha_caducidad.anio,
               productos[i].nombre_proveedor, productos[i].telefono_proveedor, productos[i].correo_proveedor);
           }
           sleep(5);
}


int busqueda_secuencial(int a[], int dato, int n) {
    char flag = 'F';
    int i = 0;
    while ((flag == 'F') && (i < n)) {
        if (a[i] == dato) {
            flag = 'V';
        }
        i++;
    }
    if (flag == 'F') {
        return -1;
    }
    else if (flag == 'V') {
    	printf("%d",i);
        return i-1;
    }
}

void EliminarProducto(Producto productos[], int *n,int clave_productos[]) {
	
    int clave_producto_a_eliminar, i, posicion_producto_a_eliminar;
    bool encontrado = false;

    printf("Ingrese la clave del producto a eliminar: ");
    scanf("%d", &clave_producto_a_eliminar);

    posicion_producto_a_eliminar = busqueda_secuencial(clave_productos, clave_producto_a_eliminar, *n);
    if (posicion_producto_a_eliminar != -1) {
        for (i = posicion_producto_a_eliminar; i < *n - 1; i++) {
            productos[i] = productos[i + 1];
        }
        (*n)--;
        printf("El producto ha sido eliminado exitosamente.\n");
		eliminacion_previa = true; // Se realizó una eliminación previa

    } else {
        printf("El producto con la clave %d no se encontró en el inventario.\n", clave_producto_a_eliminar);
    }
}

void ModificarProducto(Producto productos[], int n, int clave_productos[]) {
    int i, clave, index;
    printf("\nIngrese la clave del producto a modificar: ");
    scanf("%d", &clave);

	
	for(i=0;i<n;i++){
		if(clave==productos[i].clave){
			index=i;
		}
	}
    /*if (eliminacion_previa) {
        // Si se hizo una eliminación previa, busco el index del producto
        // mediante una nueva búsqueda secuencial
        index = busqueda_secuencial(clave_productos, clave, n-1);
    } else {
        // Si no se hizo eliminación previa, busco el index del producto
        // mediante la búsqueda secuencial original
        index = busqueda_secuencial(clave_productos, clave, n);
    }*/
    
    if (index != -1) {
        i = index;
        printf("Ingrese los nuevos datos para el producto %d:\n", i + 1);
        printf("Ingrese la cantidad nueva: \n");
        scanf("%d", &productos[i].cantidad);
        printf("Ingrese el nuevo nombre de proveedor: \n");
        scanf("%s", productos[i].nombre_proveedor);
        printf("Producto modificado: \n");
        printf("%d\t%s\t%.2f\t%d\t%d/%d/%d\t%d/%d/%d\t%s (%s, %s)\n",
               productos[i].clave, productos[i].nombre, productos[i].precio, productos[i].cantidad,
               productos[i].fecha_ingreso.dia, productos[i].fecha_ingreso.mes, productos[i].fecha_ingreso.anio,
               productos[i].fecha_caducidad.dia, productos[i].fecha_caducidad.mes, productos[i].fecha_caducidad.anio,
               productos[i].nombre_proveedor, productos[i].telefono_proveedor, productos[i].correo_proveedor);
               sleep(3);
    } else {
        printf("El producto con clave %d no existe en el inventario.\n", clave);
        sleep(3);
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

void ReporteCompleto(Producto productos[], int n, int clave_productos[]) {
    int i, clave, index=-1;
    printf("\n\n\t\t\tIngrese la clave del producto a buscar: ");
    scanf("%d", &clave);

    printf("\n\n\t\t\tBuscando producto con clave %d...\n\n", clave);
    sleep(2);

    for (i = 0; i < n; i++) {
        if (clave == productos[i].clave) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        printf("\t\t\t\tProducto con clave %d\n", clave);
        printf("\nClave\tNombre\tPrecio\tCantidad\tFecha Ingreso\tFecha Caducidad\tProveedor\n");
        printf("%d\t%s\t%.2f\t%d\t%d/%d/%d\t%d/%d/%d\t%s (%s, %s)\n",
               productos[index].clave, productos[index].nombre, productos[index].precio, productos[index].cantidad,
               productos[index].fecha_ingreso.dia, productos[index].fecha_ingreso.mes, productos[index].fecha_ingreso.anio,
               productos[index].fecha_caducidad.dia, productos[index].fecha_caducidad.mes, productos[index].fecha_caducidad.anio,
               productos[index].nombre_proveedor, productos[index].telefono_proveedor, productos[index].correo_proveedor);
        sleep(5);
    } else {
        printf("\t\t\t\tProducto con clave %d no encontrado\n", clave);
        sleep(5);
    }
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

void generarTicket(Producto productos[], int n, int clave_productos[]) {
    int i, cantidad, respuesta;
    int clave;
    float total = 0.0;
    FILE *fp;

    fp = fopen("tickets.txt", "a");  // Se abre en modo "a" (append) para agregar al final del archivo existente

    fprintf(fp, "Ticket de Orden de Compra:\n\n");
    fprintf(fp, "No.    Clave   Nombre                          Precio   Cantidad    Total\n");

    i = 0;
    do {
        printf("¿Desea agregar un producto al ticket? (1=Si, 0=No): ");
        scanf("%d", &respuesta);
        if (respuesta == 1) {
            printf("Ingrese la clave del producto que desea comprar: ");
            scanf("%d",&clave);
            i = busqueda_secuencial(clave_productos, clave, n);
            if (i == -1) {
                printf("No se encontró un producto con esa clave.\n");
            } else {
                printf("Ingrese la cantidad a ordenar del producto %d (clave %d): ", i+1, productos[i].clave);
                scanf("%d", &cantidad);

                if (cantidad > 0) {
                    fprintf(fp, "%-7d%-8d%-32s%-9.2f%-12d%-9.2f\n", i+1, productos[i].clave, productos[i].nombre, productos[i].precio, cantidad, cantidad*productos[i].precio);
                    total += cantidad * productos[i].precio;
                }
            }
        }
    } while (respuesta == 1);

    fprintf(fp, "\nTotal: $%.2f\n", total);

    fclose(fp);

    printf("Ticket generado y guardado en el archivo tickets.txt\n");
}



    








