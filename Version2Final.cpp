#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

// Estructuras de datos
FILE* misflores;
struct flores {
    int numero;
    char tipo[30];
    int cantidad;
    float precio;
} floresarial;

FILE* missucursales;
struct sucursales {
    int numero;
    char nombre[30];
    char direccion[50];
} sucursalesarial;

FILE* misempleados;
struct empleados {
    int id;
    char nombre[30];
    int sucursal;
    float salario;
} empleadosarial;

FILE* misventas;
struct ventas {
    int numero;
    char concepto[30];
    char cliente[30];
    char articulo[30];
    int cantidad;
    float total;
} ventasarial;

// Variables globales
const int COLOR_ROSA = 13;
const int COLOR_BLANCO = 15;
int acceso;
int intentos;

// Prototipos de funciones
void dibujarMarcoLogin();
void dibujarMarcoMenu();
void dibujarMarcoTitulo(const char* titulo);
void login();
void menu_principal();
void registrar_flores();
void registrar_sucursales();
void registrar_empleados();
void registrar_ventas();
void imprimir_flores();
void imprimir_sucursales();
void imprimir_empleados();
void imprimir_ventas();
void validar_texto(char *texto);
void convertir_mayusculas(char *cadena);
void mostrar_creditos();

int main() {
    textbackground(COLOR_ROSA);
    textcolor(COLOR_BLANCO);
    clrscr();
    login();
    return 0;
}

void dibujarMarcoLogin() {
    int i;
    
    gotoxy(25, 8);
    printf("%c", 201);
    for(i = 26; i <= 54; i++) {
        gotoxy(i, 8);
        printf("%c", 205);
    }
    gotoxy(55, 8);
    printf("%c", 187);
    
    for(i = 9; i <= 15; i++) {
        gotoxy(25, i);
        printf("%c", 186);
        gotoxy(55, i);
        printf("%c", 186);
    }
    
    gotoxy(25, 16);
    printf("%c", 200);
    for(i = 26; i <= 54; i++) {
        gotoxy(i, 16);
        printf("%c", 205);
    }
    gotoxy(55, 16);
    printf("%c", 188);
    
    gotoxy(35, 10);
    printf("ACCESO AL SISTEMA");
}

void dibujarMarcoTitulo(const char* titulo) {
    int i;
    int longitud = strlen(titulo);
    int inicio = 40 - (longitud / 2);
    
    gotoxy(inicio - 2, 2);
    printf("%c", 201);
    for(i = inicio - 1; i <= inicio + longitud; i++) {
        gotoxy(i, 2);
        printf("%c", 205);
    }
    gotoxy(inicio + longitud + 1, 2);
    printf("%c", 187);
    
    gotoxy(inicio - 2, 3);
    printf("%c", 186);
    gotoxy(inicio, 3);
    printf("%s", titulo);
    gotoxy(inicio + longitud + 1, 3);
    printf("%c", 186);
    
    gotoxy(inicio - 2, 4);
    printf("%c", 200);
    for(i = inicio - 1; i <= inicio + longitud; i++) {
        gotoxy(i, 4);
        printf("%c", 205);
    }
    gotoxy(inicio + longitud + 1, 4);
    printf("%c", 188);
}

void dibujarMarcoMenu() {
    int i;
    
    gotoxy(5, 6);
    printf("%c", 201);
    for(i = 6; i <= 74; i++) {
        gotoxy(i, 6);
        printf("%c", 205);
    }
    gotoxy(75, 6);
    printf("%c", 187);
    
    for(i = 7; i <= 22; i++) {
        gotoxy(5, i);
        printf("%c", 186);
        gotoxy(75, i);
        printf("%c", 186);
    }
    
    gotoxy(5, 23);
    printf("%c", 200);
    for(i = 6; i <= 74; i++) {
        gotoxy(i, 23);
        printf("%c", 205);
    }
    gotoxy(75, 23);
    printf("%c", 188);
    
    gotoxy(5, 19);
    printf("%c", 195);
    for(i = 6; i <= 74; i++) {
        gotoxy(i, 19);
        printf("%c", 196);
    }
    gotoxy(75, 19);
    printf("%c", 180);
}

