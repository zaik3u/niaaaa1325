#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>

// Variables globales del sistema
int maxOrigenes = 5;
int maxTemporadas = 3;
int precioBase = 100;
int maxIntentos = 3;
int anchoPantalla = 80;
int altoPantalla = 24;
char fechaActual[] = "2025-06-12 17:53:59";
char usuarioActual[] = "German08052";
char usuarioSistema[] = "Comrade Manager";
char usuarioValido[] = "LEONARDO";
char claveValida[] = "1917";
char version[] = "1.0";
char fechaVersion[] = "12/06/2025";

// Arrays de opciones para bayas
char const *origenes[] = {
    "Siberia",
    "Karelia", 
    "Altái", 
    "Urales", 
    "Cáucaso"
};

char const *temporadas[] = {
    "Primavera",
    "Verano",
    "Otoño"
};

// Símbolos especiales
char const *simbolos[] = {
    "?",  // Símbolo soviético
    "?",  // Estrella
    "?",  // Flecha menú
    "?",  // Diamante
    "?",  // Check
    "?"   // Advertencia
};

char moneda = '?';

// Códigos de color para system("color XX")
char const *colores[] = {
    "4F",  // Rojo soviético
    "1F",  // Azul soviético
    "2F",  // Verde soviético
    "CF",  // Rojo brillante
    "3F",  // Cyan soviético
    "7F",  // Gris soviético
    "0F",  // Negro
    "5F"   // Púrpura soviético
};

// Nombres de archivos
char archivoProductos[] = "bayas.dat";
char archivoVentas[] = "ventas.dat";
char archivoCompras[] = "compras.dat";
char archivoClientes[] = "clientes.dat";
char archivoTemp[] = "temp.dat";

// Estructuras de datos
struct productos {
    int codigo;
    char nombre[30];
    char origen[20];
    char temporada[15];
    int stock;
    float precio;
    char fechaRegistro[20];
};

struct ventas {
    int codigo;
    char fecha[11];
    int codProducto;
    int cantidad;
    float precio;
    float total;
};

struct compras {
    int codigo;
    char fecha[11];
    int codProducto;
    char proveedor[30];
    int cantidad;
    float precioProveedor;
    float total;
};

struct clientes {
    int codigo;
    char nombre[30];
    char ciudad[20];
    char fechaRegistro[11];
};

// Variables globales de archivos
FILE* berriesProductos;
FILE* berriesVentas;
FILE* berriesCompras;
FILE* berriesClientes;

// Variables globales de estructuras
struct productos productoMora;
struct ventas ventaMora;
struct compras compraMora;
struct clientes clienteMora;

// Prototipos de funciones
void dibujarMarcoSovietico();
void dibujarMarcoDoble();
void dibujarMarcoSencillo();
void iniciarSesion();
void menuPrincipal();
int buscarProducto(int codigo);
void registrarProducto();
void registrarVenta();
void registrarCompra();
void registrarCliente();
void mostrarProductos();
void mostrarVentas();
void mostrarCompras();
void mostrarClientes();
void convertirMayusculas(char *texto);
int validarNumero();
void mostrarCreditos();
void actualizarStock(int codigo, int cantidad, char tipo);

int main() {
    system("color 4F");
    clrscr();
    iniciarSesion();
    return 0;
}

void dibujarMarcoSovietico() {
    int i;
    
    // Esquinas con símbolo soviético
    gotoxy(3, 2); printf("?");
    gotoxy(77, 2); printf("?");
    gotoxy(3, 22); printf("?");
    gotoxy(77, 22); printf("?");
    
    // Líneas horizontales dobles
    for(i = 4; i <= 76; i++) {
        gotoxy(i, 2); printf("-");
        gotoxy(i, 22); printf("-");
    }
    
    // Líneas verticales dobles
    for(i = 3; i <= 21; i++) {
        gotoxy(3, i); printf("¦");
        gotoxy(77, i); printf("¦");
    }
}

