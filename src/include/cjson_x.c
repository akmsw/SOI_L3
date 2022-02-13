/**
 * @file cjson_x.c
 * @author Bonino, Francisco Ignacio (franbonino82@gmail.com).
 * @brief Librería con funciones útiles para imprimir ejercicios
 *        particulares en formato cJSON.
 * @version 1.2
 * @since 2021-09-01
 */

#include "cjson_x.h"

/**
 * @brief Esta función almacena la información obtenida
 *        en el primer ejercicio del laboratorio #2 en
 *        formato cJSON y lo imprime en pantalla.
 */
void cjson_s(void)
{
    fprintf(stdout, ">   EJ. 1 - C-STRINGS [cJSON format]\n\n");

    cJSON *sys_info = cJSON_CreateObject();

    // Recopilación de datos de la memoria RAM.

    float total_ram = (float)get_value("MemTotal", "/proc/meminfo", ":") / 1000;
    float free_ram = (float)get_value("MemFree", "/proc/meminfo", ":") / 1000;
    float available_ram = (float)get_value("MemAvailable", "/proc/meminfo", ":") / 1000;
    float total_swap = (float)get_value("SwapTotal", "/proc/meminfo", ":") / 1000;
    float free_swap = (float)get_value("SwapFree", "/proc/meminfo", ":") / 1000;

    cJSON_AddItemToObject(sys_info, "total_ram", cJSON_CreateNumber(total_ram));
    cJSON_AddItemToObject(sys_info, "free_ram", cJSON_CreateNumber(free_ram));
    cJSON_AddItemToObject(sys_info, "available_ram", cJSON_CreateNumber(available_ram));
    cJSON_AddItemToObject(sys_info, "total_swap", cJSON_CreateNumber(total_swap));
    cJSON_AddItemToObject(sys_info, "free_swap", cJSON_CreateNumber(free_swap));

    // Recopilación de datos del CPU.

    FILE *cpufile = NULL;

    int threads = get_value("siblings", "/proc/cpuinfo", ":");
    int cores = get_value("cpu cores", "/proc/cpuinfo", ":");

    strtok(search_line(cpufile, "model name", "/proc/cpuinfo"), ":");

    cJSON_AddItemToObject(sys_info, "cpu_model", cJSON_CreateString(strtok(NULL, ":")));
    cJSON_AddItemToObject(sys_info, "cores", cJSON_CreateNumber(cores));
    cJSON_AddItemToObject(sys_info, "threads_per_core", cJSON_CreateNumber(threads / cores));

    fprintf(stdout, "%s\n", cJSON_Print(sys_info));
}

/**
 * @brief Esta función almacena la información obtenida
 *        en el segundo ejercicio del laboratorio #2 en
 *        formato cJSON y lo imprime en pantalla.
 * 
 * @param path Ruta del archivo cuyas palabras
 *             se almacenan en mayúscula.
 */
void cjson_a(char *path)
{
    fprintf(stdout, ">   EJ. 2 - ARRAYS [cJSON format]\n\n");

    cJSON *array_obj = cJSON_CreateObject();
    cJSON *array = cJSON_CreateArray();

    char **words_array = malloc(sizeof(char *));

    int words_n = save_uppercase(&words_array, path);

    for (int i = 0; i < words_n; i++)
        cJSON_AddItemToArray(array, cJSON_CreateString(words_array[i]));

    cJSON_AddStringToObject(array_obj, "file", path);
    cJSON_AddItemToObject(array_obj, "words", array);

    fprintf(stdout, "%s\n", cJSON_Print(array_obj));

    free(words_array);
}