void login() {
    struct {
        char usuario[20];
        char clave[20];
    } user_input;
    int intentos = 0;
    int acceso = 0;
    char temp[20];
    
    while(intentos < 3 && acceso == 0) {
        clrscr();
        dibujarMarcoTitulo("Kristey's Flowers");
        dibujarMarcoLogin();
        
        
        do {
            gotoxy(30, 12);
            printf("Usuario: ");
            gotoxy(38, 12);
            printf("                     ");
            gotoxy(38, 12);
            fflush(stdin);
            gets(temp);
            strcpy(user_input.usuario, temp);
            convertir_mayusculas(user_input.usuario);
        } while(strlen(user_input.usuario) == 0);
        
        do {
            gotoxy(30, 14);
            printf("Clave:   ");
            gotoxy(38, 14);
            printf("                     ");
            gotoxy(38, 14);
            fflush(stdin);
            textcolor(COLOR_ROSA);
            gets(temp);
            strcpy(user_input.clave, temp);
        } while(strlen(user_input.clave) == 0);
        textcolor(COLOR_BLANCO);
        if(strcmp(user_input.usuario, "KRISTEY") == 0 && 
           strcmp(user_input.clave, "1000") == 0) {
            acceso = 1;
            gotoxy(32, 17);
            printf("Acceso concedido");
            Sleep(1000);
            menu_principal();
        } else {
            intentos++;
            gotoxy(27, 17);
            printf("                                        ");
            gotoxy(27, 17);
            printf("Datos incorrectos. Intento %i/3", intentos);
            getch();
        }
    }
    
    if(acceso == 0) {
        gotoxy(27, 17);
        printf("Sistema bloqueado. Contacte al admin");
        getch();
    }
}

void menu_principal() {
    int opcion;
    
    do {
        clrscr();
        dibujarMarcoTitulo("Kristey's Flowers");
        dibujarMarcoMenu();
        
        gotoxy(15, 9); printf("1. Registrar Flores");
        gotoxy(45, 9); printf("5. Imprimir Flores");
        gotoxy(15, 11);printf("2. Registrar Sucursales");
        gotoxy(45, 11);printf("6. Imprimir Sucursales");
        gotoxy(15, 13);printf("3. Registrar Empleados");
        gotoxy(45, 13);printf("7. Imprimir Empleados");
        gotoxy(15, 15);printf("4. Registrar Ventas");
        gotoxy(45, 15);printf("8. Imprimir Ventas");
        gotoxy(30, 17);printf("9. Creditos");
        gotoxy(30, 18);printf("0. Salir");
        
        gotoxy(20, 20);
        printf("Seleccione una opcion (0-9): ");
        gotoxy(48, 20);
        printf("                               ");
        gotoxy(48, 20);
        scanf("%i", &opcion);
        
        switch(opcion) {
            case 1: registrar_flores(); break;
            case 2: registrar_sucursales(); break;
            case 3: registrar_empleados(); break;
            case 4: registrar_ventas(); break;
            case 5: imprimir_flores(); break;
            case 6: imprimir_sucursales(); break;
            case 7: imprimir_empleados(); break;
            case 8: imprimir_ventas(); break;
            case 9: mostrar_creditos(); break;
            case 0:
                gotoxy(20, 21);
                printf("Hasta pronto");
                getch();
                break;
            default:
                gotoxy(20, 21);
                printf("Opcion invalida");
                getch();
        }
    } while(opcion != 0);
}

void registrar_flores() {
    char continuar;
    
    do {
        clrscr();
        dibujarMarcoTitulo("Kristey's Flowers");
        dibujarMarcoMenu();
        
        gotoxy(25, 8);
        printf("REGISTRO DE FLORES");
        
        misflores = fopen("flores.dat", "ab");
        if(misflores == NULL) {
            gotoxy(20, 10);
            printf("Error al abrir archivo");
            getch();
            return;
        }
        
        gotoxy(15, 10);
        printf("Numero: ");
        gotoxy(30, 10);
        printf("                               ");
        gotoxy(30, 10);
        scanf("%i", &floresarial.numero);
        
        gotoxy(15, 11);
        printf("Tipo: ");
        fflush(stdin);
        gets(floresarial.tipo);
        convertir_mayusculas(floresarial.tipo);
        
        gotoxy(15, 12);
        printf("Cantidad: ");
        gotoxy(25, 12);
        printf("                               ");
        gotoxy(25, 12);
        scanf("%i", &floresarial.cantidad);
        
        gotoxy(15, 13);
        printf("Precio: $");
        gotoxy(24, 13);
        printf("                               ");
        gotoxy(24, 13);
        scanf("%f", &floresarial.precio);
        
        fwrite(&floresarial, sizeof(floresarial), 1, misflores);
        fclose(misflores);
        
        gotoxy(15, 15);
        printf("Flor registrada exitosamente");
        gotoxy(15, 16);
        printf("Cantidad registrada: %i", floresarial.cantidad);
        gotoxy(15, 17);
        printf("Desea registrar otra flor (S/N): ");
        fflush(stdin);
        scanf("%c", &continuar);
        continuar = toupper(continuar);
        
    } while(continuar == 'S');
}