void dibujarMarcoDoble() {
    int i;
    
    // Esquinas
    gotoxy(3, 2); printf("+");
    gotoxy(77, 2); printf("+");
    gotoxy(3, 22); printf("+");
    gotoxy(77, 22); printf("+");
    
    // Líneas horizontales
    for(i = 4; i <= 76; i++) {
        gotoxy(i, 2); printf("-");
        gotoxy(i, 22); printf("-");
    }
    
    // Líneas verticales
    for(i = 3; i <= 21; i++) {
        gotoxy(3, i); printf("¦");
        gotoxy(77, i); printf("¦");
    }
}

void dibujarMarcoSencillo() {
    int i;
    
    // Esquinas
    gotoxy(3, 2); printf("+");
    gotoxy(77, 2); printf("+");
    gotoxy(3, 22); printf("+");
    gotoxy(77, 22); printf("+");
    
    // Líneas horizontales
    for(i = 4; i <= 76; i++) {
        gotoxy(i, 2); printf("-");
        gotoxy(i, 22); printf("-");
    }
    
    // Líneas verticales
    for(i = 3; i <= 21; i++) {
        gotoxy(3, i); printf("¦");
        gotoxy(77, i); printf("¦");
    }
}

void iniciarSesion() {
    char usuario[20], clave[20];
    int intentos = 0, acceso = 0;
    
    while(intentos < maxIntentos && !acceso) {
        clrscr();
        system("color 9F");
        dibujarMarcoSovietico();
        
        gotoxy(25, 10);
        printf("? SOVIET BERRIES STORE ?");
        gotoxy(20, 12);
        printf("Camarada: ");
        gotoxy(20, 13);
        printf("Código de acceso: ");
        
        gotoxy(30, 12);
        gets(usuario);
        convertirMayusculas(usuario);
        
        gotoxy(36, 13);
        gets(clave);
        
        if(strcmp(usuario, usuarioValido) == 0 && strcmp(clave, claveValida) == 0) {
            acceso = 1;
            system("color 2F");
            gotoxy(25, 16);
            printf("¡Bienvenido, Camarada!");
            gotoxy(20, 18);
            printf("Administrador: %s", usuarioSistema);
            Sleep(1500);
            menuPrincipal();
        } else {
            system("color CF");
            intentos++;
            gotoxy(20, 16);
            printf("? Acceso Denegado. Intento %d/%d ?", intentos, maxIntentos);
            Sleep(1500);
        }
    }
    
    if(!acceso) {
        system("color 0C");
        gotoxy(20, 18);
        printf("¡Sistema bloqueado por seguridad estatal!");
        getch();
    }
}

void menuPrincipal() {
    int opcion;
    
    do {
        clrscr();
        system("color 4F");
        dibujarMarcoSovietico();
        
        gotoxy(30, 7);printf("? MENÚ PRINCIPAL ?");
        gotoxy(21, 9);printf("1 ? Registrar Bayas");
        gotoxy(21, 10);printf("2 ? Registrar Venta");
        gotoxy(21, 11);printf("3 ? Registrar Importación");
        gotoxy(21, 12);printf("4 ? Registrar Camarada");
        gotoxy(21, 13);printf("5 ? Inventario de Bayas");
        gotoxy(21, 14);printf("6 ? Historial de Ventas");
        gotoxy(21, 15);printf("7 ? Historial de Importaciones");
        gotoxy(21, 16);printf("8 ? Lista de Camaradas");
        gotoxy(21, 17);printf("9 ? Sobre Nosotros");
        gotoxy(21, 18);printf("0 ? Salir");
        
        gotoxy(20, 20);printf("Seleccione una opción, Camarada (0-9): ");
        opcion = validarNumero();
        
        switch(opcion) {
            case 1: 
                system("color 1F");
                registrarProducto(); 
                break;
            case 2: 
                system("color 2F");
                registrarVenta(); 
                break;
            case 3: 
                system("color 5F");
                registrarCompra(); 
                break;
            case 4: 
                system("color 6F");
                registrarCliente(); 
                break;
            case 5: 
                system("color 3F");
                mostrarProductos(); 
                break;
            case 6: 
                system("color 4F");
                mostrarVentas(); 
                break;
            case 7: 
                system("color 9F");
                mostrarCompras(); 
                break;
            case 8: 
                system("color AF");
                mostrarClientes(); 
                break;
            case 9: 
                system("color 7F");
                mostrarCreditos(); 
                break;
            case 0: 
                system("color 0F");
                gotoxy(20, 20);
                printf("¡Hasta la próxima, Camarada!");
                Sleep(1500);
                break;
            default:
                system("color CF");
                gotoxy(20, 20);
                printf("¡Opción no válida, Camarada!");
                Sleep(1500);
        }
    } while(opcion != 0);
}

