//
// Created by Diego on 11/05/2023.
//

#ifndef AGENDADEFINITIVA_AGENDA_H
#define AGENDADEFINITIVA_AGENDA_H

#define MAX 5   //  Espacio inicial de la agenda
#define MAX_CONTACTO 50   //    Espacio nombres
#define MAX_LINEA 200  //   Espacio línea de fichero

enum tipoCont {
    FAVORITO,
    CONOCIDO,
    TRABAJO
};  //  Creación de las opciones de tipo de contacto que hay en la agenda

typedef struct {
    char nombre[MAX_CONTACTO];
    char apellidos[MAX_CONTACTO];
    char telefono[MAX_CONTACTO];
    short int edad;
    enum tipoCont tipoContacto;
} contacto; //  Creación del nuevo tipo de datos 'contacto'

void listaPersonas(contacto *agenda, int *max);

int nuevaPersona(contacto *agenda, int *cont, int *max);

int borrarPersona(contacto *agenda, int *cont, int *max);

int guardarAgenda(int *max, contacto *agenda);

int leerAgenda();

#endif //AGENDADEFINITIVA_AGENDA_H
