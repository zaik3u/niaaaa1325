#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

void diseno_ventana();
void menu_boutique();
void registrar_prenda();
void registrar_venta();
void registrar_entrada();
void registrar_cliente();
void mostrar_prendas();
void mostrar_ventas();
void mostrar_entradas();
void mostrar_clientes();
void convertir_mayusculas(char *cadena);

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

void diseno_ventana() {
    int i;
    
    // Marco superior
    gotoxy(5, 3);
    printf("%c", 201);  // +
    for(i = 0; i < 69; i++) {
        printf("%c", 205);  // -
    }
    printf("%c", 187);  // +
    
    // Marcos laterales
    for(i = 4; i <= 21; i++) {
        gotoxy(5, i);
        printf("%c", 186);  // ¦
        gotoxy(75, i);
        printf("%c", 186);  // ¦
    }
    
    // Marco inferior
    gotoxy(5, 22);
    printf("%c", 200);  // +
    for(i = 0; i < 69; i++) {
        printf("%c", 205);  // -
    }
    printf("%c", 188);  // +
    
    // Título
    gotoxy(30, 4);
    printf("BOUTIQUE ELEGANTE");
    gotoxy(28, 5);
    for(i = 0; i < 18; i++) {
        printf("%c", 205);  // -
    }
}
void menu_boutique() {
    int opcion;
    
    do {
        system("cls");
        diseno_ventana();
        
        gotoxy(25, 7);
        printf("+------- MENU PRINCIPAL -------+");
        gotoxy(25, 9);
        printf("1. Registrar Prenda");
        gotoxy(25, 10);
        printf("2. Registrar Venta");
        gotoxy(25, 11);
        printf("3. Registrar Entrada");
        gotoxy(25, 12);
        printf("4. Registrar Cliente");
        gotoxy(25, 13);
        printf("5. Mostrar Prendas");
        gotoxy(25, 14);
        printf("6. Mostrar Ventas");
        gotoxy(25, 15);
        printf("7. Mostrar Entradas");
        gotoxy(25, 16);
        printf("8. Mostrar Clientes");
        gotoxy(25, 17);
        printf("0. Salir");
        gotoxy(25, 19);
        printf("+----------------------------+");
        
        gotoxy(25, 20);
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        
        switch(opcion) {
            case 1: registrar_prenda(); break;
            case 2: registrar_venta(); break;
            case 3: registrar_entrada(); break;
            case 4: registrar_cliente(); break;
            case 5: mostrar_prendas(); break;
            case 6: mostrar_ventas(); break;
            case 7: mostrar_entradas(); break;
            case 8: mostrar_clientes(); break;
        }
    } while(opcion != 0);
}

void registrar_prenda() {
    char continuar;
    
    do {
        system("cls");
        diseno_ventana();
        
        gotoxy(30, 7);
        printf("REGISTRO DE PRENDA");
        
        productos = fopen("prendas.dat", "ab");
        if(productos == NULL) {
            gotoxy(20, 10);
            printf("Error al abrir archivo");
            getch();
            return;
        }
        
        gotoxy(20, 10);
        printf("Código: ");
        scanf("%d", &prenda.codigo);
        
        gotoxy(20, 11);
        printf("Descripción: ");
        scanf(" %[^\n]", prenda.descripcion);
        
        gotoxy(20, 12);
        printf("Stock: ");
        scanf("%d", &prenda.stock);
        
        gotoxy(20, 13);
        printf("Precio: ");
        scanf("%f", &prenda.precio);
        
        fwrite(&prenda, sizeof(prenda), 1, productos);
        fclose(productos);
        
        gotoxy(20, 15);
        printf("¿Desea registrar otra prenda? (S/N): ");
        scanf(" %c", &continuar);
        
    } while(toupper(continuar) == 'S');
}

void registrar_venta() {
    char continuar;
    
    do {
        system("cls");
        diseno_ventana();
        
        gotoxy(30, 7);
        printf("REGISTRO DE VENTA");
        
        ventas_ropa = fopen("ventas_ropa.dat", "ab");
        if(ventas_ropa == NULL) {
            gotoxy(20, 10);
            printf("Error al abrir archivo");
            getch();
            return;
        }
        
        gotoxy(20, 9);
        printf("Folio: ");
        scanf("%d", &venta.folio);
        
        gotoxy(20, 10);
        printf("Fecha (DD/MM/AAAA): ");
        scanf(" %[^\n]", venta.fecha);
        
        gotoxy(20, 11);
        printf("Código de prenda: ");
        scanf("%d", &venta.cod_prenda);
        
        gotoxy(20, 12);
        printf("Cantidad: ");
        scanf("%d", &venta.cantidad);
        
        gotoxy(20, 13);
        printf("Precio: ");
        scanf("%f", &venta.precio);
        
        venta.total = venta.cantidad * venta.precio;
        
        gotoxy(20, 14);
        printf("Total: %.2f", venta.total);
        
        fwrite(&venta, sizeof(venta), 1, ventas_ropa);
        fclose(ventas_ropa);
        
        gotoxy(20, 16);
        printf("¿Desea registrar otra venta? (S/N): ");
        scanf(" %c", &continuar);
        
    } while(toupper(continuar) == 'S');
}

