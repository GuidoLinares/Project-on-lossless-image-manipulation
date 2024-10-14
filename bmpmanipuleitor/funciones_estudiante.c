/*
    Integrantes del grupo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido: Quiroga
    Nombre: Ferney Santiago
    DNI: 95933227
    Entrega:
    -----------------
    Apellido: Lanari
    Nombre: Lara
    DNI:
    Entrega:
    -----------------
    Apellido: Zapata
    Nombre: Santiago
    DNI: 44525943
    Entrega:
    -----------------
    Apellido: Gianotti
    Nombre: Tiago
    DNI: 44792090
    Entrega:
    -----------------

    Comentarios (opcionales) que deseen hacer al docente sobre el TP:

*/

#include "constantes.h"


int solucion(int argc, char* argv[])
{
/*
    Aquí deben hacer el código que solucione lo solicitado.
    Todas las funciones utilizadas deben estar declaradas en este archivo, y en su respectivo .h
*/
    t_metadata metadata;
    t_pixel* imagenOriginal = NULL;
    if (leerImagen("test_org.bmp",&metadata, &imagenOriginal) != TODO_OK) {
        return ERROR_ARCHIVO;
    }
    guardarArch("test_cpy.bmp",&metadata, imagenOriginal);


    t_metadata metadataRotada = metadata;
    t_pixel* imagenRotada = malloc(metadata.ancho * metadata.alto * sizeof(t_pixel));
    if(!imagenRotada) return MEMORIA_INSUFICIENTE;
    rotarImagen(imagenOriginal, &metadataRotada, imagenRotada);
    guardarArch("test_rot.bmp", &metadataRotada, imagenRotada);
    free(imagenRotada);

    t_pixel* imagenGris = malloc(metadata.ancho * metadata.alto * sizeof(t_pixel));
    if(!imagenGris) return MEMORIA_INSUFICIENTE;
    escalaGrises(imagenOriginal, &metadata, imagenGris);
    guardarArch("test_gris.bmp", &metadata, imagenGris);
    free(imagenGris);

    //FUNCION TONALIDAD AZUL
    t_pixel* imagenTonAzul = malloc (metadata.ancho * metadata.alto * sizeof(t_pixel));
    if (!imagenTonAzul)
        return MEMORIA_INSUFICIENTE;
    tonalidadAzul (imagenOriginal, &metadata,imagenTonAzul);
    guardarArch ("test_Azul.bmp",&metadata, imagenTonAzul);
    free(imagenTonAzul);

    //FUNCION TONALIDAD VERDE
    t_pixel* imagenTonVerde = malloc (metadata.ancho * metadata.alto * sizeof(t_pixel));
    if (!imagenTonVerde)
        return MEMORIA_INSUFICIENTE;
    tonalidadVerde (imagenOriginal, &metadata,imagenTonVerde);
    guardarArch ("test_Verde.bmp",&metadata, imagenTonVerde);
    free(imagenTonVerde);

    //FUNCION TONALIDAD ROJA
    t_pixel* imagenTonRoja = malloc (metadata.ancho * metadata.alto * sizeof(t_pixel));
    if (!imagenTonRoja)
        return MEMORIA_INSUFICIENTE;
    tonalidadRojo (imagenOriginal, &metadata,imagenTonRoja);
    guardarArch ("test_Rojo.bmp",&metadata, imagenTonRoja);
    free(imagenTonRoja);

    //FUNCION AUMENTAR CONTRASTE
    t_pixel* imagenMasContraste = malloc (metadata.ancho * metadata.alto * sizeof(t_pixel));
    if (!imagenMasContraste)
        return MEMORIA_INSUFICIENTE;
    aumentarContraste (imagenOriginal, &metadata,imagenMasContraste);
    guardarArch ("masContraste.bmp",&metadata, imagenMasContraste);
    free(imagenMasContraste);

    //FUNCION DISMINUIR CONTRASTE
     t_pixel* imagenMenosContraste = malloc (metadata.ancho * metadata.alto * sizeof(t_pixel));
    if (!imagenMasContraste)
        return MEMORIA_INSUFICIENTE;
    disminuirContraste (imagenOriginal, &metadata,imagenMenosContraste);
    guardarArch ("menosContraste.bmp",&metadata, imagenMenosContraste);
    free(imagenMenosContraste);

    //FUNCION MONOCROMO
    t_pixel* imagenMonocromo = malloc (metadata.ancho * metadata.alto * sizeof(t_pixel));
    t_metadata monocromo = metadata;
    int *imagen8Bits = malloc (metadata.ancho * metadata.alto * sizeof(int));
    if (!imagenMonocromo)
        return MEMORIA_INSUFICIENTE;
    imagenMonocromatica (imagenOriginal, &monocromo,imagenMonocromo);
    for (int i = 0; i < metadata.ancho * metadata.alto; i++) {
        imagen8Bits[i] = imagenMonocromo[i].pixel[0];
    }
    guardarArch ("imagenMonocromo.bmp",&monocromo, imagenMonocromo);
    free(imagenMonocromo);

    //FUNCION NEGATIVO
    t_pixel* imagenNegativa = malloc (metadata.ancho * metadata.alto * sizeof(t_pixel));
    if (!imagenNegativa)
        return MEMORIA_INSUFICIENTE;
    imagenNeg (imagenOriginal, &metadata,imagenNegativa);
    guardarArch ("imagenNegativa.bmp",&metadata, imagenNegativa);
    free(imagenNegativa);

    //FUNCION ACHICAR IMAGEN
    t_metadata newTam = metadata;
    newTam.alto = metadata.alto/2;
    newTam.ancho = metadata.ancho/2;
    t_pixel* imagenAchicada = malloc (newTam.alto * newTam.ancho * sizeof (t_pixel));

    t_pixel* pixAchicado = malloc (newTam.alto * newTam.ancho * sizeof (t_pixel));
    if (!imagenAchicada)
        return MEMORIA_INSUFICIENTE;
    achicarImagen (imagenOriginal, &newTam, imagenAchicada, pixAchicado);
    guardarArch ("imagenAchicada.bmp", &newTam, imagenAchicada);
    free(imagenAchicada);
    return TODO_OK;

    //FUNCION RECORTAR IMAGEN

    t_metadata newTamData = metadata;
    newTamData.alto = metadata.alto/2;
    newTamData.ancho = metadata.ancho/2;
    t_pixel* imagenRecortada = malloc (newTamData.alto * newTamData.ancho * sizeof (t_pixel));
    if (!imagenRecortada)
        return MEMORIA_INSUFICIENTE;
    recortarImagen (imagenOriginal, &metadata, &newTamData, imagenRecortada);
    guardarArch ("imagenRecortada.bmp", &newTamData, imagenRecortada);
    free(imagenRecortada);
    return TODO_OK;

    free(imagenOriginal);
}