void registrarProducto() {
    char continuar;
    
    do {
        clrscr();
        system("color 1F");
        dibujarMarcoDoble();
        
        gotoxy(28, 7);printf("? REGISTRO DE BAYAS ?");
        
        berriesProductos = fopen(archivoProductos, "ab");
        if(berriesProductos == NULL) {
            gotoxy(20, 10);
            printf("? Error al abrir archivo");
            getch();
            return;
        }
        
        gotoxy(20, 10);printf("? Código: ");
        productoMora.codigo = validarNumero();
        
        gotoxy(20, 11);printf("? Nombre de Baya: ");
        fflush(stdin);
        gets(productoMora.nombre);
        convertirMayusculas(productoMora.nombre);
        
        gotoxy(20, 12);printf("? Región de origen (1-5):");
        for(int i = 0; i < maxOrigenes; i++) {
            gotoxy(22, 13+i);
            printf("%d. %s", i+1, origenes[i]);
        }
        int origen;
        gotoxy(20, 18);printf("Seleccione: ");
        origen = validarNumero();
        if(origen >= 1 && origen <= maxOrigenes) {
            strcpy(productoMora.origen, origenes[origen-1]);
        }
        
        gotoxy(45, 12);printf("? Temporada (1-3):");
        for(int i = 0; i < maxTemporadas; i++) {
            gotoxy(47, 13+i);
            printf("%d. %s", i+1, temporadas[i]);
        }
        int temp;
        gotoxy(45, 16);printf("Seleccione: ");
        temp = validarNumero();
        if(temp >= 1 && temp <= maxTemporadas) {
            strcpy(productoMora.temporada, temporadas[temp-1]);
        }
        
        gotoxy(45, 17);printf("? Stock (gramos): ");
        productoMora.stock = validarNumero();
        
        gotoxy(45, 18);printf("? Precio por 100g: %c", moneda);
        scanf("%f", &productoMora.precio);
        
        strcpy(productoMora.fechaRegistro, fechaActual);
        
        fwrite(&productoMora, sizeof(productoMora), 1, berriesProductos);
        fclose(berriesProductos);
        
        gotoxy(20, 20);printf("? ¡Baya registrada exitosamente!");
        gotoxy(20, 21);printf("¿Desea agregar otra baya, Camarada? (S/N): ");
        fflush(stdin);
        scanf("%c", &continuar);
        continuar = toupper(continuar);
        
    } while(continuar == 'S');
}