void registrar_sucursales() {
    char continuar;
    
    do {
        clrscr();
        dibujarMarcoTitulo("Kristey's Flowers");
        dibujarMarcoMenu();
        
        gotoxy(25, 8);
        printf("REGISTRO DE SUCURSALES");
        
        missucursales = fopen("sucursales.dat", "ab");
        if(missucursales == NULL) {
            gotoxy(20, 10);
            printf("Error al abrir archivo");
            getch();
            return;
        }
        
        gotoxy(15, 10);
        printf("Numero: ");
        gotoxy(30, 10);
        printf("                               ");
        gotoxy(30, 10);
        scanf("%i", &sucursalesarial.numero);
        
        gotoxy(15, 11);
        printf("Nombre: ");
        fflush(stdin);
        gets(sucursalesarial.nombre);
        convertir_mayusculas(sucursalesarial.nombre);
        
        gotoxy(15, 12);
        printf("Direccion: ");
        fflush(stdin);
        gets(sucursalesarial.direccion);
        convertir_mayusculas(sucursalesarial.direccion);
        
        fwrite(&sucursalesarial, sizeof(sucursalesarial), 1, missucursales);
        fclose(missucursales);
        
        gotoxy(15, 14);
        printf("Sucursal registrada exitosamente");
        gotoxy(15, 15);
        printf("Desea registrar otra sucursal (S/N): ");
        fflush(stdin);
        scanf("%c", &continuar);
        continuar = toupper(continuar);
        
    } while(continuar == 'S');
}

void registrar_empleados() {
    char continuar;
    
    do {
        clrscr();
        dibujarMarcoTitulo("Kristey's Flowers");
        dibujarMarcoMenu();
        
        gotoxy(25, 8);
        printf("REGISTRO DE EMPLEADOS");
        
        misempleados = fopen("empleados.dat", "ab");
        if(misempleados == NULL) {
            gotoxy(20, 10);
            printf("Error al abrir archivo");
            getch();
            return;
        }
        
        gotoxy(15, 10);
        printf("ID del empleado: ");
        gotoxy(30, 10);
        printf("                               ");
        gotoxy(30, 10);
        scanf("%i", &empleadosarial.id);
        
        gotoxy(15, 11);
        printf("Nombre: ");
        fflush(stdin);
        gets(empleadosarial.nombre);
        convertir_mayusculas(empleadosarial.nombre);
        
        gotoxy(15, 12);
        printf("Numero de sucursal: ");
        gotoxy(34, 12);
        printf("                               ");
        gotoxy(34, 12);
        scanf("%i", &empleadosarial.sucursal);
        
        gotoxy(15, 13);
        printf("Salario: $");
        gotoxy(25, 13);
        printf("                               ");
        gotoxy(25, 13);
        scanf("%f", &empleadosarial.salario);
        
        fwrite(&empleadosarial, sizeof(empleadosarial), 1, misempleados);
        fclose(misempleados);
        
        gotoxy(15, 15);
        printf("Empleado registrado exitosamente");
        gotoxy(15, 16);
        printf("Desea registrar otro empleado (S/N): ");
        fflush(stdin);
        scanf("%c", &continuar);
        continuar = toupper(continuar);
        
    } while(continuar == 'S');
}

