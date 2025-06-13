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
char fechaActual[] = "2025-06-13 06:34:17";
char usuarioActual[] = "zaik3u";
char usuarioSistema[] = "Comrade Manager";
char usuarioValido[] = "LEONARDO";
char claveValida[] = "1917";
char version[] = "1.0";
char fechaVersion[] = "13/06/2025";

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
    char origen[20];          // Para regiones soviéticas
    char temporada[15];       // Primavera, Verano, Otoño
    int stock;
    float precio;
    char fechaRegistro[20];   // Nuevo campo
};

struct ventas {
    int codigo;
    int codigoProducto;
    int cantidad;
    float precioVenta;
    float precio;    // Agregado para mostrarVentas
    float total;     // Agregado para mostrarVentas
    char fecha[20];          
    char usuario[30];        
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
    char telefono[15];      
    char direccion[30];      
    char fechaRegistro[20];  
};

struct usuarios {
    int codigo;
    char nombre[30];
    char usuario[20];
    char clave[30];
    char fechaCreacion[20];
    char ultimoAcceso[20];
    char tipo[15];          
};

struct importaciones {
    int codigo;
    int codigoProducto;
    int cantidad;
    float precioCompra;
    char fecha[20];         
    char proveedor[30];
    char usuario[30];       
};

// Variables globales de archivos
FILE* berriesProductos;
FILE* berriesVentas;
FILE* berriesCompras;
FILE* berriesClientes;

// Variables globales de estructuras
struct productos productoMora = {0};
struct ventas ventaMora = {0};
struct compras compraMora = {0};
struct clientes clienteMora = {0};
// Prototipos de funciones
void dibujarMarcoSovietico();
void dibujarMarcoDoble();
void dibujarMarcoSencillo();
void iniciarSesion();
void menuPrincipal();
int buscarProducto(int codigo, struct productos *producto);
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
int clienteExiste(struct clientes cliente);
int productoExiste(struct productos producto);
void actualizarProductoExistente(struct productos producto);
int ventaExiste(int codigo);

int main() {
    system("color 4F");
    clrscr();
    iniciarSesion();
    return 0;
}
void dibujarMarcoSovietico() {
    int i;
    
    // Esquinas con símbolo soviético
    gotoxy(3, 2); printf("%c", 201);   // +
    gotoxy(77, 2); printf("%c", 187);  // +
    gotoxy(3, 22); printf("%c", 200);  // +
    gotoxy(77, 22); printf("%c", 188); // +
    
    // Líneas horizontales dobles
    for(i = 4; i <= 76; i++) {
        gotoxy(i, 2); printf("%c", 205);  // -
        gotoxy(i, 22); printf("%c", 205); // -
    }
    
    // Líneas verticales dobles
    for(i = 3; i <= 21; i++) {
        gotoxy(3, i); printf("%c", 186);  // ¦
        gotoxy(77, i); printf("%c", 186); // ¦
    }
}

void dibujarMarcoDoble() {
    int i;
    
    // Esquinas
    gotoxy(3, 2); printf("%c", 201);   // +
    gotoxy(77, 2); printf("%c", 187);  // +
    gotoxy(3, 22); printf("%c", 200);  // +
    gotoxy(77, 22); printf("%c", 188); // +
    
    // Líneas horizontales
    for(i = 4; i <= 76; i++) {
        gotoxy(i, 2); printf("%c", 205);  // -
        gotoxy(i, 22); printf("%c", 205); // -
    }
    
    // Líneas verticales
    for(i = 3; i <= 21; i++) {
        gotoxy(3, i); printf("%c", 186);  // ¦
        gotoxy(77, i); printf("%c", 186); // ¦
    }
}

void dibujarMarcoSencillo() {
    int i;
    
    // Esquinas
    gotoxy(3, 2); printf("%c", 218);   // +
    gotoxy(77, 2); printf("%c", 191);  // +
    gotoxy(3, 22); printf("%c", 192);  // +
    gotoxy(77, 22); printf("%c", 217); // +
    
    // Líneas horizontales
    for(i = 4; i <= 76; i++) {
        gotoxy(i, 2); printf("%c", 196);  // -
        gotoxy(i, 22); printf("%c", 196); // -
    }
    
    // Líneas verticales
    for(i = 3; i <= 21; i++) {
        gotoxy(3, i); printf("%c", 179);  // ¦
        gotoxy(77, i); printf("%c", 179); // ¦
    }
}