int leerImagen(char* nombre_archivo,t_metadata* metadata, t_pixel** imagenOriginal)
{
    char header[54]; // Tamaño del encabezado de un archivo BMP
    FILE *file;
    file = fopen(nombre_archivo, "rb");
    if (file == NULL)
    {
        printf("Error al abrir la imagen original.\n");
        return ARCHIVO_NO_ENCONTRADO;
    }
    fread(header, 1, 54, file); // Leer los primeros 54 bytes del archivo
        if(header[0] == 'B' && header[1] == 'M'){
            metadata->tamarchivo = *(unsigned int*)&header[2];
            metadata->comienzoimagen = *(unsigned int*)&header[10];
            metadata->tamencabezado = *(unsigned int*)&header[14];
            metadata->ancho = *(unsigned int*)&header[18];
            metadata->alto = *(unsigned int*)&header[22];
            metadata->profundidad = *(unsigned short*)&header[28];

        }else{
            puts("El archivo no es un BMP.");
            return ERROR_ARCHIVO;
        }
    //
    // if (fgetc(file) == 'B' && fgetc(file) == 'M'{
    //     fseek(file, 8, SEEK_CUR);
    //     fread(&metadata->comienzoimagen, 4, 1, file); //comienzo de la imagen
    //     fread(&metadata->tamencabezado, 4, 1, file); //tamaño del encabezado
    //     fread(&metadata->ancho, 4, 1, file);
    //     printf("Ancho: %d\n", metadata->ancho);
    //     fread(&metadata->alto, 4, 1, file);
    //     printf("Alto: %d\n", metadata->alto);
    //     fseek(file, 2, SEEK_CUR);
    //     fread(&metadata->profundidad, 2, 1, file);
    //     printf("Profundidad: %d\n", metadata->profundidad);

    // }else{
    //     printf("El archivo no es un BMP.\n");
    //     return ERROR_ARCHIVO;
    // }


    fseek(file, metadata->comienzoimagen, SEEK_SET); // Mover al comienzo de los datos de la imagen
    *imagenOriginal = malloc(metadata->ancho * metadata->alto * sizeof(t_pixel));
    if (!*imagenOriginal) {
        return MEMORIA_INSUFICIENTE;
    }
    for (int i = 0; i < metadata->ancho * metadata->alto; i++) {
        fread(&(*imagenOriginal)[i].pixel, 3, 1, file);
        (*imagenOriginal)[i].profundidad = metadata->profundidad;
    }
    fclose(file);
    return TODO_OK;
}

