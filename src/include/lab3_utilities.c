/**
 * @file lab3_utilities.c
 * @author Bonino, Francisco Ignacio (franbonino82@gmail.com).
 * @brief Librería con funciones útiles particulares para el laboratorio #3.
 * @version 1.2
 * @since 2021-08-18
 */

#include "lab3_utilities.h"

/**
 * @brief Esta función imprime en terminal ayuda acerca de los argumentos
 *        aceptados para la ejecución del programa.
 */
void print_help(void)
{
    fprintf(stdout, "Valid arguments and their functionalities:\n\
                    \n-s......Runs the first excercise of the second lab.\
                    \n-a......Runs the second excercise of the second lab.\
                    \n-j......This argument must be prefixed with any of the above options.\
                    \n        It is used to run the required excercise and print its output\
                    \n        in cJSON format.\
                    \n-d......This argument loads dynamically a plugin library that shows\
                    \n        information about the filesystems supported by the kernel.\
                    \n        The information is already printed in cJSON format, so this\
                    \n        argument should not be suffixed with '-j' or 'j'.\
                    \n-h......Shows the help menu.\n");
}

/**
 * @brief Esta función ejecuta dinámicamente la
 *        función relacionada a los filesystems
 *        de la librería dinámica.
 * 
 * @details Con un handle abrimos la librería en
 *          modo RTLD_LAZY verificando que no haya
 *          errores en la apertura. Luego, creamos
 *          un puntero a la función especificada con
 *          dlsym y la ejecutamos siempre que la
 *          misma exista y se pueda abrir.
 */
void fsys_ex(void)
{
    void *handle = dlopen("./dlib/libfsys_utilities.so", RTLD_LAZY);

    if (!handle)
    {
        perror(dlerror());
        exit(-1);
    }

    void (*func)(void);

    *(void **)(&func) = dlsym(handle, "kernel_fsys");

    if (func == NULL)
    {
        fprintf(stderr, "ERROR [main.c]: Failure on DLL.");
        exit(-1);
    }

    func();

    dlclose(handle);
}

/**
 * @brief Esta función chequea si el argumento pasado al programa
 *        contiene el parámetro opcional recibido.
 * 
 * @param optarg Parámetros del argumento pasado al programa.
 * @param seek Parámetro a buscar.
 * 
 * @returns Si se encontró el argumento 'j'.
 */
bool arg_has_param(char *optarg, char seek)
{
    if (optarg != NULL)
    {
        if ((strlen(optarg) == 1) && (*optarg == seek))
            return true;
        else if (strchr(optarg, seek))
            return true;
        else
            return false;
    }

    return false;
}