// Función de búsqueda de producto actualizada
int buscarProducto(int codigo, struct productos *producto) {
    FILE* archivo = fopen("bayas.dat", "rb");
    if(archivo == NULL) return 0;
    
    int encontrado = 0;
    struct productos temp;
    
    while(fread(&temp, sizeof(temp), 1, archivo)) {
        if(temp.codigo == codigo) {
            *producto = temp;
            encontrado = 1;
            break;
        }
    }
    
    fclose(archivo);
    return encontrado;
}
void registrarProducto() {
    clrscr();
    system("color 2F");
    dibujarMarcoSovietico();
    
    gotoxy(25, 4); printf("? REGISTRO DE BAYAS ?");
    gotoxy(20, 6); printf("Código[    ]");
    gotoxy(20, 7); printf("Nombre[                 ]");
    gotoxy(20, 8); printf("Región[                 ]");
    gotoxy(20, 9); printf("Temporada[              ]");
    gotoxy(20, 10); printf("Stock (gramos)[         ]");
    gotoxy(20, 11); printf("Precio (?)[            ]");
    
    char continuar;
    FILE* berriesProductos = fopen("bayas.dat", "ab+");
    
    if(berriesProductos == NULL) {
        gotoxy(20, 15); printf("? Error al abrir el archivo");
        getch();
        return;
    }
    
    do {
        struct productos productoMora;
        
        gotoxy(27, 6); scanf("%d", &productoMora.codigo);
        fflush(stdin);
        gotoxy(27, 7); gets(productoMora.nombre);
        convertirMayusculas(productoMora.nombre);
        gotoxy(27, 8); gets(productoMora.origen);
        convertirMayusculas(productoMora.origen);
        gotoxy(30, 9); gets(productoMora.temporada);
        convertirMayusculas(productoMora.temporada);
        
        do {
            gotoxy(34, 10); scanf("%d", &productoMora.stock);
            if(productoMora.stock <= 0) {
                gotoxy(20, 15); printf("? El stock debe ser mayor a 0");
                gotoxy(34, 10); printf("         ");
                continue;
            }
            break;
        } while(1);
        
        do {
            gotoxy(31, 11); scanf("%f", &productoMora.precio);
            if(productoMora.precio <= 0) {
                gotoxy(20, 15); printf("? El precio debe ser mayor a 0");
                gotoxy(31, 11); printf("            ");
                continue;
            }
            break;
        } while(1);
        
        fflush(stdin);
        strcpy(productoMora.fechaRegistro, fechaActual);
        
        if(productoExiste(productoMora)) {
            gotoxy(20, 15); printf("? Esta baya ya está registrada");
            gotoxy(20, 16); printf("¿Desea sumar al stock existente? (S/N)[ ]");
            char respuesta;
            gotoxy(53, 16); scanf("%c", &respuesta);
            fflush(stdin);
            
            if(toupper(respuesta) == 'S') {
                actualizarProductoExistente(productoMora);
                gotoxy(20, 17); printf("? Stock actualizado exitosamente");
                getch();
            }
            gotoxy(20, 15); printf("                                ");
            gotoxy(20, 16); printf("                                        ");
            gotoxy(20, 17); printf("                                ");
            continue;
        }
        
        fwrite(&productoMora, sizeof(productoMora), 1, berriesProductos);
        
        gotoxy(20, 15); printf("? Baya registrada exitosamente");
        gotoxy(20, 16); printf("¿Registrar otra baya? (S/N)[ ]");
        gotoxy(47, 16); scanf("%c", &continuar);
        fflush(stdin);
        
        // Limpiar campos
        gotoxy(27, 6); printf("    ");
        gotoxy(27, 7); printf("                 ");
        gotoxy(27, 8); printf("                 ");
        gotoxy(30, 9); printf("              ");
        gotoxy(34, 10); printf("         ");
        gotoxy(31, 11); printf("            ");
        gotoxy(20, 15); printf("                                ");
        gotoxy(20, 16); printf("                                ");
        
    } while(toupper(continuar) == 'S');
    
    fclose(berriesProductos);
}