void registrar_ventas() {
    char continuar;
    float precio_unitario;
    int encontrado;
    int numero_flor;
    
    do {
        clrscr();
        dibujarMarcoTitulo("Kristey's Flowers");
        dibujarMarcoMenu();
        
        gotoxy(25, 8);
        printf("REGISTRO DE VENTAS");
        
        misventas = fopen("ventas.dat", "ab");
        if(misventas == NULL) {
            gotoxy(20, 10);
            printf("Error al abrir archivo");
            getch();
            return;
        }
        
        gotoxy(15, 10);
        printf("Numero de venta: ");
        gotoxy(31, 10);
        printf("                               ");
        gotoxy(31, 10);
        scanf("%i", &ventasarial.numero);
        
        gotoxy(15, 11);
        printf("Concepto: ");
        fflush(stdin);
        gets(ventasarial.concepto);
        convertir_mayusculas(ventasarial.concepto);
        
        gotoxy(15, 12);
        printf("Cliente: ");
        fflush(stdin);
        gets(ventasarial.cliente);
        convertir_mayusculas(ventasarial.cliente);
        
        gotoxy(15, 13);
        printf("Numero de flor: ");
        gotoxy(30, 13);
        printf("                               ");
        gotoxy(30, 13);
        scanf("%i", &numero_flor);
        
        // Buscar flor por número
        encontrado = 0;
        precio_unitario = 0;
        misflores = fopen("flores.dat", "rb");
        if(misflores != NULL) {
            while(fread(&floresarial, sizeof(floresarial), 1, misflores)) {
                if(floresarial.numero == numero_flor) {
                    precio_unitario = floresarial.precio;
                    strcpy(ventasarial.articulo, floresarial.tipo);
                    encontrado = 1;
                    break;
                }
            }
            fclose(misflores);
        }
        
        if(encontrado == 0) {
            gotoxy(15, 15);
            printf("Error: Flor no encontrada");
            gotoxy(15, 16);
        	printf("");
            getch();
            fclose(misventas);
            continue;
        }
        
        gotoxy(15, 14);
        printf("Tipo de flor: %s", ventasarial.articulo);
        
        gotoxy(15, 15);
        printf("Cantidad: ");
        gotoxy(25, 15);
        printf("                               ");
        gotoxy(25, 15);
        scanf("%i", &ventasarial.cantidad);
        
        ventasarial.total = ventasarial.cantidad * precio_unitario;
        
        gotoxy(15, 16);
        printf("Precio unitario: $%8.2f", precio_unitario);
        gotoxy(15, 17);
        printf("Total: $%8.2f", ventasarial.total);
        
        fwrite(&ventasarial, sizeof(ventasarial), 1, misventas);
        fclose(misventas);
        
        gotoxy(15, 19);
        printf("Desea registrar otra venta (S/N): ");
        fflush(stdin);
        scanf("%c", &continuar);
        continuar = toupper(continuar);
        
    } while(continuar == 'S');
}

void imprimir_flores() {
    int linea;
    float total_inventario;
    
    clrscr();
    dibujarMarcoTitulo("Kristey's Flowers");
    dibujarMarcoMenu();
    
    gotoxy(25, 8);
    printf("LISTADO DE FLORES");
    gotoxy(8, 10);
    printf("Num   Tipo                Cantidad   Precio");
    
    misflores = fopen("flores.dat", "rb");
    if(misflores == NULL) {
        gotoxy(20, 12);
        printf("No hay flores registradas");
        getch();
        return;
    }
    
    linea = 11;
    total_inventario = 0;
    
    while(fread(&floresarial, sizeof(floresarial), 1, misflores)) {
        gotoxy(8, linea);
        printf("%i     %-20s %i          %8.2f", floresarial.numero, floresarial.tipo, floresarial.cantidad,floresarial.precio);
        total_inventario += floresarial.cantidad * floresarial.precio;
        linea++;
    }
    
    fclose(misflores);
    gotoxy(8, linea + 1);
    printf("Total Inventario: $%8.2f", total_inventario);
    gotoxy(8, linea + 3);
printf("");
    getch();
}

void imprimir_sucursales() {
    int linea;
    
    clrscr();
    dibujarMarcoTitulo("Kristey's Flowers");
    dibujarMarcoMenu();
    
    gotoxy(25, 8);
    printf("LISTADO DE SUCURSALES");
    gotoxy(8, 10);
    printf("Num   Nombre              Direccion");
    
    missucursales = fopen("sucursales.dat", "rb");
    if(missucursales == NULL) {
        gotoxy(20, 12);
        printf("No hay sucursales registradas");
        getch();
        return;
    }
    
    linea = 11;
    while(fread(&sucursalesarial, sizeof(sucursalesarial), 1, missucursales)) {
        gotoxy(8, linea);
        printf("%i     %-20s %s", 
               sucursalesarial.numero, 
               sucursalesarial.nombre, 
               sucursalesarial.direccion);
        linea++;
    }
    
    fclose(missucursales);
    gotoxy(8, linea + 2);
printf("");
    getch();
}

