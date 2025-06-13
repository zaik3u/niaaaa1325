#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<windows.h>



void cuadro_nuevo() {
    gotoxy(5,2); printf("+--------------------------------------------------------------------------+");
    gotoxy(5,3); printf("|                           FRUTERIA CABEZON                               |");
    gotoxy(5,4); printf("|--------------------------------------------------------------------------|");
    gotoxy(5,20); printf("+--------------------------------------------------------------------------+");
    for(int i=5; i<20; i++) {
        gotoxy(5,i); printf("|");
        gotoxy(80,i); printf("|");
    }
}

FILE*archiventas;
struct datosv {
    int numventa;
    int numarti;
    int canventa;
    char fecha[11];
} misventas;

FILE*archicompras;
struct datoscompras {
    int numcompra;
    int numarti;
    int cancompra;
    float preciocompra;
    char fecha[11];
} miscompras;

FILE*archiarti2;
struct datosarti {
    int numarti;
    char nomarti[20];
    int cantarti;
    float precioarti;
} misarti;

FILE*persona;
struct usuarios {
    int numero;
    char nombre[20];
    char clave[30];
} usuarios;

FILE*archiclientes;
struct datosclientes {
    int numcliente;
    char nomcliente[20];
    char telefono[15];
    char direccion[30];
} misclientes;

void menu();
void registrar();
void buscar();
void articulos();
void imprimir();
void ventas();
void compras();
void imprimirventas();
void imprimircompras();
int actualiza(int numero);
int actualizacompra(int numero, int cantidad);
int buscaarti(int numero);
int buscaarti2(int numero);
void clientes();
void imprimirclientes();
void convertir_mayusculas(char*cadena);

int opor=0, indice=0, encontrado=0, cantidad=0, inventario=0;
float totalarti=0, precioarti=0;
char nomarti[20];

main() {
    clrscr();
    textcolor(14); // Amarillo
    char claveusua[20];
    
    do {
        clrscr();
        persona=fopen("usuarios.dat","r");
        if(persona == NULL) {
            clrscr();
            gotoxy(15,10);printf("Error: No se puede abrir archivo de usuarios");
            getch();
            return 1;
        }
        
        cuadro_nuevo();
        gotoxy(15,10);printf("Dame clave de Acceso: ");fflush(stdin);
        textcolor(0);gets(claveusua);
        textcolor(14);
        
        encontrado = 0;
        indice = 0;
        
        while(!feof(persona)) {
            fseek(persona,indice*sizeof(usuarios),SEEK_SET);
            if(fread(&usuarios,sizeof(usuarios),1,persona)) {
                if(strcmp(claveusua,usuarios.clave)==0) {
                    clrscr();
                    gotoxy(15,10);printf("Acceso permitido");
                    getch();
                    encontrado = 1;
                    menu();
                    break;
                }
            }
            indice++;
        }
        
        if(!encontrado) {
            opor++;
            gotoxy(15,12);printf("Clave incorrecta. Intento %d de 3", opor);
            getch();
        }
        
        fclose(persona);
        indice=0;
        
    } while(opor<3 && !encontrado);
    
    if(opor >= 3) {
        clrscr();
        gotoxy(15,10);printf("Agotaste tus intentos, no puedes acceder");
        getch();
    }
}