void registrarVenta() {
    clrscr();
    system("color 4F");
    dibujarMarcoSovietico();
    
    gotoxy(25, 4); printf("? REGISTRO DE VENTAS ?");
    
    char continuar;
    FILE* berriesVentas = fopen("ventas.dat", "ab+");
    
    if(berriesVentas == NULL) {
        gotoxy(20, 15); printf("? Error al abrir el archivo");
        getch();
        return;
    }
    
    do {
        struct ventas ventaMora;
        struct productos productoMora;
        
        gotoxy(20, 6); printf("Código de venta[    ]");
        gotoxy(36, 6); scanf("%d", &ventaMora.codigo);
        fflush(stdin);
        
        if(ventaExiste(ventaMora.codigo)) {
            gotoxy(20, 15); printf("? Este código de venta ya existe");
            getch();
            gotoxy(36, 6); printf("    ");
            gotoxy(20, 15); printf("                                ");
            continue;
        }
        
        gotoxy(20, 7); printf("Código de baya[    ]");
        gotoxy(35, 7); scanf("%d", &ventaMora.codigoProducto);
        
        if(!buscarProducto(ventaMora.codigoProducto, &productoMora)) {
            gotoxy(20, 15); printf("? Baya no encontrada");
            getch();
            continue;
        }
        
        gotoxy(20, 9); printf("Stock disponible: %d gramos", productoMora.stock);
        gotoxy(20, 10); printf("Cantidad a vender[         ]");
        gotoxy(38, 10); scanf("%d", &ventaMora.cantidad);
        
        if(ventaMora.cantidad > productoMora.stock) {
            gotoxy(20, 15); printf("? Stock insuficiente");
            getch();
            continue;
        }
        
        ventaMora.precio = productoMora.precio;
        ventaMora.total = (ventaMora.cantidad / 100.0) * ventaMora.precio;
        strcpy(ventaMora.fecha, fechaActual);
        strcpy(ventaMora.usuario, usuarioActual);
        
        fwrite(&ventaMora, sizeof(ventaMora), 1, berriesVentas);
        actualizarStock(ventaMora.codigoProducto, ventaMora.cantidad, 'V');
        
        gotoxy(20, 15); printf("? Venta registrada exitosamente");
        gotoxy(20, 16); printf("¿Registrar otra venta? (S/N)[ ]");
        gotoxy(47, 16); scanf("%c", &continuar);
        fflush(stdin);
        
        // Limpiar campos
        gotoxy(36, 6); printf("    ");
        gotoxy(35, 7); printf("    ");
        gotoxy(20, 9); printf("                                    ");
        gotoxy(38, 10); printf("         ");
        gotoxy(20, 15); printf("                                    ");
        gotoxy(20, 16); printf("                                    ");
        
    } while(toupper(continuar) == 'S');
    
    fclose(berriesVentas);
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
        
        struct productos productoTemp;
        
        gotoxy(20, 9);printf("Código de importación: ");
        compraMora.codigo = validarNumero();
        
        gotoxy(20, 10);printf("Fecha (DD/MM/AAAA): ");
        fflush(stdin);
        gets(compraMora.fecha);
        
        gotoxy(20, 11);printf("Código de baya: ");
        compraMora.codProducto = validarNumero();
        
        if(buscarProducto(compraMora.codProducto, &productoTemp)) {
            gotoxy(20, 12);printf("Baya: %s", productoTemp.nombre);
            gotoxy(20, 13);printf("Stock actual: %dg", productoTemp.stock);
            
            gotoxy(20, 14);printf("Proveedor soviético: ");
            fflush(stdin);
            gets(compraMora.proveedor);
            convertirMayusculas(compraMora.proveedor);
            
            do {
                gotoxy(20, 15);printf("Cantidad a importar (gramos): ");
                compraMora.cantidad = validarNumero();
                if(compraMora.cantidad <= 0) {
                    gotoxy(20, 17);printf("? La cantidad debe ser mayor a 0");
                    getch();
                    gotoxy(20, 15);printf("                                          ");
                    gotoxy(20, 17);printf("                                          ");
                    continue;
                }
                break;
            } while(1);
            
            do {
                gotoxy(20, 16);printf("Precio de compra por 100g: %c", moneda);
                scanf("%f", &compraMora.precioProveedor);
                if(compraMora.precioProveedor <= 0) {
                    gotoxy(20, 17);printf("? El precio debe ser mayor a 0");
                    getch();
                    gotoxy(20, 16);printf("                                          ");
                    gotoxy(20, 17);printf("                                          ");
                    continue;
                }
                break;
            } while(1);
            
            compraMora.total = (compraMora.cantidad / 100.0) * compraMora.precioProveedor;
            
            gotoxy(20, 17);printf("Total: %c%.2f", moneda, compraMora.total);
            
            fwrite(&compraMora, sizeof(compraMora), 1, berriesCompras);
            fclose(berriesCompras);
            
            actualizarStock(compraMora.codProducto, compraMora.cantidad, 'C');
            
            gotoxy(20, 19);printf("? Importación registrada exitosamente!");
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
    clrscr();
    system("color 6F");
    dibujarMarcoSovietico();
    
    gotoxy(25, 4); printf("? REGISTRO DE CAMARADAS ?");
    gotoxy(20, 6); printf("Código[    ]");
    gotoxy(20, 7); printf("Nombre[                 ]");
    gotoxy(20, 8); printf("Ciudad[                 ]");
    gotoxy(20, 9); printf("Teléfono[              ]");
    gotoxy(20, 10); printf("Dirección[                           ]");
    
    char continuar;
    FILE* berriesClientes = fopen("clientes.dat", "ab+");
    
    if(berriesClientes == NULL) {
        gotoxy(20, 15); printf("? Error al abrir el archivo");
        getch();
        return;
    }
    
    do {
        struct clientes clienteMora;
        
        gotoxy(27, 6); scanf("%d", &clienteMora.codigo);
        fflush(stdin);
        gotoxy(27, 7); gets(clienteMora.nombre);
        convertirMayusculas(clienteMora.nombre);
        gotoxy(27, 8); gets(clienteMora.ciudad);
        convertirMayusculas(clienteMora.ciudad);
        gotoxy(29, 9); gets(clienteMora.telefono);
        gotoxy(30, 10); gets(clienteMora.direccion);
        convertirMayusculas(clienteMora.direccion);
        strcpy(clienteMora.fechaRegistro, fechaActual);
        
        if(clienteExiste(clienteMora)) {
            gotoxy(20, 15); printf("? ¡Este camarada ya está registrado!");
            getch();
            // Limpiar campos
            gotoxy(27, 6); printf("    ");
            gotoxy(27, 7); printf("                 ");
            gotoxy(27, 8); printf("                 ");
            gotoxy(29, 9); printf("              ");
            gotoxy(30, 10); printf("                           ");
            gotoxy(20, 15); printf("                                    ");
            continue;
        }
        
        fwrite(&clienteMora, sizeof(clienteMora), 1, berriesClientes);
        
        gotoxy(20, 15); printf("? Camarada registrado exitosamente");
        gotoxy(20, 16); printf("¿Registrar otro camarada? (S/N)[ ]");
        gotoxy(49, 16); scanf("%c", &continuar);
        fflush(stdin);
        
        // Limpiar campos
        gotoxy(27, 6); printf("    ");
        gotoxy(27, 7); printf("                 ");
        gotoxy(27, 8); printf("                 ");
        gotoxy(29, 9); printf("              ");
        gotoxy(30, 10); printf("                           ");
        gotoxy(20, 15); printf("                                    ");
        gotoxy(20, 16); printf("                                    ");
        
    } while(toupper(continuar) == 'S');
    
    fclose(berriesClientes);
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
               ventaMora.codigoProducto, ventaMora.cantidad,
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
    system("color 7C");
    dibujarMarcoSovietico();
    
    gotoxy(15, 8);printf("Desarrollado por");
    gotoxy(15, 9);printf("---------------------------");
    gotoxy(15, 10);printf("Leonardo -");
    gotoxy(15, 11);printf("--------------------------");
    gotoxy(15, 12);printf("Marcos");
    gotoxy(15, 13);printf("---------------------------");
    gotoxy(15, 14);printf("Gracias por usar nuestro programa!");
    getch();
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
    
    if(encontrado) {
        remove(archivoProductos);
        rename(archivoTemp, archivoProductos);
    } else {
        remove(archivoTemp);
    }
}
// Actualizar las variables globales con los nuevos valores


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

int ventaExiste(int codigo) {
    FILE* archivo = fopen("ventas.dat", "rb");
    if(archivo == NULL) return 0;
    
    struct ventas temp;
    while(fread(&temp, sizeof(temp), 1, archivo)) {
        if(temp.codigo == codigo) {
            fclose(archivo);
            return 1;
        }
    }
    fclose(archivo);
    return 0;
}

int productoExiste(struct productos producto) {
    FILE* archivo = fopen("bayas.dat", "rb");
    if(archivo == NULL) return 0;
    
    struct productos temp;
    while(fread(&temp, sizeof(temp), 1, archivo)) {
        if(strcmp(temp.nombre, producto.nombre) == 0) {
            fclose(archivo);
            return 1;
        }
    }
    fclose(archivo);
    return 0;
}

int clienteExiste(struct clientes cliente) {
    FILE* archivo = fopen("clientes.dat", "rb");
    if(archivo == NULL) return 0;
    
    struct clientes temp;
    while(fread(&temp, sizeof(temp), 1, archivo)) {
        if(strcmp(temp.nombre, cliente.nombre) == 0 && 
           strcmp(temp.telefono, cliente.telefono) == 0) {
            fclose(archivo);
            return 1;
        }
    }
    fclose(archivo);
    return 0;
}

void actualizarProductoExistente(struct productos producto) {
    FILE* archivo = fopen("bayas.dat", "rb+");
    if(archivo == NULL) return;
    
    struct productos temp;
    int pos = 0;
    
    while(fread(&temp, sizeof(temp), 1, archivo)) {
        if(strcmp(temp.nombre, producto.nombre) == 0) {
            temp.stock += producto.stock;
            // Actualizar precio solo si es diferente y mayor que 0
            if(producto.precio > 0) {
                temp.precio = producto.precio;
            }
            fseek(archivo, pos * sizeof(struct productos), SEEK_SET);
            fwrite(&temp, sizeof(temp), 1, archivo);
            break;
        }
        pos++;
    }
    fclose(archivo);
}

void iniciarSesion() {
    char usuario[20], clave[20];
    int intentos = 0, acceso = 0;
    
    while(intentos < maxIntentos && !acceso) {
        clrscr();
        system("color 9F");
        dibujarMarcoSovietico();
        
        gotoxy(25, 10);
        printf("? Tienda De Bayas Soviéticas ?");
        gotoxy(20, 12);
        printf("Camarada: ");
        gotoxy(20, 13);
        printf("Código de acceso: ");
        
        gotoxy(30, 12);
        gets(usuario);
        convertirMayusculas(usuario);
        
        gotoxy(37, 13);
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
            printf("? Acceso Denegado. Intento %d/%d ", intentos, maxIntentos);
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
        
        gotoxy(30, 7);printf("? MENU PRINCIPAL ?");
        gotoxy(21, 9);printf("1  Registrar Bayas");
        gotoxy(21, 10);printf("2  Registrar Venta");
        gotoxy(21, 11);printf("3  Registrar Importación");
        gotoxy(21, 12);printf("4  Registrar Camarada");
        gotoxy(21, 13);printf("5  Inventario de Bayas");
        gotoxy(21, 14);printf("6  Historial de Ventas");
        gotoxy(21, 15);printf("7  Historial de Importaciones");
        gotoxy(21, 16);printf("8  Lista de Camaradas");
        gotoxy(21, 17);printf("9  Sobre Nosotros");
        gotoxy(21, 18);printf("0  Salir");
        
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