void imprimir_empleados() {
    int linea;
    
    clrscr();
    dibujarMarcoTitulo("Kristey's Flowers");
    dibujarMarcoMenu();
    
    gotoxy(25, 8);
    printf("LISTADO DE EMPLEADOS");
    gotoxy(8, 10);
    printf("ID    Nombre              Sucursal    Salario");
    
    misempleados = fopen("empleados.dat", "rb");
    if(misempleados == NULL) {
        gotoxy(20, 12);
        printf("No hay empleados registrados");
        getch();
        return;
    }
    
    linea = 11;
    while(fread(&empleadosarial, sizeof(empleadosarial), 1, misempleados)) {
        gotoxy(8, linea);
        printf("%i     %-20s %i          %8.2f", 
               empleadosarial.id, 
               empleadosarial.nombre, 
               empleadosarial.sucursal,
               empleadosarial.salario);
        linea++;
    }
    
    fclose(misempleados);
    gotoxy(8, linea + 2);
    printf("Presione una tecla para continuar");
    getch();
}

void imprimir_ventas() {
    int linea;
    float total_ventas;
    
    clrscr();
    dibujarMarcoTitulo("Kristey's Flowers");
    dibujarMarcoMenu();
    
    gotoxy(25, 8);
    printf("LISTADO DE VENTAS");
    gotoxy(8, 10);
    printf("Num   Concepto    Cliente     Articulo    Cant   Total");
    
    misventas = fopen("ventas.dat", "rb");
    if(misventas == NULL) {
        gotoxy(20, 12);
        printf("No hay ventas registradas");
        getch();
        return;
    }
    
    linea = 11;
    total_ventas = 0;
    
    while(fread(&ventasarial, sizeof(ventasarial), 1, misventas)) {
        gotoxy(8, linea);
        printf("%i     %-11s %-11s %-11s %i      %8.2f", 
               ventasarial.numero,
               ventasarial.concepto,
               ventasarial.cliente,
               ventasarial.articulo,
               ventasarial.cantidad,
               ventasarial.total);
               
        total_ventas = total_ventas + ventasarial.total;
        linea++;
    }
    
    fclose(misventas);
    gotoxy(8, linea + 1);
    printf("Total General de Ventas: $%8.2f", total_ventas);
    gotoxy(8, linea + 3);
    printf("Presione una tecla para continuar");
    getch();
}

void convertir_mayusculas(char *cadena) {
    int i;
    for(i = 0; cadena[i]; i++) {
        if(cadena[i] >= 'a' && cadena[i] <= 'z') {
            cadena[i] = cadena[i] - 32;
        }
    }
}

void validar_texto(char *texto) {
    int i;
    char temp[50];
    
    strcpy(temp, texto);
    for(i = 0; temp[i]; i++) {
        if(temp[i] >= '0' && temp[i] <= '9') {
            gotoxy(15, 20);
            printf("Error: No se permiten numeros en este campo");
            gotoxy(15, 21);
            printf("Presione una tecla para continuar");
            getch();
            gotoxy(15, 20);
            printf("                                           ");
            gotoxy(15, 21);
            printf("                                           ");
            fflush(stdin);
            gets(texto);
            strcpy(temp, texto);
            i = -1;
        }
    }
}

void mostrar_creditos() {
    clrscr();
    dibujarMarcoTitulo("Kristey's Flowers");
    dibujarMarcoMenu();
    
    // Título
    gotoxy(35, 8);
    printf("%c%c%c INTEGRANTES %c%c%c", 175, 175, 175, 174, 174, 174);
    
    // Marco decorativo para los nombres
    int i;
    gotoxy(20, 10);
    printf("%c", 201);
    for(i = 0; i < 40; i++) printf("%c", 205);
    printf("%c", 187);
    
    for(i = 11; i < 15; i++) {
        gotoxy(20, i);
        printf("%c", 186);
        gotoxy(61, i);
        printf("%c", 186);
    }
    
    gotoxy(20, 15);
    printf("%c", 200);
    for(i = 0; i < 40; i++) printf("%c", 205);
    printf("%c", 188);
    
    // Nombres de los integrantes
    gotoxy(22, 11);
    printf("%c Ruiz Pena Hilen Rebeca", 4);
    gotoxy(22, 12);
    printf("%c Vazquez Ibarra Aneth Citlali", 4);
    gotoxy(22, 13);
    printf("%c Morales Blanco Kristey Adilene", 4);
    
    // Decoración adicional
  
    // Mensaje para salir
    gotoxy(25, 20);
    getch();
}