void rotarImagen(t_pixel* imagenOriginal, t_metadata* metadata, t_pixel* imagenRotada){
    //Rotamos la imagen
    for (int i = 0; i < metadata->alto; i++) {
        for (int j = 0; j < metadata->ancho; j++) {
            imagenRotada[j * metadata->alto + i] = imagenOriginal[(metadata->alto - i - 1) * metadata->ancho + j];
        }
    }
    int temp = metadata->ancho;
    metadata->ancho = metadata->alto;
    metadata->alto = temp;
}

int guardarArch(char* nombreArch,t_metadata* metadata, t_pixel *imagenOriginal){
    char ruta[256];
    snprintf(ruta, sizeof(ruta), "tests/%s", nombreArch);
    FILE* fp = fopen(ruta, "wb"); //abro el archivo en modo escritura binaria
    int error = 0;
    if (!fp){
        printf("Error al abrir el archivo test_cpy.\n");
        return 2;
    }
    if (!error && fwrite("BM", 2, 1, fp) != 1) error = 1;
    unsigned int tam = BMP_HEADER_SIZE + metadata->ancho * metadata->alto * 3;
    if (!error && fwrite(&tam, sizeof(tam), 1, fp) != 1) error = 1;
    int cero = 0;
    if (!error && fwrite(&cero, sizeof(cero), 1, fp) != 1) error = 1;
    if (!error && fwrite(&metadata->comienzoimagen, sizeof(metadata->comienzoimagen), 1, fp) != 1) error = 1;
    if (!error && fwrite(&metadata->tamencabezado, sizeof(metadata->tamencabezado), 1, fp) != 1) error = 1;
    if (!error && fwrite(&metadata->ancho, sizeof(metadata->ancho), 1, fp) != 1) error = 1;
    if (!error && fwrite(&metadata->alto, sizeof(metadata->alto), 1, fp) != 1) error = 1;
    unsigned short planos = 1;
    if (!error && fwrite(&planos, sizeof(planos), 1, fp) != 1) error = 1;
    if (!error && fwrite(&metadata->profundidad, sizeof(metadata->profundidad), 1, fp) != 1) error = 1;
    if (!error && fwrite(&cero, sizeof(cero), 1, fp) != 1) error = 1;
    int tamImagen = metadata->ancho * metadata->alto * 3;
    if (!error && fwrite(&tamImagen, sizeof(tamImagen), 1, fp) != 1) error = 1;

    if (!error) {
        fseek(fp, metadata->comienzoimagen, SEEK_SET);
        for (int i = 0; i < metadata->ancho * metadata->alto; i++) {
            if (fwrite(&imagenOriginal[i].pixel, 3, 1, fp) != 1) {
                error = 1;
                return ERROR_ARCHIVO;
            }
        }
    }

    fclose(fp);

    if (error) {
        printf("Error al escribir el archivo.\n");
        return 3;
    }

    return TODO_OK;
}

