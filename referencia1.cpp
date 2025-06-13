#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

// Estructuras de datos
FILE* misarticulos;
struct articulos {
    int numero;
    char nombre[30];
    int cantidad;
    float precio;
} articulosarial;

FILE* misventas;
struct ventas {
    int numero;
    char fecha[11];
    int numarti;
    int cantidad;
    float precio;
    float total;
} ventasarial;

FILE* miscompras;
struct compras {
    int numero;
    char fecha[11];
    int numarti;
    int cantidad;
    float preciocompra;
    float total;
} comprasarial;

FILE* misclientes;
struct clientes {
    int numero;
    char nombre[30];
    char fecha[11];
} clientesarial;

FILE* misusuarios;
struct usuarios {
    char usuario[20];
    char clave[20];
} usuariosarial;

FILE* miconfig;
struct configs {
    int color_fondo;
    int color_texto;
} configsarial = {0, 15}; // Negro fondo, blanco texto por defecto

// Variables globales
int color_actual = 15;

// Prototipos de funciones
void marco();
void login();
void menu_principal();
void registrar_articulos();
void registrar_ventas();
void registrar_compras();
void registrar_clientes();
void imprimir_articulos();
void imprimir_ventas();
void imprimir_compras();
void imprimir_clientes();
void configurar_colores();
void cargar_configuracion();
void guardar_configuracion();
int buscar_articulo(int numero);
void convertir_mayusculas(char *cadena);
int validar_numero();
void limpiar_buffer();

int main() {
    cargar_configuracion();
    textbackground(configsarial.color_fondo);
    textcolor(configsarial.color_texto);
    clrscr();
    login();
    return 0;
}

void marco() {
    int i;
    // Marco superior
    gotoxy(5, 3);
    printf("%c", 218);
    for(i = 6; i <= 74; i++) {
        gotoxy(i, 3);
        printf("%c", 196);
    }
    gotoxy(75, 3);
    printf("%c", 191);
    
    // Marco inferior
    gotoxy(5, 22);
    printf("%c", 192);
    for(i = 6; i <= 74; i++) {
        gotoxy(i, 22);
        printf("%c", 196);
    }
    gotoxy(75, 22);
    printf("%c", 217);
    
    // Marcos laterales
    for(i = 4; i <= 21; i++) {
        gotoxy(5, i);
        printf("%c", 179);
        gotoxy(75, i);
        printf("%c", 179);
    }
    
    // Titulo
    gotoxy(30, 4);
    printf("SISTEMA DE INVENTARIO");
    gotoxy(28, 5);
    printf("======================");
}

void login() {
    struct usuarios user_input, user_file;
    int intentos = 0, acceso = 0;
    
    while(intentos < 3 && !acceso) {
        clrscr();
        marco();
        
        gotoxy(25, 10);
        printf("ACCESO AL SISTEMA");
        gotoxy(20, 12);
        printf("Usuario: ");
        gotoxy(20, 13);
        printf("Clave: ");
        
        gotoxy(29, 12);
        gets(user_input.usuario);
        convertir_mayusculas(user_input.usuario);
        
        gotoxy(28, 13);
        gets(user_input.clave);
        
        misusuarios = fopen("usuarios.dat", "rb");
        if(misusuarios == NULL) {
            // Crear usuario por defecto si no existe
            misusuarios = fopen("usuarios.dat", "wb");
            strcpy(user_file.usuario, "ADMIN");
            strcpy(user_file.clave, "123");
            fwrite(&user_file, sizeof(user_file), 1, misusuarios);
            fclose(misusuarios);
            misusuarios = fopen("usuarios.dat", "rb");
        }
        
        while(fread(&user_file, sizeof(user_file), 1, misusuarios) && !acceso) {
            if(strcmp(user_input.usuario, user_file.usuario) == 0 && 
               strcmp(user_input.clave, user_file.clave) == 0) {
                acceso = 1;
            }
        }
        fclose(misusuarios);
        
        if(acceso) {
            gotoxy(25, 16);
            printf("Acceso concedido!");
            getch();
            menu_principal();
        } else {
            intentos++;
            gotoxy(20, 16);
            printf("Usuario o clave incorrectos. Intento %d/3", intentos);
            getch();
        }
    }
    
    if(!acceso) {
        gotoxy(20, 18);
        printf("Acceso denegado. Sistema bloqueado.");
        getch();
    }
}

