#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

// Estructuras de datos
FILE* productos;
struct prendas {
    int codigo;
    char descripcion[30];
    int stock;
    float precio;
} prenda;

FILE* ventas_ropa;
struct venta_boutique {
    int folio;
    char fecha[11];
    int cod_prenda;
    int cantidad;
    float precio;
    float total;
} venta;

FILE* inventario_entrada;
struct entrada_mercancia {
    int folio;
    char fecha[11];
    int cod_prenda;
    int cantidad;
    float precio_compra;
    float total;
} entrada;

FILE* clientes_boutique;
struct cliente {
    int codigo;
    char nombre[30];
    char fecha_registro[11];
} cliente;

FILE* empleados;
struct usuario {
    char nombre[20];
    char password[20];
} empleado;

FILE* configuracion;
struct tema {
    int color_fondo;
    int color_texto;
} temaActual = {0, 15}; // Negro fondo, blanco texto por defecto

// Variables globales
int color_actual = 15;

// Prototipos de funciones
void diseno_ventana();
void inicio_sesion();
void menu_boutique();
void registrar_prenda();
void registrar_venta();
void registrar_entrada();
void registrar_cliente();
void mostrar_prendas();
void mostrar_ventas();
void mostrar_entradas();
void mostrar_clientes();
void personalizar_tema();
void cargar_tema();
void guardar_tema();
int buscar_prenda(int codigo);
void convertir_mayusculas(char *cadena);
int validar_numero();

int main() {
    system("color 07"); // Fondo negro, texto gris claro - Pantalla inicial
    cargar_tema();
    textbackground(temaActual.color_fondo);
    textcolor(temaActual.color_texto);
    clrscr();
    inicio_sesion();
    return 0;
}

void diseno_ventana() {
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
    printf("SISTEMA DE BOUTIQUE");
    gotoxy(28, 5);
    printf("======================");
}