int escalaGrises(t_pixel *imagenOriginal, t_metadata* metadata, t_pixel* imagenGris){
    for (int i=0; i<metadata->alto*metadata->ancho; i++)
    {
        unsigned char promedio = (imagenOriginal[i].pixel[0] + imagenOriginal[i].pixel[1] + imagenOriginal[i].pixel[2]) / 3;
        imagenGris[i].pixel[0] = promedio;
        imagenGris[i].pixel[1] = promedio;
        imagenGris[i].pixel[2] = promedio;
    }
    return TODO_OK;
}

int tonalidadAzul (t_pixel* imagenOriginal, t_metadata* metadata, t_pixel* imagenTonAzul)
{
    for(int i=0;i<metadata->alto * metadata->ancho; i++)
    {
            if(imagenOriginal[i].pixel[0] * 1.5f>= 255)
                 imagenTonAzul[i].pixel[0]= 255 ; //azul
            else
                imagenTonAzul[i].pixel[0] = imagenOriginal[i].pixel[0] * 1.5f;


            imagenTonAzul[i].pixel[1] = imagenOriginal[i].pixel[1];
            imagenTonAzul[i].pixel[2] = imagenOriginal[i].pixel[2];



    }
    return TODO_OK;

}
int tonalidadVerde (t_pixel* imagenOriginal, t_metadata* metadata, t_pixel* imagenTonVerde)
{
    for(int i=0;i<metadata->alto * metadata->ancho; i++)
    {
        if(imagenOriginal[i].pixel[1] * 1.5f>= 255)
                 imagenTonVerde[i].pixel[1]= 255 ; //verde
            else
                imagenTonVerde[i].pixel[1] = imagenOriginal[i].pixel[1] * 1.5f;


            imagenTonVerde[i].pixel[0] = imagenOriginal[i].pixel[0];
            imagenTonVerde[i].pixel[2] = imagenOriginal[i].pixel[2];
    }
    return TODO_OK;

}

int tonalidadRojo (t_pixel* imagenOriginal, t_metadata* metadata, t_pixel* imagenTonRoja)
{
     for(int i=0;i<metadata->alto * metadata->ancho; i++)
    {
        if(imagenOriginal[i].pixel[2] * 1.5f>= 255)
                 imagenTonRoja[i].pixel[2]= 255 ; //rojo
            else
                imagenTonRoja[i].pixel[2] = imagenOriginal[i].pixel[2] * 1.5f;


            imagenTonRoja[i].pixel[0] = imagenOriginal[i].pixel[0];
            imagenTonRoja[i].pixel[1] = imagenOriginal[i].pixel[1];
    }
    return TODO_OK;

}

int aumentarContraste (t_pixel* imagenOriginal, t_metadata* metadata, t_pixel*imagenMasContraste )
{
    for(int i=0;i<metadata->alto * metadata->ancho; i++)
    {
        float r = (imagenOriginal[i].pixel[2] - 128) * 1.25 + 128;
        float g = (imagenOriginal[i].pixel[1] - 128) * 1.25 + 128;
        float b = (imagenOriginal[i].pixel[0] - 128) * 1.25 + 128;

        imagenMasContraste[i].pixel[2] = (r > 255) ? 255 : (r < 0 ? 0 : (unsigned char)r);
        imagenMasContraste[i].pixel[1] = (g > 255) ? 255 : (g < 0 ? 0 : (unsigned char)g);
        imagenMasContraste[i].pixel[0] = (b > 255) ? 255 : (b < 0 ? 0 : (unsigned char)b);
    }
    return 0;
}