void menu() {
    int opc=0;
    
    do {
        clrscr();
        textcolor(11); // Cyan claro
        cuadro_nuevo();
        gotoxy(22,6);printf("Bienvenido a mi sistema");
        gotoxy(15,8);printf("1.-Registrar Articulos");
        gotoxy(15,9);printf("2.-Imprimir Articulos");
        gotoxy(15,10);printf("3.-Buscar Articulos");
        gotoxy(15,11);printf("4.-Registrar Ventas");
        gotoxy(15,12);printf("5.-Imprimir Ventas");
        gotoxy(15,13);printf("6.-Registrar compras");
        gotoxy(15,14);printf("7.-Imprimir compras");
        gotoxy(15,15);printf("8.-Registrar clientes");
        gotoxy(15,16);printf("9.-Imprimir clientes");
		gotoxy(14,17);printf("10.-Terminar");
        gotoxy(15,18);printf("Dame una opcion del 1-10[  ]");
        gotoxy(60,8);printf("Integrantes: ");
        gotoxy(60,9);printf("Int 1");
        gotoxy(60,10);printf("Int 2");
        gotoxy(60,11);printf("Int 3");
        gotoxy(40,18);scanf("%i",&opc);
        switch(opc) {
            case 1: 
				articulos(); 
				break;
            case 2: 
				clrscr(); 
				imprimir(); 
				break;
            case 3: 
				clrscr(); 
				buscar(); 
				break;
            case 4: 
				clrscr(); 
				ventas(); 
				break;
            case 5: 
				clrscr(); 
				imprimirventas(); 
				break;
            case 6: 
				clrscr(); 
				compras(); 
				break;
            case 7: 
				clrscr(); 
				imprimircompras(); 
				break;
            case 10: 
				clrscr(); 
				gotoxy(15,10);printf("Sistema cerrandose!"); 
				getch(); 
				return;
            case 8: 
				clrscr(); 
				clientes(); 
				break;
			case 9: 
				clrscr(); 
				imprimirclientes(); 
				break;
            default: 
				gotoxy(15,19);printf("Opcion invalida, presiona una tecla"); 
				getch(); 
				break;
        }
    } while(opc != 10);
}

void articulos() {
    clrscr();
    textcolor(10); // Verde claro
    cuadro_nuevo();
    gotoxy(26,6);printf("Registrar articulo");
    archiarti2=fopen("archiarti2.dat","ab");
    if(archiarti2 == NULL) {
        gotoxy(15,10);printf("Error al abrir archivo de articulos");
        getch();
        return;
    }
    
    char otro;
    gotoxy(20,8);printf("Numero articulo[    ]");
    gotoxy(20,9);printf("Nombre articulo[                 ]");
    gotoxy(20,10);printf("Cantidad articulo[     ]");
    gotoxy(20,11);printf("Precio Articulo[      ]");
    
    do {
        gotoxy(36,8);scanf("%i",&misarti.numarti);fflush(stdin);
		gotoxy(37,9);gets(misarti.nomarti);
		convertir_mayusculas(misarti.nomarti);        
        gotoxy(39,10);scanf("%i",&misarti.cantarti);fflush(stdin);
        gotoxy(38,11);scanf("%f",&misarti.precioarti);fflush(stdin);
        fwrite(&misarti,sizeof(misarti),1,archiarti2);
        gotoxy(15,13);printf("Deseas agregar otro(s/n)[ ]");fflush(stdin);
        gotoxy(40,13);scanf("%c",&otro);
        
        gotoxy(36,8);printf("    ");
        gotoxy(37,9);printf("                 ");
        gotoxy(39,10);printf("     ");
        gotoxy(38,11);printf("      ");
        gotoxy(15,13);printf("                                    ");
    } while(otro=='s' || otro=='S');
    fclose(archiarti2);
}

void imprimir() {
    clrscr();
    textcolor(13); // Magenta claro
    totalarti = 0;
    archiarti2=fopen("archiarti2.dat","r");
    if(archiarti2 == NULL) {
        gotoxy(15,10);printf("No hay articulos registrados o error al abrir archivo");
        getch();
        return;
    }
    
    cuadro_nuevo();
    gotoxy(30,6);printf("Listado de Articulos");
    gotoxy(7,8);printf("Numero    Nombre          Cantidad  Precio    Total ");
    int ren=9;
    
    while(!feof(archiarti2)) {
        if(fread(&misarti,sizeof(misarti),1,archiarti2)) {
            gotoxy(7,ren);printf("%4i",misarti.numarti);
            gotoxy(17,ren);printf("%-15s",misarti.nomarti);
            gotoxy(34,ren);printf("%4i",misarti.cantarti);
            gotoxy(42,ren);printf("%8.2f",misarti.precioarti);
            gotoxy(52,ren);printf("%8.2f",misarti.cantarti*misarti.precioarti);
            ren++;
            totalarti+=(misarti.cantarti*misarti.precioarti);
        }
    }
    gotoxy(39,ren+1);printf("Total inventario $%8.2f",totalarti);
    getch();
    fclose(archiarti2);
}