void registrarVenta() {
    char continuar;
    
    do {
        clrscr();
        system("color 2F");
        dibujarMarcoDoble();
        
        gotoxy(30, 7);printf("? REGISTRO DE VENTAS ?");
        
        berriesVentas = fopen(archivoVentas, "ab");
        if(berriesVentas == NULL) {
            gotoxy(20, 10);
            printf("? Error al abrir archivo");
            getch();
            return;
        }
        
        gotoxy(20, 9);printf("? Código de venta: ");
        ventaMora.codigo = validarNumero();
        
        gotoxy(20, 10);printf("? Fecha (DD/MM/AAAA): ");
        fflush(stdin);
        gets(ventaMora.fecha);
        
        gotoxy(20, 11);printf("? Código de baya: ");
        ventaMora.codProducto = validarNumero();
        
        if(buscarProducto(ventaMora.codProducto)) {
            gotoxy(20, 12);printf("Baya: %s", productoMora.nombre);
            gotoxy(20, 13);printf("Origen: %s", productoMora.origen);
            gotoxy(20, 14);printf("Precio por 100g: %c%.2f", moneda, productoMora.precio);
            gotoxy(20, 15);printf("Stock disponible: %dg", productoMora.stock);
            
            gotoxy(20, 16);printf("? Cantidad a vender (gramos): ");
            ventaMora.cantidad = validarNumero();
            
            if(ventaMora.cantidad > productoMora.stock) {
                gotoxy(20, 18);
                printf("? ¡Stock insuficiente, Camarada!");
                getch();
                fclose(berriesVentas);
                continue;
            }
            
            ventaMora.precio = productoMora.precio;
            ventaMora.total = (ventaMora.cantidad / 100.0) * ventaMora.precio;
            
            gotoxy(20, 17);printf("Total: %c%.2f", moneda, ventaMora.total);
            
            fwrite(&ventaMora, sizeof(ventaMora), 1, berriesVentas);
            fclose(berriesVentas);
            
            actualizarStock(ventaMora.codProducto, ventaMora.cantidad, 'V');
            
            gotoxy(20, 19);printf("? ¡Venta registrada exitosamente!");
        } else {
            gotoxy(20, 12);printf("? ¡Baya no encontrada!");
            fclose(berriesVentas);
        }
        
        gotoxy(20, 20);printf("¿Desea registrar otra venta, Camarada? (S/N): ");
        fflush(stdin);
        scanf("%c", &continuar);
        continuar = toupper(continuar);
        
    } while(continuar == 'S');
}

void registrarCompra() {
    char continuar;
    
    do {
        clrscr();
        system("color 5F");
        dibujarMarcoDoble();
        
        gotoxy(30, 7);printf("? REGISTRO DE IMPORTACIONES ?");
        
        berriesCompras = fopen(archivoCompras, "ab");
        if(berriesCompras == NULL) {
            gotoxy(20, 10);
            printf("? Error al abrir archivo");
            getch();
            return;
        }
        
        gotoxy(20, 9);printf("? Código de importación: ");
        compraMora.codigo = validarNumero();
        
        gotoxy(20, 10);printf("? Fecha (DD/MM/AAAA): ");
        fflush(stdin);
        gets(compraMora.fecha);
        
        gotoxy(20, 11);printf("? Código de baya: ");
        compraMora.codProducto = validarNumero();
        
        if(buscarProducto(compraMora.codProducto)) {
            gotoxy(20, 12);printf("Baya: %s", productoMora.nombre);
            gotoxy(20, 13);printf("Stock actual: %dg", productoMora.stock);
            
            gotoxy(20, 14);printf("? Proveedor soviético: ");
            fflush(stdin);
            gets(compraMora.proveedor);
            convertirMayusculas(compraMora.proveedor);
            
            gotoxy(20, 15);printf("? Cantidad a importar (gramos): ");
            compraMora.cantidad = validarNumero();
            
            gotoxy(20, 16);printf("? Precio de compra por 100g: %c", moneda);
            scanf("%f", &compraMora.precioProveedor);
            
            compraMora.total = (compraMora.cantidad / 100.0) * compraMora.precioProveedor;
            
            gotoxy(20, 17);printf("Total: %c%.2f", moneda, compraMora.total);
            
            fwrite(&compraMora, sizeof(compraMora), 1, berriesCompras);
            fclose(berriesCompras);
            
            actualizarStock(compraMora.codProducto, compraMora.cantidad, 'C');
            
            gotoxy(20, 19);printf("? ¡Importación registrada exitosamente!");
        } else {
            gotoxy(20, 12);printf("? ¡Baya no encontrada!");
            fclose(berriesCompras);
        }
        
        gotoxy(20, 20);printf("¿Desea registrar otra importación, Camarada? (S/N): ");
        fflush(stdin);
        scanf("%c", &continuar);
        continuar = toupper(continuar);
        
    } while(continuar == 'S');
}

