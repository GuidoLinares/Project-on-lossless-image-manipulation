#ifndef FUNCIONES_ESTUDIANTE_H_INCLUDED
#define FUNCIONES_ESTUDIANTE_H_INCLUDED


#include "constantes.h"

int solucion(int argc, char* argv[]);
int leerImagen(char* nombre_archivo, t_metadata* metadata, t_pixel **imagenOriginal);
void rotarImagen(t_pixel* imagenOriginal, t_metadata* metadata, t_pixel* imagenRotada);
int guardarArch(char* nombreArch,t_metadata* metadata, t_pixel *imagenOriginal);
int escalaGrises(t_pixel *imagenOriginal, t_metadata* metadata, t_pixel* imagenGris);
int tonalidadAzul (t_pixel *imagenOriginal, t_metadata* metadata, t_pixel* imagenTonAzul);
int tonalidadVerde (t_pixel *imagenOriginal, t_metadata* metadata, t_pixel* imagenTonVerde);
int tonalidadRojo (t_pixel *imagenOriginal, t_metadata* metadata, t_pixel* imagenTonRoja);
int aumentarContraste (t_pixel *imagenOriginal, t_metadata* metadata, t_pixel* imagenMasContraste);
int disminuirContraste (t_pixel *imagenOriginal, t_metadata* metadata, t_pixel* imagenMenosContraste);
int imagenMonocromatica (t_pixel *imagenOriginal, t_metadata* metadata, t_pixel* imagenMonocromo);
int imagenNeg (t_pixel *imagenOriginal, t_metadata* metadata, t_pixel* imagenNegativa);
int achicarImagen(t_pixel* imagenOriginal, t_metadata* newTam, t_pixel* imagenAchicada,t_pixel* pixAchicado);
int recortarImagen (t_pixel* imagenOriginal, t_metadata* metadata, t_metadata* newTam, t_pixel* imagenRecortada);
#endif // FUNCIONES_ESTUDIANTE_H_INCLUDED