void buscar() {
    clrscr();
    textcolor(12); // Rojo claro
    int numerobus;
    cuadro_nuevo();
    gotoxy(25,6);printf("Buscar Articulo");
    gotoxy(20,8);printf("Numero del articulo a buscar[    ]");
    gotoxy(49,8);scanf("%i",&numerobus);
    
    if(buscaarti(numerobus)) {
        gotoxy(20,10);printf("Articulo encontrado:");
        gotoxy(20,11);printf("Numero: %i", misarti.numarti);
        gotoxy(20,12);printf("Nombre: %s", misarti.nomarti);
        gotoxy(20,13);printf("Cantidad: %i", misarti.cantarti);
        gotoxy(20,14);printf("Precio: %.2f", misarti.precioarti);
        gotoxy(20,15);printf("Total: %.2f", misarti.cantarti * misarti.precioarti);
    } else {
        gotoxy(20,10);printf("Articulo no encontrado");
    }
    getch();
}

void ventas() {
    archiventas = fopen("ventas.dat","ab");
    if(archiventas == NULL) {
        gotoxy(15,10);printf("Error al abrir archivo de ventas");
        getch();
        return;
    }
    
    clrscr();
    textcolor(9); // Azul claro
    char otro, fechaactual[11];
    gotoxy(25,12);printf("Dame la fecha actual[          ]");fflush(stdin);
    gotoxy(46,12);gets(fechaactual);
    clrscr();
    cuadro_nuevo();
    gotoxy(20,6);printf("Fecha:%s",fechaactual);
    gotoxy(25,5);printf("Registro de ventas");
    gotoxy(20,8);printf("Numero Venta[    ]");
    gotoxy(20,9);printf("Numero Articulo[    ]");
    gotoxy(20,10);printf("Cantidad de Venta[        ]");
    
    do {
        gotoxy(33,8);scanf("%i",&misventas.numventa);fflush(stdin);
        do {
            gotoxy(36,9);printf("    ");
            gotoxy(36,9);scanf("%i",&misventas.numarti);fflush(stdin);
            if(!buscaarti(misventas.numarti)) {
                gotoxy(20,16);printf("Articulo no existe, intenta de nuevo");
            } else {
                gotoxy(20,16);printf("                                      ");
            }
        } while(!buscaarti(misventas.numarti));
        
        gotoxy(25,12);printf("Existencia Actual:%i",inventario);
        
        if(inventario <= 0) {
            gotoxy(20,14);printf("Este articulo no tiene existencias disponibles");
            getch();
            continue;
        }
        
        do {
            gotoxy(38,10);printf("        ");
            gotoxy(38,10);scanf("%i",&misventas.canventa);
            if(misventas.canventa > inventario) {
                gotoxy(20,14);printf("No hay suficiente inventario (Max: %i)", inventario);
            } else {
                gotoxy(20,14);printf("                                            ");
            }
        } while(misventas.canventa > inventario || misventas.canventa <= 0);
        
        strcpy(misventas.fecha,fechaactual);
        fwrite(&misventas,sizeof(misventas),1,archiventas);
        cantidad=misventas.canventa;
        actualiza(misventas.numarti);
        gotoxy(20,15);printf("Otra venta?(s/n)[ ]");fflush(stdin);
        gotoxy(37,15);scanf("%c",&otro);
        
        gotoxy(33,8);printf("    ");
        gotoxy(36,9);printf("    ");
        gotoxy(25,12);printf("                           ");
        gotoxy(38,10);printf("        ");
        gotoxy(20,15);printf("                   ");
        gotoxy(20,16);printf("                                      ");
        gotoxy(20,14);printf("                                            ");
    
    } while(otro=='s' || otro=='S');
    fclose(archiventas);
}

