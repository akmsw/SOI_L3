/**
 * @file file_utilities.c
 * @author Bonino, Francisco Ignacio (franbonino82@gmail.com).
 * @brief Librería con funciones útiles generales para archivos.
 * @version 1.1
 * @since 2021-08-18 
 */

#include "file_utilities.h"

/**
 * @brief Esta función se encarga de tomar el contenido del
 *        archivo requerido por parámetro y almacenarlo en un
 *        arreglo dinámicamente transformando cada palabra a
 *        mayúsculas.
 * 
 * @details Recorro el archivo línea por línea. De cada una,
 *          tomo las palabras de manera individual y las
 *          recorro letra por letra. Cada letra cuyo valor en
 *          ASCII esté entre los valores de las letras 'a' y
 *          'z', la convierto a mayúsculas. Este resultado lo
 *          agrego de manera dinámica al arreglo de palabras.
 *          Una vez finalizada la conversión y el almacenamiento,
 *          se cierra el archivo.
 * 
 * @param words_array Arreglo bidimensional de strings
 *                    a rellenar de manera dinámica.
 * @param path Ruta del archivo a imprimir en mayúsculas.
 * 
 * @returns La cantidad de palabras que contiene el archivo.
 */
int save_uppercase(char ***words_array, char *path)
{
    FILE *file = NULL; // Archivo a recorrer.

    if (!open_file_r(&file, path))
        exit(-1);

    int word_n = 0; // Cantidad de palabras obtenidas del archivo.

    char line[STR_MAX_LEN]; // Línea del archivo que está siendo leída.

    // Almaceno todas las palabras en mayúscula.
    while (fgets(line, STR_MAX_LEN, file) != NULL)
    {
        char *word = strtok(line, " "); // Palabra siendo analizada.

        do
        {
            if (word_n > 0)
            {
                // Variable temporal para salvar NULL en realloc.
                void *temp = realloc(*words_array, sizeof(char *) * (word_n + 1));

                if (temp == NULL)
                {
                    perror("\nERROR: FAILURE ON MEMORY REALLOCATION.");
                    exit(-1);
                }

                *words_array = temp; // Si todo salió bien, el arreglo habrá cambiado de tamaño.
            }

            for (int i = 0; i < strlen(word); i++)
                if (word[i] >= 'a' && word[i] <= 'z')
                    word[i] = toupper(word[i]);

            (*words_array)[word_n] = word;

            word_n++;
        } while ((word = strtok(NULL, " ")) != NULL);
    }

    // Cierro el archivo.
    fclose(file);

    return word_n;
}

/**
 * @brief Esta función se encarga de devolver el valor
 *        numérico de un campo en un archivo.
 *
 * @param search Nombre del campo a buscar.
 * @param where Ruta donde está el archivo que contiene ese dato.
 * @param delim Delimitador para strtok.
 *
 * @returns El valor del campo buscado.
 */
int get_value(char *search, char *where, char *delim)
{
    FILE *file = NULL;

    strtok(search_line(file, search, where), delim);

    return atoi(strtok(NULL, delim));
}

/**
 *  @brief  Esta función cuenta la cantidad de líneas de un archivo.
 * 
 *  @param directory Directorio del archivo a abrir.
 * 
 *  @returns La cantidad de líneas del archivo.
 */
int lines_amount(char *directory)
{
    FILE *file = fopen(directory, "r");

    char line[STR_MAX_LEN];

    int lines_n = 0;

    while (fgets(line, STR_MAX_LEN, file) != NULL)
        lines_n++;

    return lines_n;
}

/**
 * @brief Esta función retorna una línea específica de un archivo a leer.
 * 
 * @details Leemos el archivo línea por línea y, ante la primer coincidencia con
 *          el parámetro search, cerramos el archivo y retornamos la línea hallada.
 * 
 * @param file Archivo donde se buscará la información necesaria.
 * @param search Palabra o cadena que debe contener la línea a retornar.
 * @param where Directorio del archivo donde se buscará la información necesaria.
 * 
 * @returns La línea que contiene el parámetro de búsqueda.
 */
char *search_line(FILE *file, char *search, char *where)
{
    static char line[STR_MAX_LEN]; // La declaro estática para poder retornarla.

    if (!open_file_r(&file, where))
        exit(-1);

    while (fgets(line, STR_MAX_LEN, file) != NULL)
        if (strstr(line, search))
            break;

    fclose(file);

    return line;
}

/**
 * @brief Esta función se encarga de abrir el archivo que queremos
 *        en modo lectura.
 * 
 * @param file Archivo con el que se trabajará.
 * @param directory Directorio del archivo que queremos abrir.
 * 
 * @returns Si se pudo abrir exitosamente el archivo.
 */
bool open_file_r(FILE **file, char *directory)
{
    *file = fopen(directory, "r");

    // Si hubo un error al leer el archivo, mostramos un mensaje de error y salimos del programa.
    if (!*file)
    {
        char err_msg[STR_MAX_LEN];

        sprintf(err_msg, "\nERROR: CANNOT OPEN SYSTEM FILE: %s", directory);
        perror(err_msg);

        return false;
    }

    return true;
}