void menu_principal() {
    int opcion;
    
    do {
        clrscr();
        marco();
        
        gotoxy(30, 7);
        printf("MENU PRINCIPAL");
        gotoxy(20, 9);
        printf("1. Registrar Articulos");
        gotoxy(20, 10);
        printf("2. Registrar Ventas");
        gotoxy(20, 11);
        printf("3. Registrar Compras");
        gotoxy(20, 12);
        printf("4. Registrar Clientes");
        gotoxy(20, 13);
        printf("5. Imprimir Articulos");
        gotoxy(20, 14);
        printf("6. Imprimir Ventas");
        gotoxy(20, 15);
        printf("7. Imprimir Compras");
        gotoxy(20, 16);
        printf("8. Imprimir Clientes");
        gotoxy(20, 17);
        printf("9. Configurar Colores");
        gotoxy(20, 18);
        printf("0. Salir");
        
        gotoxy(20, 20);
        printf("Seleccione una opcion (0-9): ");
        opcion = validar_numero();
        
        switch(opcion) {
            case 1: registrar_articulos(); break;
            case 2: registrar_ventas(); break;
            case 3: registrar_compras(); break;
            case 4: registrar_clientes(); break;
            case 5: imprimir_articulos(); break;
            case 6: imprimir_ventas(); break;
            case 7: imprimir_compras(); break;
            case 8: imprimir_clientes(); break;
            case 9: configurar_colores(); break;
            case 0: 
                gotoxy(25, 20);
                printf("Gracias por usar el sistema!");
                getch();
                break;
            default:
                gotoxy(20, 20);
                printf("Opcion invalida. Presione una tecla...");
                getch();
        }
    } while(opcion != 0);
}

void registrar_articulos() {
    char continuar;
    
    do {
        clrscr();
        marco();
        
        gotoxy(28, 7);
        printf("REGISTRAR ARTICULOS");
        
        misarticulos = fopen("articulos.dat", "ab");
        if(misarticulos == NULL) {
            gotoxy(20, 10);
            printf("Error al abrir archivo");
            getch();
            return;
        }
        
        gotoxy(20, 10);
        printf("Numero: ");
        articulosarial.numero = validar_numero();
        
        gotoxy(20, 11);
        printf("Nombre: ");
        limpiar_buffer();
        gets(articulosarial.nombre);
        convertir_mayusculas(articulosarial.nombre);
        
        gotoxy(20, 12);
        printf("Cantidad: ");
        articulosarial.cantidad = validar_numero();
        
        gotoxy(20, 13);
        printf("Precio: ");
        scanf("%f", &articulosarial.precio);
        
        fwrite(&articulosarial, sizeof(articulosarial), 1, misarticulos);
        fclose(misarticulos);
        
        gotoxy(20, 15);
        printf("Articulo registrado exitosamente!");
        gotoxy(20, 16);
        printf("Desea agregar otro? (S/N): ");
        limpiar_buffer();
        scanf("%c", &continuar);
        continuar = toupper(continuar);
        
    } while(continuar == 'S');
}