void compras() {
    archicompras = fopen("compras.dat","ab");
    if(archicompras == NULL) {
        gotoxy(15,10);printf("Error al abrir archivo de compras");
        getch();
        return;
    }
    
    clrscr();
    textcolor(6); // Amarillo oscuro
    char otro, fechaactual[11];
    gotoxy(25,12);printf("Dame la fecha actual[          ]");fflush(stdin);
    gotoxy(46,12);gets(fechaactual);
    clrscr();
    cuadro_nuevo();
    gotoxy(20,6);printf("Fecha:%s",fechaactual);
    gotoxy(25,5);printf("Registro de compras");
    gotoxy(20,8);printf("Numero Compra[    ]");
    gotoxy(20,9);printf("Numero Articulo[    ]");
    gotoxy(20,10);printf("Precio Compra[     ]");
    gotoxy(20,11);printf("Cantidad de Compra[        ]");
    
    do {
        gotoxy(34,8);scanf("%i",&miscompras.numcompra);fflush(stdin);
        do {
            gotoxy(36,9);printf("    ");
            gotoxy(36,9);scanf("%i",&miscompras.numarti);fflush(stdin);
            if(!buscaarti(miscompras.numarti)) {
                gotoxy(20,15);printf("Articulo no existe, intenta de nuevo");
            } else {
                gotoxy(20,15);printf("                                      ");
            }
        } while(!buscaarti(miscompras.numarti));
        
        gotoxy(35,10);scanf("%f",&miscompras.preciocompra);fflush(stdin);
        
        do {
            gotoxy(39,11);printf("        ");
            gotoxy(39,11);scanf("%i",&miscompras.cancompra);
            if(miscompras.cancompra <= 0) {
                gotoxy(20,16);printf("La cantidad debe ser mayor a 0");
            } else {
                gotoxy(20,16);printf("                              ");
            }
        } while(miscompras.cancompra <= 0);
        
        strcpy(miscompras.fecha,fechaactual);
        fwrite(&miscompras,sizeof(miscompras),1,archicompras);
        actualizacompra(miscompras.numarti, miscompras.cancompra);
        gotoxy(20,13);printf("Otra compra?(s/n)[ ]");fflush(stdin);
        gotoxy(38,13);scanf("%c",&otro);
        
        gotoxy(34,8);printf("    ");
        gotoxy(36,9);printf("    ");
        gotoxy(35,10);printf("      ");
        gotoxy(39,11);printf("        ");
        gotoxy(20,13);printf("                     ");
        gotoxy(20,15);printf("                                      ");
        gotoxy(20,16);printf("                              ");
    
    } while(otro=='s' || otro=='S');
    fclose(archicompras);
}

void imprimirventas() {
    clrscr();
    textcolor(5); // Magenta
    archiventas = fopen("ventas.dat","r");
    if(archiventas == NULL) {
        gotoxy(15,10);printf("No hay ventas registradas o error al abrir archivo");
        getch();
        return;
    }
    
    cuadro_nuevo();
    gotoxy(32,6);printf("Listado de Ventas");
    gotoxy(7,8);printf("NumVenta NumArt Nombre     Cant  Precio   Total    Fecha");
    int ren=9;
    totalarti = 0;
    
    while(!feof(archiventas)) {
        if(fread(&misventas,sizeof(misventas),1,archiventas)) {
            gotoxy(7,ren);printf("%4i",misventas.numventa);
            gotoxy(16,ren);printf("%4i",misventas.numarti);
            buscaarti2(misventas.numarti);
            gotoxy(23,ren);printf("%-9s",nomarti);
            gotoxy(34,ren);printf("%4i",misventas.canventa);
            gotoxy(40,ren);printf("%7.2f",precioarti);
            gotoxy(49,ren);printf("%7.2f",misventas.canventa*precioarti);
            gotoxy(58,ren);printf("%-10s",misventas.fecha);
            totalarti+=misventas.canventa*precioarti;
            ren++;
        }
    }
    gotoxy(40,ren+1);printf("Total Ventas $%8.2f",totalarti);
    getch();
    fclose(archiventas);
}