int disminuirContraste (t_pixel* imagenOriginal, t_metadata* metadata, t_pixel*imagenMenosContraste )
{
    for(int i=0;i<metadata->alto * metadata->ancho; i++)
    {
        float r = (imagenOriginal[i].pixel[2] - 128) * 0.75f + 128;
        float g = (imagenOriginal[i].pixel[1] - 128) * 0.75f + 128;
        float b = (imagenOriginal[i].pixel[0] - 128) * 0.75f + 128;

        imagenMenosContraste[i].pixel[2] = (r > 255) ? 255 : (r < 0 ? 0 : (unsigned char)r);
        imagenMenosContraste[i].pixel[1] = (g > 255) ? 255 : (g < 0 ? 0 : (unsigned char)g);
        imagenMenosContraste[i].pixel[0] = (b > 255) ? 255 : (b < 0 ? 0 : (unsigned char)b);
    }
    return 0;
}


int imagenMonocromatica (t_pixel* imagenOriginal, t_metadata* metadata, t_pixel* imagenMonocromo){
    for (int i = 0; i < metadata->ancho * metadata->alto; i++) {
        int promedio = (imagenOriginal[i].pixel[0] + imagenOriginal[i].pixel[1] + imagenOriginal[i].pixel[2]) / 3;
        if (promedio < 128) {
            imagenMonocromo[i].pixel[0] = 0;
            imagenMonocromo[i].pixel[1] = 0;
            imagenMonocromo[i].pixel[2] = 0;
        } else {
            imagenMonocromo[i].pixel[0] = 255;
            imagenMonocromo[i].pixel[1] = 255;
            imagenMonocromo[i].pixel[2] = 255;
        }
    }
    return TODO_OK;
}


int imagenNeg(t_pixel* imagenOriginal, t_metadata* metadata, t_pixel* imagenNegativa)
{
    for (int i = 0; i < metadata->ancho * metadata->alto; i++) {
        imagenNegativa[i].pixel[0] = 255 - imagenOriginal[i].pixel[0];
        imagenNegativa[i].pixel[1] = 255 - imagenOriginal[i].pixel[1];
        imagenNegativa[i].pixel[2] = 255 - imagenOriginal[i].pixel[2];
    }
    return TODO_OK;
}

int achicarImagen (t_pixel* imagenOriginal , t_metadata* newTam, t_pixel* imagenAchicada,t_pixel* pixAchicado)
{
    for (int y = 0; y < newTam->alto*2 - 2; y+=2) //Filas
    {
        for (int x = 0; x < newTam->ancho*2 - 2; x+=2) //Columnas
        {
            int anchoViejo = newTam->ancho*2;

            t_pixel promedio;
            for (int i = 0; i < 2; i++)
            {
                for(int j=0;j<2;j++)
                {
                    t_pixel p1 = imagenOriginal[(y + i) * anchoViejo + (x + j)];
                    t_pixel p2 = imagenOriginal[(y + i) * anchoViejo + (x + j + 1)];
                    t_pixel p3 = imagenOriginal[(y + i + 1) * anchoViejo + (x + j)];
                    t_pixel p4 = imagenOriginal[(y + i + 1) * anchoViejo + (x + j + 1)];
                    promedio.pixel[i] = (p1.pixel[i] + p2.pixel[i] + p3.pixel[i] + p4.pixel[i]) / 4;
                    //Poner el maximo si se paso de 255
                    if(promedio.pixel[i] > 255)
                        promedio.pixel[i] = 255;
                }

            }


            imagenAchicada[y/2 * newTam->ancho + x/2] = promedio;
        }
    }
    return TODO_OK;
}


int recortarImagen (t_pixel* imagenOriginal, t_metadata* metadata, t_metadata* newTam, t_pixel* imagenRecortada)
{
    for (int y = 0; y < newTam->alto; y++)
    {
        for (int x = 0; x < newTam->ancho; x++)
        {
            imagenRecortada[y * newTam->ancho + x] = imagenOriginal[y *  metadata->ancho + x ];
        }
    }
}