void registrar_entrada() {
    char continuar;
    
    do {
        system("cls");
        diseno_ventana();
        
        gotoxy(30, 7);
        printf("REGISTRO DE ENTRADA");
        
        inventario_entrada = fopen("inventario_entrada.dat", "ab");
        if(inventario_entrada == NULL) {
            gotoxy(20, 10);
            printf("Error al abrir archivo");
            getch();
            return;
        }
        
        gotoxy(20, 9);
        printf("Folio: ");
        scanf("%d", &entrada.folio);
        
        gotoxy(20, 10);
        printf("Fecha (DD/MM/AAAA): ");
        scanf(" %[^\n]", entrada.fecha);
        
        gotoxy(20, 11);
        printf("Código de prenda: ");
        scanf("%d", &entrada.cod_prenda);
        
        gotoxy(20, 12);
        printf("Cantidad: ");
        scanf("%d", &entrada.cantidad);
        
        gotoxy(20, 13);
        printf("Precio de compra: ");
        scanf("%f", &entrada.precio_compra);
        
        entrada.total = entrada.cantidad * entrada.precio_compra;
        
        gotoxy(20, 14);
        printf("Total: %.2f", entrada.total);
        
        fwrite(&entrada, sizeof(entrada), 1, inventario_entrada);
        fclose(inventario_entrada);
        
        gotoxy(20, 16);
        printf("¿Desea registrar otra entrada? (S/N): ");
        scanf(" %c", &continuar);
        
    } while(toupper(continuar) == 'S');
}

void registrar_cliente() {
    char continuar;
    
    do {
        system("cls");
        diseno_ventana();
        
        gotoxy(30, 7);
        printf("REGISTRO DE CLIENTE");
        
        clientes_boutique = fopen("clientes_boutique.dat", "ab");
        if(clientes_boutique == NULL) {
            gotoxy(20, 10);
            printf("Error al abrir archivo");
            getch();
            return;
        }
        
        gotoxy(20, 10);
        printf("Código: ");
        scanf("%d", &cliente.codigo);
        
        gotoxy(20, 11);
        printf("Nombre: ");
        scanf(" %[^\n]", cliente.nombre);
        
        gotoxy(20, 12);
        printf("Fecha de registro (DD/MM/AAAA): ");
        scanf(" %[^\n]", cliente.fecha_registro);
        
        fwrite(&cliente, sizeof(cliente), 1, clientes_boutique);
        fclose(clientes_boutique);
        
        gotoxy(20, 14);
        printf("¿Desea registrar otro cliente? (S/N): ");
        scanf(" %c", &continuar);
        
    } while(toupper(continuar) == 'S');
}

void mostrar_prendas() {
    float total_inventario = 0;
    int linea = 9, i;
    
    system("cls");
    diseno_ventana();
    
    gotoxy(30, 7);
    printf("LISTADO DE PRENDAS");
    
    // Marco superior de la tabla
    gotoxy(10, 8);
    printf("%c", 201);  // +
    for(i = 0; i < 5; i++) printf("%c", 205);
    printf("%c", 203);  // -
    for(i = 0; i < 16; i++) printf("%c", 205);
    printf("%c", 203);  // -
    for(i = 0; i < 6; i++) printf("%c", 205);
    printf("%c", 203);  // -
    for(i = 0; i < 8; i++) printf("%c", 205);
    printf("%c", 203);  // -
    for(i = 0; i < 9; i++) printf("%c", 205);
    printf("%c", 187);  // +
    
    // Encabezados
    gotoxy(10, 9);
    printf("%c COD %c   DESCRIPCION    %c STOCK %c PRECIO %c   TOTAL   %c",
           186,186,186,186,186,186);
    
    // Línea divisoria
    gotoxy(10, 10);
    printf("%c", 204);  // ¦
    for(i = 0; i < 5; i++) printf("%c", 205);
    printf("%c", 206);  // +
    for(i = 0; i < 16; i++) printf("%c", 205);
    printf("%c", 206);  // +
    for(i = 0; i < 6; i++) printf("%c", 205);
    printf("%c", 206);  // +
    for(i = 0; i < 8; i++) printf("%c", 205);
    printf("%c", 206);  // +
    for(i = 0; i < 9; i++) printf("%c", 205);
    printf("%c", 185);  // ¦
    
    
    productos = fopen("prendas.dat", "rb");
    if(productos == NULL) {
        gotoxy(20, 12);
        printf("No hay prendas registradas");
        getch();
        return;
    }
    
    linea = 11;
    while(fread(&prenda, sizeof(prenda), 1, productos)) {
        float total_prenda = prenda.stock * prenda.precio;
        gotoxy(10, linea);
        printf("¦ %3d ¦ %-16s ¦ %5d ¦ %6.2f ¦ %9.2f ¦", 
               prenda.codigo, prenda.descripcion, prenda.stock, 
               prenda.precio, total_prenda);
        total_inventario += total_prenda;
        linea++;
    }
    
    gotoxy(10, linea);
    printf("%c", 200);  // +
    for(i = 0; i < 5; i++) printf("%c", 205);
    printf("%c", 202);  // -
    for(i = 0; i < 16; i++) printf("%c", 205);
    printf("%c", 202);  // -
    for(i = 0; i < 6; i++) printf("%c", 205);
    printf("%c", 202);  // -
    for(i = 0; i < 8; i++) printf("%c", 205);
    printf("%c", 202);  // -
    for(i = 0; i < 9; i++) printf("%c", 205);
    printf("%c", 188);  // +

    gotoxy(10, linea + 1);
    printf("Total Inventario: $%.2f", total_inventario);
    
    fclose(productos);
    getch();
}