void imprimircompras() {
    clrscr();
    textcolor(3); // Cyan
    archicompras = fopen("compras.dat","r");
    if(archicompras == NULL) {
        gotoxy(15,10);printf("No hay compras registradas o error al abrir archivo");
        getch();
        return;
    }
    
    cuadro_nuevo();
    gotoxy(32,6);printf("Listado de Compras");
    gotoxy(7,8);printf("NumComp NumArt Nombre     Cant  PrecComp  Total    Fecha");
    int ren=9;
    float totalcompras = 0;
    
    while(!feof(archicompras)) {
        if(fread(&miscompras,sizeof(miscompras),1,archicompras)) {
            gotoxy(7,ren);printf("%4i",miscompras.numcompra);
            gotoxy(15,ren);printf("%4i",miscompras.numarti);
            buscaarti2(miscompras.numarti);
            gotoxy(22,ren);printf("%-9s",nomarti);
            gotoxy(33,ren);printf("%4i",miscompras.cancompra);
            gotoxy(39,ren);printf("%8.2f",miscompras.preciocompra);
            gotoxy(49,ren);printf("%7.2f",miscompras.cancompra*miscompras.preciocompra);
            gotoxy(58,ren);printf("%-10s",miscompras.fecha);
            totalcompras+=miscompras.cancompra*miscompras.preciocompra;
            ren++;
        }
    }
    gotoxy(40,ren+1);printf("Total Compras $%8.2f",totalcompras);
    getch();
    fclose(archicompras);
}


void imprimirclientes() {
    clrscr();
    textcolor(4); // Rojo
    archiclientes=fopen("clientes.dat","r");
    if(archiclientes == NULL) {
        gotoxy(15,10);printf("No hay clientes registrados o error al abrir archivo");
        getch();
        return;
    }
    
    cuadro_nuevo();
    gotoxy(32,6);printf("Listado de Clientes");
    gotoxy(7,8);printf("Numero  Nombre          Telefono     Direccion");
    int ren=9;
    
    while(!feof(archiclientes)) {
        if(fread(&misclientes,sizeof(misclientes),1,archiclientes)) {
            gotoxy(7,ren);printf("%4i",misclientes.numcliente);
            gotoxy(15,ren);printf("%-15s",misclientes.nomcliente);
            gotoxy(31,ren);printf("%-12s",misclientes.telefono);
            gotoxy(45,ren);printf("%-30s",misclientes.direccion);
            ren++;
        }
    }
    getch();
    fclose(archiclientes);
}

int buscaarti(int numero) {
    archiarti2=fopen("archiarti2.dat","rb");
    if(archiarti2 == NULL) return 0;
    
    int indice=0;
    encontrado=0;
    
    while(!feof(archiarti2)) {
        fseek(archiarti2,indice*sizeof(misarti),SEEK_SET);
        if (fread(&misarti,sizeof(misarti),1,archiarti2)) {
            if(misarti.numarti==numero) {
                strcpy(nomarti,misarti.nomarti);
                precioarti=misarti.precioarti;
                inventario=misarti.cantarti;
                encontrado=1;
                break;
            }
        }
        indice++;
    }
    fclose(archiarti2);
    return encontrado;
}

