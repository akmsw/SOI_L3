/**
 * @file lab3_utilities.h
 * @author Bonino, Francisco Ignacio (franbonino82@gmail.com).
 * @brief Header de librería con funciones útiles particulares
 *        para el laboratorio #3.
 * @version 1.2
 * @since 2021-08-18
 */

#ifndef __LAB3_UTILITIES__
#define __LAB3_UTILITIES__

#include "file_utilities.h"
#include <dlfcn.h>

void print_help(void);
void fsys_ex(void);

bool arg_has_param(char *, char);

#endif