void registrarCliente() {
    char continuar;
    
    do {
        clrscr();
        system("color 6F");
        dibujarMarcoSencillo();
        
        gotoxy(30, 7);printf("? REGISTRO DE CAMARADAS ?");
        
        berriesClientes = fopen(archivoClientes, "ab");
        if(berriesClientes == NULL) {
            gotoxy(20, 10);
            printf("? Error al abrir archivo");
            getch();
            return;
        }
        
        gotoxy(20, 10);printf("? Código de camarada: ");
        clienteMora.codigo = validarNumero();
        
        gotoxy(20, 11);printf("? Nombre del camarada: ");
        fflush(stdin);
        gets(clienteMora.nombre);
        convertirMayusculas(clienteMora.nombre);
        
        gotoxy(20, 12);printf("? Ciudad: ");
        gets(clienteMora.ciudad);
        convertirMayusculas(clienteMora.ciudad);
        
        gotoxy(20, 13);printf("? Fecha de registro (DD/MM/AAAA): ");
        gets(clienteMora.fechaRegistro);
        
        fwrite(&clienteMora, sizeof(clienteMora), 1, berriesClientes);
        fclose(berriesClientes);
        
        gotoxy(20, 15);printf("? ¡Camarada registrado exitosamente!");
        gotoxy(20, 16);printf("¿Desea registrar otro camarada? (S/N): ");
        fflush(stdin);
        scanf("%c", &continuar);
        continuar = toupper(continuar);
        
    } while(continuar == 'S');
}

void mostrarProductos() {
    float totalInventario = 0;
    int linea = 9;
    
    clrscr();
    system("color 3F");
    dibujarMarcoSovietico();
    
    gotoxy(30, 7);printf("? INVENTARIO DE BAYAS ?");
    gotoxy(8, 8);printf("Cod  Baya          Origen      Temporada  Stock(g)  %c/100g   Total", moneda);
    
    berriesProductos = fopen(archivoProductos, "rb");
    if(berriesProductos == NULL) {
        gotoxy(20, 10);
        printf("No hay bayas registradas, Camarada");
        getch();
        return;
    }
    
    while(fread(&productoMora, sizeof(productoMora), 1, berriesProductos)) {
        float totalProducto = (productoMora.stock / 100.0) * productoMora.precio;
        gotoxy(8, linea);
        printf("%d  %-13s %-10s %-9s %6d %8.2f %8.2f", 
               productoMora.codigo, productoMora.nombre, 
               productoMora.origen, productoMora.temporada,
               productoMora.stock, productoMora.precio, totalProducto);
        totalInventario += totalProducto;
        linea++;
    }
    
    gotoxy(8, linea + 1);
    printf("VALOR TOTAL DEL INVENTARIO: %c%.2f", moneda, totalInventario);
    
    fclose(berriesProductos);
    getch();
}

void mostrarVentas() {
    float totalVentas = 0;
    int linea = 9;
    
    clrscr();
    system("color 4F");
    dibujarMarcoSovietico();
    
    gotoxy(30, 7);printf("? HISTORIAL DE VENTAS ?");
    gotoxy(7, 8);printf("Cod  Fecha      Baya  Cant(g)  %c/100g   Total", moneda);
    
    berriesVentas = fopen(archivoVentas, "rb");
    if(berriesVentas == NULL) {
        gotoxy(20, 10);
        printf("No hay ventas registradas, Camarada");
        getch();
        return;
    }
    
    while(fread(&ventaMora, sizeof(ventaMora), 1, berriesVentas)) {
        gotoxy(7, linea);
        printf("%d   %-10s %3d  %6d %8.2f %8.2f", 
               ventaMora.codigo, ventaMora.fecha, 
               ventaMora.codProducto, ventaMora.cantidad,
               ventaMora.precio, ventaMora.total);
        totalVentas += ventaMora.total;
        linea++;
    }
    
    gotoxy(7, linea + 1);
    printf("TOTAL VENTAS: %c%.2f", moneda, totalVentas);
    
    fclose(berriesVentas);
    getch();
}

