//
// Created by Diego on 11/05/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "Agenda.h"

void listaPersonas(contacto *agenda, int *max) {
    printf("Agenda:\n");
    for (int i = 0; i < max[0]; ++i) {
        printf("%d; %s; %s; %s; %d; %d\n", i + 1, agenda[i].nombre, agenda[i].apellidos, agenda[i].telefono,
               agenda[i].edad, agenda[i].tipoContacto);
    }
}

int nuevaPersona(contacto *agenda, int *cont, int *max) {

    if (max[0] == 5) {
        max[0]++;
        agenda = realloc(agenda, max[0] * sizeof(contacto));
    }   //  Si el espacio de almacenamiento está completo le reasigno una línea más de tipo 'contacto'

    printf("Ecribe los datos del nuevo contacto:\n"
           " Nombre: ");
    scanf("%s", &agenda[*cont].nombre);

    fflush(stdin);  // Este comando limpia el buffer y nos permite asignar los valores por teclados con menos errores
    printf("Apellidos: ");
    scanf("%[^\n]", &agenda[*cont].apellidos);  //  "%[^\n]" le indica al 'scanf()' que guarde todos los datos que vayan entrando hasta el siguiente salto de línea
    fflush(stdin);

    printf("Telefono: ");
    scanf("%s", &agenda[*cont].telefono);

    printf("Edad: ");
    scanf("%d", &agenda[*cont].edad);

    printf("Tipo de contacto (FAVORITO, CONOCIDO, TRABAJO): ");
    scanf("%d", &agenda[*cont].tipoContacto);
    fflush(stdin);

    return max[0];
}

int borrarPersona(contacto *agenda, int *cont, int *max) {
    int id = -1, seguro = -1;

    //  MOSTRAR AGENDA ACTUAL:
    listaPersonas(agenda, max);

    // Pide el id que se quiere eliminar de la agenda:
    printf("\nIndica el ID del usuario que deseas borrar:\t");
    scanf("%d", &id);

    // Verifica si el número es válido y si existe la persona:
    if (id < 1 || id > max[0]) {
        printf("El numero de persona es invalido.\n");
    }

    // Pide la confirmación de operación al usuario:
    printf("Usted desea borrar:\t %d;%s;%s;%s;%d;%d\n", id, agenda[id - 1].nombre, agenda[id - 1].apellidos, agenda[id - 1].telefono, agenda[id - 1].edad, agenda[id - 1].tipoContacto);
    printf("¿Quiere confirmar la eliminacion del contacto?\n"
           "\t0 - SI\n"
           "\t1 - NO\n");
    scanf("%i", &seguro);

    if (seguro == 0) {
        for (int i = id-1 ; i < max[0]; ++i) {
            agenda[i] = agenda[i+1];
        }   //  Copia el valor de la siguiente fila en la que se quiere eliminar
        printf("Persona borrada.\n");
        max[0]--;   //  Resta una unidad al tamaño de la agenda
        while (sizeof(agenda) != 1) {
            realloc(agenda, max[0]*sizeof (contacto));
            break;
         }  //  Este código es un seguro para que la agenda no se quede con contactos negativos
    } else printf("Operacion cancelada.\n");

    return max[0];
}

int guardarAgenda(int *max, contacto *agenda) {
    char nombreAgenda;

    //  Pedimos el nombre del fichero al que queremos acceder:
    printf("Escribe el nombre de la agenda ('agenda.txt'): ");
    scanf("%s", &nombreAgenda);

    //  Abrimos el fichero:
    FILE *fichero = fopen(&nombreAgenda, "w");
    if (fichero == NULL) {
        perror("Error de apertura\n");
        return -1;
    }

    //  Realizamos la operación de escritura en el fichero:
    for (int i = 0; i < max[0]; ++i) {
        fprintf(fichero, "%d; %s; %s; %s; %d; %d\n", i + 1, agenda[i].nombre, agenda[i].apellidos, agenda[i].telefono,
                agenda[i].edad, agenda[i].tipoContacto);
    }

    printf("Fichero grabado correctamente\n");

    //  Cerramos el fichero:
    if (fclose(fichero) != 0) {
        perror("Error en clausura\n");
        return -1;
    }
    return 0;
}

int leerAgenda() {
    int linea[MAX_LINEA];
    char nombre;

    //  Pedimos el nombre del fichero al que queremos acceder:
    printf("Escribe el nombre de la agenda ('agenda.txt'): ");
    scanf("%s", &nombre);

    //  Abrimos el fichero:
    FILE *fichero = fopen(&nombre, "r");
    if (fichero == NULL) {
        printf("Error de apertura\n");
        return -1;
    }

    printf("Fichero abierto OK");

    //  Realizamos la operación de lectura y escritura por pantalla:
    printf("\nContenido:\n-------\n");
    while (!feof(fichero)) {
        fgets(linea, sizeof(linea-1), fichero);
        printf("%s", linea);
    }

    printf("-------\n");

    //  Cerramos el fichero:
    if (fclose(fichero) != 0) {
    perror("Error en clausura de fichero\n");
    return -1;
    }
}