void registrar_ventas() {
    char continuar;
    float precio_unitario;
    
    do {
        clrscr();
        marco();
        
        gotoxy(30, 7);
        printf("REGISTRAR VENTAS");
        
        misventas = fopen("ventas.dat", "ab");
        if(misventas == NULL) {
            gotoxy(20, 10);
            printf("Error al abrir archivo");
            getch();
            return;
        }
        
        gotoxy(20, 9);
        printf("Numero de venta: ");
        ventasarial.numero = validar_numero();
        
        gotoxy(20, 10);
        printf("Fecha (DD/MM/AAAA): ");
        limpiar_buffer();
        gets(ventasarial.fecha);
        
        gotoxy(20, 11);
        printf("Numero de articulo: ");
        ventasarial.numarti = validar_numero();
        
        if(buscar_articulo(ventasarial.numarti)) {
            gotoxy(20, 12);
            printf("Nombre: %s", articulosarial.nombre);
            gotoxy(20, 13);
            printf("Precio unitario: %.2f", articulosarial.precio);
            
            gotoxy(20, 14);
            printf("Cantidad a vender: ");
            ventasarial.cantidad = validar_numero();
            
            if(ventasarial.cantidad > articulosarial.cantidad) {
                gotoxy(20, 16);
                printf("No hay suficiente inventario!");
                getch();
                fclose(misventas);
                continue;
            }
            
            ventasarial.precio = articulosarial.precio;
            ventasarial.total = ventasarial.cantidad * ventasarial.precio;
            
            gotoxy(20, 15);
            printf("Total: %.2f", ventasarial.total);
            
            fwrite(&ventasarial, sizeof(ventasarial), 1, misventas);
            
            gotoxy(20, 17);
            printf("Venta registrada exitosamente!");
            gotoxy(20, 18);
            printf("NOTA: Inventario NO actualizado automaticamente");
        } else {
            gotoxy(20, 12);
            printf("Articulo no encontrado!");
        }
        
        fclose(misventas);
        
        gotoxy(20, 19);
        printf("Desea registrar otra venta? (S/N): ");
        limpiar_buffer();
        scanf("%c", &continuar);
        continuar = toupper(continuar);
        
    } while(continuar == 'S');
}

void registrar_compras() {
    char continuar;
    
    do {
        clrscr();
        marco();
        
        gotoxy(30, 7);
        printf("REGISTRAR COMPRAS");
        
        miscompras = fopen("compras.dat", "ab");
        if(miscompras == NULL) {
            gotoxy(20, 10);
            printf("Error al abrir archivo");
            getch();
            return;
        }
        
        gotoxy(20, 9);
        printf("Numero de compra: ");
        comprasarial.numero = validar_numero();
        
        gotoxy(20, 10);
        printf("Fecha (DD/MM/AAAA): ");
        limpiar_buffer();
        gets(comprasarial.fecha);
        
        gotoxy(20, 11);
        printf("Numero de articulo: ");
        comprasarial.numarti = validar_numero();
        
        if(buscar_articulo(comprasarial.numarti)) {
            gotoxy(20, 12);
            printf("Nombre: %s", articulosarial.nombre);
            
            gotoxy(20, 13);
            printf("Cantidad a comprar: ");
            comprasarial.cantidad = validar_numero();
            
            gotoxy(20, 14);
            printf("Precio de compra: ");
            scanf("%f", &comprasarial.preciocompra);
            
            comprasarial.total = comprasarial.cantidad * comprasarial.preciocompra;
            
            gotoxy(20, 15);
            printf("Total: %.2f", comprasarial.total);
            
            fwrite(&comprasarial, sizeof(comprasarial), 1, miscompras);
            
            gotoxy(20, 17);
            printf("Compra registrada exitosamente!");
            gotoxy(20, 18);
            printf("NOTA: Inventario NO actualizado automaticamente");
        } else {
            gotoxy(20, 12);
            printf("Articulo no encontrado!");
        }
        
        fclose(miscompras);
        
        gotoxy(20, 19);
        printf("Desea registrar otra compra? (S/N): ");
        limpiar_buffer();
        scanf("%c", &continuar);
        continuar = toupper(continuar);
        
    } while(continuar == 'S');
}