int buscaarti2(int numero) {
    archiarti2=fopen("archiarti2.dat","r");
    if(archiarti2 == NULL) {
        strcpy(nomarti,"N/A");
        precioarti = 0;
        return 0;
    }
    
    int indice=0, encontrado_local = 0;
    
    while(!feof(archiarti2)) {
        fseek(archiarti2,indice*sizeof(misarti),SEEK_SET);
        if(fread(&misarti,sizeof(misarti),1,archiarti2)) {
            if(misarti.numarti==numero) {
                strcpy(nomarti,misarti.nomarti);
                precioarti=misarti.precioarti;
                encontrado_local = 1;
                break;
            }
        }
        indice++;
    }
    
    if(!encontrado_local) {
        strcpy(nomarti,"N/A");
        precioarti = 0;
    }
    
    fclose(archiarti2);
    return encontrado_local;
}

int actualiza(int numero) {
    archiarti2 = fopen("archiarti2.dat","rb+");
    if(archiarti2 == NULL) return 0;
    
    int indice=0, actualizado = 0;
    
    while(!feof(archiarti2)) {
        fseek(archiarti2,indice*sizeof(misarti),SEEK_SET);
        if (fread(&misarti,sizeof(misarti),1,archiarti2)) {
            if(misarti.numarti==numero) {
                misarti.cantarti -= cantidad;
                fseek(archiarti2,indice*sizeof(misarti),SEEK_SET);
                fwrite(&misarti,sizeof(misarti),1,archiarti2);
                actualizado = 1;
                break;
            }
        }
        indice++;
    }
    fclose(archiarti2);
    return actualizado;
}

int actualizacompra(int numero, int cantidad) {
    archiarti2 = fopen("archiarti2.dat","rb+");
    if(archiarti2 == NULL) return 0;
    
    int indice=0, actualizado = 0;
    
    while(!feof(archiarti2)) {
        fseek(archiarti2,indice*sizeof(misarti),SEEK_SET);
        if (fread(&misarti,sizeof(misarti),1,archiarti2)) {
            if(misarti.numarti==numero) {
                misarti.cantarti += cantidad;
                fseek(archiarti2,indice*sizeof(misarti),SEEK_SET);
                fwrite(&misarti,sizeof(misarti),1,archiarti2);
                actualizado = 1;
                break;
            }
        }
        indice++;
    }
    fclose(archiarti2);
    return actualizado;
}

void clientes() {
    clrscr();
    textcolor(15); // Blanco
    cuadro_nuevo();
    gotoxy(26,6);printf("Registrar cliente");
    archiclientes=fopen("clientes.dat","ab");
    if(archiclientes == NULL) {
        gotoxy(15,10);printf("Error al abrir archivo de clientes");
        getch();
        return;
    }
    
    char otro;
    gotoxy(20,8);printf("Numero cliente[    ]");
    gotoxy(20,9);printf("Nombre cliente[                 ]");
    gotoxy(20,10);printf("Telefono[              ]");
    gotoxy(20,11);printf("Direccion[                           ]");
    
    do {
        gotoxy(35,8);scanf("%i",&misclientes.numcliente);fflush(stdin);
		gotoxy(36,9);gets(misclientes.nomcliente);
		convertir_mayusculas(misclientes.nomcliente);;
        gotoxy(30,10);gets(misclientes.telefono);
        gotoxy(31,11);gets(misclientes.direccion);
        convertir_mayusculas(misclientes.direccion);
        fwrite(&misclientes,sizeof(misclientes),1,archiclientes);
        gotoxy(15,13);printf("Deseas agregar otro(s/n)[ ]");fflush(stdin);
        gotoxy(40,13);scanf("%c",&otro);
        
        gotoxy(35,8);printf("    ");
        gotoxy(36,9);printf("                 ");
        gotoxy(30,10);printf("              ");
        gotoxy(31,11);printf("                           ");
        gotoxy(15,13);printf("                                    ");
    } while(otro=='s' || otro=='S');
    fclose(archiclientes);
}

void convertir_mayusculas(char *cadena) {
    int i;
    for (i = 0; i < strlen(cadena); i++) {
        cadena[i] = toupper(cadena[i]);
    }
}
