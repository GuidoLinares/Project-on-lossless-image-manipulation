#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

typedef struct
{
    unsigned char pixel[3];
    unsigned int profundidad;  // esta estructura admite formatos de distinta profundidad de color,
                                //a priori utilizaremos s�lo 24 bits.
}t_pixel;

typedef struct
{
    unsigned int tamarchivo;
    unsigned int tamencabezado;    // el tama�o del encabezado no siempre coincide con el comienzo de la imagen
    unsigned int comienzoimagen;   // por eso dejo espacio para ambas cosas
    unsigned int ancho;
    unsigned int alto;
    unsigned short profundidad;
}t_metadata;
#endif // estructuras_h_included