void mostrar_ventas() {
    float total_ventas = 0;
    int linea = 9;
    
    system("cls");
    diseno_ventana();
    
    gotoxy(30, 7);
    printf("LISTADO DE VENTAS");
    gotoxy(7, 8);
    printf("+------------------------------------------------------+");
    gotoxy(7, 9);
    printf("¦ Folio¦   Fecha    ¦ Cód. ¦ Cant.¦ Precio ¦   Total   ¦");
    gotoxy(7, 10);
    printf("¦------+------------+------+------+--------+-----------¦");
    
    ventas_ropa = fopen("ventas_ropa.dat", "rb");
    if(ventas_ropa == NULL) {
        gotoxy(20, 12);
        printf("No hay ventas registradas");
        getch();
        return;
    }
    
    linea = 11;
    while(fread(&venta, sizeof(venta), 1, ventas_ropa)) {
        gotoxy(7, linea);
        printf("¦ %4d ¦ %-10s ¦ %4d ¦ %4d ¦ %6.2f ¦ %9.2f ¦", 
               venta.folio, venta.fecha, venta.cod_prenda, 
               venta.cantidad, venta.precio, venta.total);
        total_ventas += venta.total;
        linea++;
    }
    
    gotoxy(7, linea);
    printf("+------------------------------------------------------+");
    gotoxy(7, linea + 1);
    printf("Total Ventas: $%.2f", total_ventas);
    
    fclose(ventas_ropa);
    getch();
}

void mostrar_entradas() {
    float total_entradas = 0;
    int linea = 9;
    
    system("cls");
    diseno_ventana();
    
    gotoxy(30, 7);
    printf("LISTADO DE ENTRADAS");
    gotoxy(5, 8);
    printf("+------------------------------------------------------+");
    gotoxy(5, 9);
    printf("¦ Folio¦   Fecha    ¦ Cód. ¦ Cant.¦ Precio ¦   Total   ¦");
    gotoxy(5, 10);
    printf("¦------+------------+------+------+--------+-----------¦");
    
    inventario_entrada = fopen("inventario_entrada.dat", "rb");
    if(inventario_entrada == NULL) {
        gotoxy(20, 12);
        printf("No hay entradas registradas");
        getch();
        return;
    }
    
    linea = 11;
    while(fread(&entrada, sizeof(entrada), 1, inventario_entrada)) {
        gotoxy(5, linea);
        printf("¦ %4d ¦ %-10s ¦ %4d ¦ %4d ¦ %6.2f ¦ %9.2f ¦", 
               entrada.folio, entrada.fecha, entrada.cod_prenda, 
               entrada.cantidad, entrada.precio_compra, entrada.total);
        total_entradas += entrada.total;
        linea++;
    }
    
    gotoxy(5, linea);
    printf("+------------------------------------------------------+");
    gotoxy(5, linea + 1);
    printf("Total Entradas: $%.2f", total_entradas);
    
    fclose(inventario_entrada);
    getch();
}

void mostrar_clientes() {
    int linea = 9;
    
    system("cls");
    diseno_ventana();
    
    gotoxy(30, 7);
    printf("LISTADO DE CLIENTES");
    gotoxy(10, 8);
    printf("+------------------------------------------+");
    gotoxy(10, 9);
    printf("¦ Cód. ¦       Nombre         ¦   Fecha    ¦");
    gotoxy(10, 10);
    printf("¦------+----------------------+------------¦");
    
    clientes_boutique = fopen("clientes_boutique.dat", "rb");
    if(clientes_boutique == NULL) {
        gotoxy(20, 12);
        printf("No hay clientes registrados");
        getch();
        return;
    }
    
    linea = 11;
    while(fread(&cliente, sizeof(cliente), 1, clientes_boutique)) {
        gotoxy(10, linea);
        printf("¦ %4d ¦ %-20s ¦ %-10s ¦", 
               cliente.codigo, cliente.nombre, cliente.fecha_registro);
        linea++;
    }
    
    gotoxy(10, linea);
    printf("+------------------------------------------+");
    
    fclose(clientes_boutique);
    getch();
}

int main() {
    SetConsoleTitle("BOUTIQUE ELEGANTE");
    menu_boutique();
    return 0;
}