void inicio_sesion() {
    char usuario[20];
    char clave[20];
    int intentos = 0, acceso = 0;
    
    while(intentos < 3 && !acceso) {
        system("color 0B"); // Fondo negro, texto aguamarina - Login
        clrscr();
        diseno_ventana();
        
        gotoxy(25, 10);
        printf("ACCESO AL SISTEMA");
        gotoxy(20, 12);
        printf("Usuario: ");
        gotoxy(20, 13);
        printf("Clave: ");
        
        gotoxy(29, 12);
        gets(usuario);
        convertir_mayusculas(usuario);
        
        gotoxy(28, 13);
        gets(clave);
        
        if(strcmp(usuario, "CHICAS") == 0 && strcmp(clave, "1234") == 0) {
            acceso = 1;
            gotoxy(25, 16);
            printf("Bienvenido al sistema!");
            getch();
            menu_boutique();
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
void menu_boutique() {
    int opcion;
    
    do {
        system("color F5"); // Fondo blanco brillante, texto púrpura - Menú Principal
        clrscr();
        diseno_ventana();
        
        gotoxy(30, 7);
        printf("MENU PRINCIPAL");
        gotoxy(20, 9);
        printf("1. Registrar Prenda");
        gotoxy(20, 10);
        printf("2. Registrar Venta");
        gotoxy(20, 11);
        printf("3. Registrar Entrada de Mercancia");
        gotoxy(20, 12);
        printf("4. Registrar Cliente");
        gotoxy(20, 13);
        printf("5. Mostrar Prendas");
        gotoxy(20, 14);
        printf("6. Mostrar Ventas");
        gotoxy(20, 15);
        printf("7. Mostrar Entradas");
        gotoxy(20, 16);
        printf("8. Mostrar Clientes");
        gotoxy(20, 17);
        printf("9. Personalizar Tema");
        gotoxy(20, 18);
        printf("0. Salir");
        
        gotoxy(20, 20);
        printf("Seleccione una opcion (0-9): ");
        opcion = validar_numero();
        
        switch(opcion) {
            case 1: registrar_prenda(); break;
            case 2: registrar_venta(); break;
            case 3: registrar_entrada(); break;
            case 4: registrar_cliente(); break;
            case 5: mostrar_prendas(); break;
            case 6: mostrar_ventas(); break;
            case 7: mostrar_entradas(); break;
            case 8: mostrar_clientes(); break;
            case 9: personalizar_tema(); break;
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

void registrar_prenda() {
    char continuar;
    
    do {
        system("color D0"); // Fondo púrpura claro, texto negro - Registro de Prendas
        clrscr();
        diseno_ventana();
        
        gotoxy(28, 7);
        printf("REGISTRAR PRENDA");
        
        productos = fopen("prendas.dat", "ab");
        if(productos == NULL) {
            gotoxy(20, 10);
            printf("Error al abrir archivo");
            getch();
            return;
        }
        
        gotoxy(20, 10);
        printf("Codigo: ");
        prenda.codigo = validar_numero();
        
        gotoxy(20, 11);
        printf("Descripcion: ");
        fflush(stdin);
        gets(prenda.descripcion);
        convertir_mayusculas(prenda.descripcion);
        
        gotoxy(20, 12);
        printf("Stock: ");
        prenda.stock = validar_numero();
        
        gotoxy(20, 13);
        printf("Precio: ");
        scanf("%f", &prenda.precio);
        
        fwrite(&prenda, sizeof(prenda), 1, productos);
        fclose(productos);
        
        gotoxy(20, 15);
        printf("Prenda registrada exitosamente!");
        gotoxy(20, 16);
        printf("Desea agregar otra? (S/N): ");
        fflush(stdin);
        scanf("%c", &continuar);
        continuar = toupper(continuar);
        
    } while(continuar == 'S');
}

void registrar_venta() {
    char continuar;
    float precio_unitario;
    
    do {
        system("color A0"); // Fondo verde claro, texto negro - Registro de Ventas
        clrscr();
        diseno_ventana();
        
        gotoxy(30, 7);
        printf("REGISTRAR VENTA");
        
        ventas_ropa = fopen("ventas_ropa.dat", "ab");
        if(ventas_ropa == NULL) {
            gotoxy(20, 10);
            printf("Error al abrir archivo");
            getch();
            return;
        }
        
        gotoxy(20, 9);
        printf("Folio de venta: ");
        venta.folio = validar_numero();
        
        gotoxy(20, 10);
        printf("Fecha (DD/MM/AAAA): ");
        fflush(stdin);
        gets(venta.fecha);
        
        gotoxy(20, 11);
        printf("Codigo de prenda: ");
        venta.cod_prenda = validar_numero();
        
        if(buscar_prenda(venta.cod_prenda)) {
            gotoxy(20, 12);
            printf("Descripcion: %s", prenda.descripcion);
            gotoxy(20, 13);
            printf("Precio unitario: %.2f", prenda.precio);
            
            gotoxy(20, 14);
            printf("Cantidad a vender: ");
            venta.cantidad = validar_numero();
            
            if(venta.cantidad > prenda.stock) {
                gotoxy(20, 16);
                printf("No hay suficiente stock!");
                getch();
                fclose(ventas_ropa);
                continue;
            }
            
            venta.precio = prenda.precio;
            venta.total = venta.cantidad * venta.precio;
            
            gotoxy(20, 15);
            printf("Total: %.2f", venta.total);
            
            fwrite(&venta, sizeof(venta), 1, ventas_ropa);
            
            gotoxy(20, 17);
            printf("Venta registrada exitosamente!");
            gotoxy(20, 18);
            printf("NOTA: Stock NO actualizado automaticamente");
        } else {
            gotoxy(20, 12);
            printf("Prenda no encontrada!");
        }
        
        fclose(ventas_ropa);
        
        gotoxy(20, 19);
        printf("Desea registrar otra venta? (S/N): ");
        fflush(stdin);
        scanf("%c", &continuar);
        continuar = toupper(continuar);
        
    } while(continuar == 'S');
}

void registrar_entrada() {
    char continuar;
    
    do {
        system("color B0"); // Fondo aguamarina claro, texto negro - Registro de Entradas
        clrscr();
        diseno_ventana();
        
        gotoxy(30, 7);
        printf("REGISTRAR ENTRADA");
        
        inventario_entrada = fopen("inventario_entrada.dat", "ab");
        if(inventario_entrada == NULL) {
            gotoxy(20, 10);
            printf("Error al abrir archivo");
            getch();
            return;
        }
        
        gotoxy(20, 9);
        printf("Folio de entrada: ");
        entrada.folio = validar_numero();
        
        gotoxy(20, 10);
        printf("Fecha (DD/MM/AAAA): ");
        fflush(stdin);
        gets(entrada.fecha);
        
        gotoxy(20, 11);
        printf("Codigo de prenda: ");
        entrada.cod_prenda = validar_numero();
        
        if(buscar_prenda(entrada.cod_prenda)) {
            gotoxy(20, 12);
            printf("Descripcion: %s", prenda.descripcion);
            
            gotoxy(20, 13);
            printf("Cantidad a ingresar: ");
            entrada.cantidad = validar_numero();
            
            gotoxy(20, 14);
            printf("Precio de compra: ");
            scanf("%f", &entrada.precio_compra);
            
            entrada.total = entrada.cantidad * entrada.precio_compra;
            
            gotoxy(20, 15);
            printf("Total: %.2f", entrada.total);
            
            fwrite(&entrada, sizeof(entrada), 1, inventario_entrada);
            
            gotoxy(20, 17);
            printf("Entrada registrada exitosamente!");
            gotoxy(20, 18);
            printf("NOTA: Stock NO actualizado automaticamente");
        } else {
            gotoxy(20, 12);
            printf("Prenda no encontrada!");
        }
        
        fclose(inventario_entrada);
        
        gotoxy(20, 19);
        printf("Desea registrar otra entrada? (S/N): ");
        fflush(stdin);
        scanf("%c", &continuar);
        continuar = toupper(continuar);
        
    } while(continuar == 'S');
}

void registrar_cliente() {
    char continuar;
    
    do {
        system("color E0"); // Fondo amarillo claro, texto negro - Registro de Clientes
        clrscr();
        diseno_ventana();
        
        gotoxy(30, 7);
        printf("REGISTRAR CLIENTE");
        
        clientes_boutique = fopen("clientes_boutique.dat", "ab");
        if(clientes_boutique == NULL) {
            gotoxy(20, 10);
            printf("Error al abrir archivo");
            getch();
            return;
        }
        
        gotoxy(20, 10);
        printf("Codigo: ");
        cliente.codigo = validar_numero();
        
        gotoxy(20, 11);
        printf("Nombre: ");
        fflush(stdin);
        gets(cliente.nombre);
        convertir_mayusculas(cliente.nombre);
        
        gotoxy(20, 12);
        printf("Fecha de registro (DD/MM/AAAA): ");
        gets(cliente.fecha_registro);
        
        fwrite(&cliente, sizeof(cliente), 1, clientes_boutique);
        fclose(clientes_boutique);
        
        gotoxy(20, 14);
        printf("Cliente registrado exitosamente!");
        gotoxy(20, 15);
        printf("Desea agregar otro? (S/N): ");
        scanf("%c", &continuar);
        continuar = toupper(continuar);
        
    } while(continuar == 'S');
}

void mostrar_prendas() {
    float total_inventario = 0;
    int linea = 9;
    
    system("color F1"); // Fondo blanco brillante, texto azul - Mostrar Prendas
    clrscr();
    diseno_ventana();
    
    gotoxy(30, 7);
    printf("LISTADO DE PRENDAS");
    gotoxy(10, 8);
    printf("Cod  Descripcion         Stock  Precio   Total");
    
    productos = fopen("prendas.dat", "rb");
    if(productos == NULL) {
        gotoxy(20, 10);
        printf("No hay prendas registradas");
        getch();
        return;
    }
    
    while(fread(&prenda, sizeof(prenda), 1, productos)) {
        float total_prenda = prenda.stock * prenda.precio;
        gotoxy(10, linea);
        printf("%d     %-20s %d %8.2f %8.2f", 
               prenda.codigo, prenda.descripcion, prenda.stock, 
               prenda.precio, total_prenda);
        total_inventario += total_prenda;
        linea++;
    }
    
    gotoxy(10, linea + 1);
    printf("TOTAL INVENTARIO: $%.2f", total_inventario);
    
    fclose(productos);
    getch();
}

void mostrar_ventas() {
    float total_ventas = 0;
    int linea = 9;
    
    system("color F2"); // Fondo blanco brillante, texto verde - Mostrar Ventas
    clrscr();
    diseno_ventana();
    
    gotoxy(30, 7);
    printf("LISTADO DE VENTAS");
    gotoxy(7, 8);
    printf("Folio  Fecha      Cod Cant  Precio   Total");
    
    ventas_ropa = fopen("ventas_ropa.dat", "rb");
    if(ventas_ropa == NULL) {
        gotoxy(20, 10);
        printf("No hay ventas registradas");
        getch();
        return;
    }
    
    while(fread(&venta, sizeof(venta), 1, ventas_ropa)) {
        gotoxy(7, linea);
        printf("%-4d %-10s %3d %4d %8.2f %8.2f", 
               venta.folio, venta.fecha, venta.cod_prenda, 
               venta.cantidad, venta.precio, venta.total);
        total_ventas += venta.total;
        linea++;
    }
    
    gotoxy(7, linea + 1);
    printf("TOTAL VENTAS: $%.2f", total_ventas);
    
    fclose(ventas_ropa);
    getch();
}

void mostrar_entradas() {
    float total_entradas = 0;
    int linea = 9;
    
    system("color F9"); // Fondo blanco brillante, texto azul claro - Mostrar Entradas
    clrscr();
    diseno_ventana();
    
    gotoxy(30, 7);
    printf("LISTADO DE ENTRADAS");
    gotoxy(5, 8);
    printf("Folio  Fecha      Cod  Descripcion         Cant  Precio   Total");
    
    inventario_entrada = fopen("inventario_entrada.dat", "rb");
    if(inventario_entrada == NULL) {
        gotoxy(20, 10);
        printf("No hay entradas registradas");
        getch();
        return;
    }
    
    while(fread(&entrada, sizeof(entrada), 1, inventario_entrada)) {
        char descripcion_prenda[30] = "NO ENCONTRADA";
        if(buscar_prenda(entrada.cod_prenda)) {
            strcpy(descripcion_prenda, prenda.descripcion);
        }
        
        gotoxy(5, linea);
        printf("%d  %s    %d    %-20s %d %8.2f %8.2f", 
               entrada.folio, entrada.fecha, entrada.cod_prenda, 
               descripcion_prenda, entrada.cantidad, 
               entrada.precio_compra, entrada.total);
        total_entradas += entrada.total;
        linea++;
    }
    
    gotoxy(5, linea + 1);
    printf("TOTAL ENTRADAS: $%.2f", total_entradas);
    
    fclose(inventario_entrada);
    gotoxy(20, linea + 3);
    printf("Presione cualquier tecla para continuar...");
    getch();
}

void mostrar_clientes() {
    int linea = 9;
    
    system("color F5"); // Fondo blanco brillante, texto púrpura - Mostrar Clientes
    clrscr();
    diseno_ventana();
    
    gotoxy(30, 7);
    printf("LISTADO DE CLIENTES");
    gotoxy(15, 8);
    printf("Codigo  Nombre              Fecha Registro");
    
    clientes_boutique = fopen("clientes_boutique.dat", "rb");
    if(clientes_boutique == NULL) {
        gotoxy(20, 10);
        printf("No hay clientes registrados");
        getch();
        return;
    }
    
    while(fread(&cliente, sizeof(cliente), 1, clientes_boutique)) {
        gotoxy(15, linea);
        printf("%d  %-20s %s", 
               cliente.codigo, cliente.nombre, cliente.fecha_registro);
        linea++;
    }
    
    fclose(clientes_boutique);
    getch();
}

void personalizar_tema() {
    int opcion;
    
    system("color F3"); // Fondo blanco brillante, texto aguamarina - Personalizar Tema
    clrscr();
    diseno_ventana();
    
    gotoxy(28, 7);
    printf("PERSONALIZAR TEMA");
    gotoxy(20, 10);
    printf("1. Tema Claro (Negro/Blanco)");
    gotoxy(20, 11);
    printf("2. Tema Oscuro (Azul/Amarillo)");
    gotoxy(20, 12);
    printf("3. Tema Verde (Verde/Blanco)");
    gotoxy(20, 13);
    printf("4. Tema Rosa (Magenta/Blanco)");
    
    gotoxy(20, 15);
    printf("Seleccione tema (1-4): ");
    opcion = validar_numero();
    
    switch(opcion) {
        case 1:
            temaActual.color_fondo = 0;
            temaActual.color_texto = 15;
            break;
        case 2:
            temaActual.color_fondo = 1;
            temaActual.color_texto = 14;
            break;
        case 3:
            temaActual.color_fondo = 2;
            temaActual.color_texto = 15;
            break;
        case 4:
            temaActual.color_fondo = 5;
            temaActual.color_texto = 15;
            break;
        default:
            gotoxy(20, 17);
            printf("Opcion invalida");
            getch();
            return;
    }
    
    textbackground(temaActual.color_fondo);
    textcolor(temaActual.color_texto);
    guardar_tema();
    
    gotoxy(20, 17);
    printf("Configuracion guardada!");
    getch();
    clrscr();
}

void cargar_tema() {
    configuracion = fopen("configuracion.dat", "rb");
    if(configuracion != NULL) {
        fread(&temaActual, sizeof(temaActual), 1, configuracion);
        fclose(configuracion);
    }
}

void guardar_tema() {
    configuracion = fopen("configuracion.dat", "wb");
    if(configuracion != NULL) {
        fwrite(&temaActual, sizeof(temaActual), 1, configuracion);
        fclose(configuracion);
    }
}

int buscar_prenda(int codigo) {
    productos = fopen("prendas.dat", "rb");
    if(productos == NULL) return 0;
    
    while(fread(&prenda, sizeof(prenda), 1, productos)) {
        if(prenda.codigo == codigo) {
            fclose(productos);
            return 1;
        }
    }
    fclose(productos);
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
        fflush(stdin);
    }
    return numero;
}