void registrar_clientes() {
    char continuar;
    
    do {
        clrscr();
        marco();
        
        gotoxy(30, 7);
        printf("REGISTRAR CLIENTES");
        
        misclientes = fopen("clientes.dat", "ab");
        if(misclientes == NULL) {
            gotoxy(20, 10);
            printf("Error al abrir archivo");
            getch();
            return;
        }
        
        gotoxy(20, 10);
        printf("Numero: ");
        clientesarial.numero = validar_numero();
        
        gotoxy(20, 11);
        printf("Nombre: ");
        limpiar_buffer();
        gets(clientesarial.nombre);
        convertir_mayusculas(clientesarial.nombre);
        
        gotoxy(20, 12);
        printf("Fecha de ingreso (DD/MM/AAAA): ");
        gets(clientesarial.fecha);
        
        fwrite(&clientesarial, sizeof(clientesarial), 1, misclientes);
        fclose(misclientes);
        
        gotoxy(20, 14);
        printf("Cliente registrado exitosamente!");
        gotoxy(20, 15);
        printf("Desea agregar otro? (S/N): ");
        scanf("%c", &continuar);
        continuar = toupper(continuar);
        
    } while(continuar == 'S');
}

void imprimir_articulos() {
    float total_inventario = 0;
    int linea = 9;
    
    clrscr();
    marco();
    
    gotoxy(30, 7);
    printf("LISTADO DE ARTICULOS");
    gotoxy(10, 8);
    printf("Num  Nombre              Cant  Precio   Total");
    
    misarticulos = fopen("articulos.dat", "rb");
    if(misarticulos == NULL) {
        gotoxy(20, 10);
        printf("No hay articulos registrados");
        getch();
        return;
    }
    
    while(fread(&articulosarial, sizeof(articulosarial), 1, misarticulos)) {
        float total_articulo = articulosarial.cantidad * articulosarial.precio;
        gotoxy(10, linea);
        printf("%d     %s              %d %8.2f %8.2f", articulosarial.numero, articulosarial.nombre, articulosarial.cantidad, articulosarial.precio, total_articulo);
        total_inventario += total_articulo;
        linea++;
    }
    
    gotoxy(10, linea + 1);
    printf("TOTAL INVENTARIO: $%.2f", total_inventario);
    
    fclose(misarticulos);
    getch();
}

void imprimir_ventas() {
    float total_ventas = 0;
    int linea = 9;
    
    clrscr();
    marco();
    
    gotoxy(30, 7);
    printf("LISTADO DE VENTAS");
    gotoxy(7, 8);
    printf("Num  Fecha      Art Cant  Precio   Total");
    
    misventas = fopen("ventas.dat", "rb");
    if(misventas == NULL) {
        gotoxy(20, 10);
        printf("No hay ventas registradas");
        getch();
        return;
    }
    
    while(fread(&ventasarial, sizeof(ventasarial), 1, misventas)) {
        gotoxy(7, linea);
        printf("%-4d %-10s %3d %4d %8.2f %8.2f", 
               ventasarial.numero, ventasarial.fecha, ventasarial.numarti, ventasarial.cantidad, ventasarial.precio, ventasarial.total);
        total_ventas += ventasarial.total;
        linea++;
    }
    
    gotoxy(7, linea + 1);
    printf("TOTAL VENTAS: $%.2f", total_ventas);
    
    fclose(misventas);
    getch();
}

void imprimir_compras() {
    float total_compras = 0;
    int linea = 9;
    
    clrscr();
    marco();
    
    gotoxy(30, 7);
    printf("LISTADO DE COMPRAS");
    gotoxy(5, 8);
    printf("Num  Fecha      Art  Nombre              Cant  Precio   Total");
    
    miscompras = fopen("compras.dat", "rb");
    if(miscompras == NULL) {
        gotoxy(20, 10);
        printf("No hay compras registradas");
        getch();
        return;
    }
    
    while(fread(&comprasarial, sizeof(comprasarial), 1, miscompras)) {
        // Buscar el nombre del artículo
        char nombre_articulo[30] = "NO ENCONTRADO";
        if(buscar_articulo(comprasarial.numarti)) {
            strcpy(nombre_articulo, articulosarial.nombre);
        }
        
        gotoxy(5, linea);
        printf("%d  %s    %d    %s               %d %8.2f %8.2f", comprasarial.numero, comprasarial.fecha, comprasarial.numarti, nombre_articulo, comprasarial.cantidad, comprasarial.preciocompra, comprasarial.total);
        total_compras += comprasarial.total;
        linea++;
    }
    
    gotoxy(5, linea + 1);
    printf("TOTAL COMPRAS: $%.2f", total_compras);
    
    fclose(miscompras);
    gotoxy(20, linea + 3);
    printf("Presione cualquier tecla para continuar...");
    getch();
}