void mostrarCompras() {
    float totalCompras = 0;
    int linea = 9;
    
    clrscr();
    system("color 5F");
    dibujarMarcoSovietico();
    
    gotoxy(30, 7);printf("? HISTORIAL DE IMPORTACIONES ?");
    gotoxy(5, 8);printf("Cod  Fecha      Baya  Proveedor        Cant(g)  %c/100g   Total", moneda);
    
    berriesCompras = fopen(archivoCompras, "rb");
    if(berriesCompras == NULL) {
        gotoxy(20, 10);
        printf("No hay importaciones registradas, Camarada");
        getch();
        return;
    }
    
    while(fread(&compraMora, sizeof(compraMora), 1, berriesCompras)) {
        gotoxy(5, linea);
        printf("%d  %s  %d  %-15s %6d %8.2f %8.2f", 
               compraMora.codigo, compraMora.fecha, 
               compraMora.codProducto, compraMora.proveedor,
               compraMora.cantidad, compraMora.precioProveedor,
               compraMora.total);
        totalCompras += compraMora.total;
        linea++;
    }
    
    gotoxy(5, linea + 1);
    printf("TOTAL IMPORTACIONES: %c%.2f", moneda, totalCompras);
    
    fclose(berriesCompras);
    getch();
}

void mostrarClientes() {
    int linea = 9;
    
    clrscr();
    system("color 2F");
    dibujarMarcoSencillo();
    
    gotoxy(30, 7);printf("? LISTADO DE CAMARADAS ?");
    gotoxy(15, 8);printf("Código  Nombre              Ciudad         Registro");
    
    berriesClientes = fopen(archivoClientes, "rb");
    if(berriesClientes == NULL) {
        gotoxy(20, 10);
        printf("No hay camaradas registrados");
        getch();
        return;
    }
    
    while(fread(&clienteMora, sizeof(clienteMora), 1, berriesClientes)) {
        gotoxy(15, linea);
        printf("%d      %-20s %-14s %s", 
               clienteMora.codigo, clienteMora.nombre, 
               clienteMora.ciudad, clienteMora.fechaRegistro);
        linea++;
    }
    
    fclose(berriesClientes);
    getch();
}

void mostrarCreditos() {
    clrscr();
    system("color 7F");
    dibujarMarcoSovietico();
    
    gotoxy(30, 8);printf("? SOVIET BERRIES STORE ?");
    gotoxy(15, 10);printf("Sistema de Gestión de Bayas Soviéticas");
    gotoxy(15, 12);printf("Desarrollado por: %s", usuarioActual);
    gotoxy(15, 13);printf("Fecha: %s", fechaVersion);
    gotoxy(15, 14);printf("Versión: %s", version);
    gotoxy(15, 16);printf("«???????? ?? ????????? ????»");
    gotoxy(15, 18);printf("Todos los derechos reservados ?");
    getch();
}

void convertirMayusculas(char *texto) {
    int i;
    for(i = 0; texto[i]; i++) {
        texto[i] = toupper(texto[i]);
    }
}

int validarNumero() {
    int numero;
    while(scanf("%d", &numero) != 1) {
        printf("\nError: Ingrese solo números, Camarada: ");
        fflush(stdin);
    }
    return numero;
}

int buscarProducto(int codigo) {
    berriesProductos = fopen(archivoProductos, "rb");
    if(berriesProductos == NULL) return 0;
    
    while(fread(&productoMora, sizeof(productoMora), 1, berriesProductos)) {
        if(productoMora.codigo == codigo) {
            fclose(berriesProductos);
            return 1;
        }
    }
    fclose(berriesProductos);
    return 0;
}

void actualizarStock(int codigo, int cantidad, char tipo) {
    FILE* temp;
    int encontrado = 0;
    struct productos productoTemp;
    
    berriesProductos = fopen(archivoProductos, "rb");
    temp = fopen(archivoTemp, "wb");
    
    if(berriesProductos == NULL || temp == NULL) {
        if(temp) fclose(temp);
        if(berriesProductos) fclose(berriesProductos);
        return;
    }
    
    while(fread(&productoTemp, sizeof(productos), 1, berriesProductos)) {
        if(productoTemp.codigo == codigo) {
            if(tipo == 'V') {
                productoTemp.stock -= cantidad;
            } else if(tipo == 'C') {
                productoTemp.stock += cantidad;
            }
            encontrado = 1;
        }
        fwrite(&productoTemp, sizeof(productos), 1, temp);
    }
    
    fclose(berriesProductos);
    fclose(temp);
    
    remove(archivoProductos);
    rename(archivoTemp, archivoProductos);
}
