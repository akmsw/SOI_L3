/**
 * @file fsys_utilities.c
 * @author Bonino, Francisco Ignacio (franbonino82@gmail.com).
 * @brief Librería con funciones para manejo de filesystems.
 * @version 1.0
 * @since 2021-09-02
 */

#include "fsys_utilities.h"

/**
 * @brief Esta función muestra información relacionada a los
 *        filesystems soportados por el kernel del sistema.
 * 
 * @details Se muestra la cantidad de filesystems soportados
 *          por el kernel, y a continuación se proporciona un
 *          listado con los mismos.
 */
void kernel_fsys(void)
{
    FILE *file = NULL;

    if (!open_file_r(&file, "/proc/filesystems"))
        exit(-1);

    cJSON *fsys_cjson = cJSON_CreateObject();

    cJSON_AddNumberToObject(fsys_cjson, "supported_filesystems_amount", lines_amount("/proc/filesystems"));

    char line[STR_MAX_LEN];

    while (fgets(line, STR_MAX_LEN, file) != NULL)
    {
        char *aux = strtok(line, "\t");

        if (strstr(aux, "nodev"))
            cJSON_AddStringToObject(fsys_cjson, "supported_filesystem", strtok(NULL, "\n"));
        else
            cJSON_AddStringToObject(fsys_cjson, "supported_filesystem", strtok(aux, "\n"));
    }

    fprintf(stdout, "%s\n", cJSON_Print(fsys_cjson));
}