void imprimir_clientes() {
    int linea = 9;
    
    clrscr();
    marco();
    
    gotoxy(30, 7);
    printf("LISTADO DE CLIENTES");
    gotoxy(15, 8);
    printf("Numero  Nombre              Fecha");
    
    misclientes = fopen("clientes.dat", "rb");
    if(misclientes == NULL) {
        gotoxy(20, 10);
        printf("No hay clientes registrados");
        getch();
        return;
    }
    
    while(fread(&clientesarial, sizeof(clientesarial), 1, misclientes)) {
        gotoxy(15, linea);
        printf("%d  %s         %s", clientesarial.numero, clientesarial.nombre, clientesarial.fecha);
        linea++;
    }
    
    fclose(misclientes);
    getch();
}

void configurar_colores() {
    int opcion;
    
    clrscr();
    marco();
    
    gotoxy(28, 7);
    printf("CONFIGURAR COLORES");
    gotoxy(20, 10);
    printf("1. Tema Claro (Negro/Blanco)");
    gotoxy(20, 11);
    printf("2. Tema Oscuro (Azul/Amarillo)");
    gotoxy(20, 12);
    printf("3. Tema Verde (Verde/Blanco)");
    gotoxy(20, 13);
    printf("4. Tema Rojo (Rojo/Blanco)");
    
    gotoxy(20, 15);
    printf("Seleccione tema (1-4): ");
    opcion = validar_numero();
    
    switch(opcion) {
        case 1:
            configsarial.color_fondo = 0;
            configsarial.color_texto = 15;
            break;
        case 2:
            configsarial.color_fondo = 1;
            configsarial.color_texto = 14;
            break;
        case 3:
            configsarial.color_fondo = 2;
            configsarial.color_texto = 15;
            break;
        case 4:
            configsarial.color_fondo = 4;
            configsarial.color_texto = 15;
            break;
        default:
            gotoxy(20, 17);
            printf("Opcion invalida");
            getch();
            return;
    }
    
    textbackground(configsarial.color_fondo);
    textcolor(configsarial.color_texto);
    guardar_configuracion();
    
    gotoxy(20, 17);
    printf("Configuracion guardada!");
    getch();
    clrscr();
}

void cargar_configuracion() {
    miconfig = fopen("config.dat", "rb");
    if(miconfig != NULL) {
        fread(&configsarial, sizeof(configsarial), 1, miconfig);
        fclose(miconfig);
    }
}

void guardar_configuracion() {
    miconfig = fopen("config.dat", "wb");
    if(miconfig != NULL) {
        fwrite(&configsarial, sizeof(configsarial), 1, miconfig);
        fclose(miconfig);
    }
}

int buscar_articulo(int numero) {
    misarticulos = fopen("articulos.dat", "rb");
    if(misarticulos == NULL) return 0;
    
    while(fread(&articulosarial, sizeof(articulosarial), 1, misarticulos)) {
        if(articulosarial.numero == numero) {
            fclose(misarticulos);
            return 1;
        }
    }
    fclose(misarticulos);
    return 0;
}

void convertir_mayusculas(char *cadena) {
    int i;
    for(i = 0; cadena[i]; i++) {
        cadena[i] = toupper(cadena[i]);
    }
}

int validar_numero() {
    int numero;
    while(scanf("%d", &numero) != 1) {
        printf("Error: Ingrese solo numeros. Intente de nuevo: ");
        limpiar_buffer();
    }
    return numero;
}

void limpiar_buffer() {
    while(getchar() != '\n');
}

