# GNU toolchain & Linux software

Para comenzar, se debe clonar el repositorio. Una vez hecho, podemos compilar todo el proyecto aprovechando el archivo `makefile`, con el comando:

`make lab3`

Esto compilará todo con las flags indicadas en la consigna:

`gcc -Wall -Werror -pedantic`

Se organizó el proyeto en distintas carpetas para un mejor manejo de archivos. El código fuente en lenguaje C que resuelve los ejercicios se encuentra en la carpeta `src`. Los headers y cuerpos de las librerías utilizadas (estáticas, dinámicas, propias y externas) se encuentran en `src/include`.

Se crean carpetas adicionales para los archivos `.o`, `.so`, `.a`, y para el ejecutable.

Para correr el programa, debe ingresarse por consola:

`./bin/lab3`

junto a ciertos argumentos.  
A continuación se darán las pautas para ejecutar correctamente el programa.

### **El proyecto ha sido documentado en su totalidad explicando cómo y por qué cada función hace lo que hace.**

# Command line arguments
Esta primera actividad tiene como objetivo aprender sobre el manejo de argumentos en la función principal.

La lista de argumentos válidos y sus funcionalidades es la siguiente:

- `-s`: Ejecuta el ejercicio #1 del laboratorio #2.
- `-a`: Ejecuta el ejercicio #2 del laboratorio #2.
- `-j`: Este argumento debe ser prefijado con alguna de las opciones anteriores. Su función es la de mostrar la información requerida en formato cJSON mediante la librería [cJSON](https://github.com/DaveGamble/cJSON).
- `-d`: Este argumento puede ser prefijado con cualquiera de las primeras dos opciones. Su función es la de mostrar información acerca de los sistemas de archivos soportados por el kernel del sistema en formato cJSON haciendo uso de la librería nombrada anteriormente. Esto se realiza mediante una librería cargada dinámicamente (en tiempo de ejecución). Como esta opción tiene por defecto el formato cJSON, no debe tener como prefijo/sufjo la opción `-j`.
- `-h`: Despliega un menú de ayuda con los argumentos permitidos en caso de que el usuario desconozca esta información. No puede tener ningún otro argumento/parámetro como prefijo/sufijo.

Esto fue resuelto mediante la librería `getopt`, que ofrece funciones muy útiles para analizar los argumentos recibidos en la función principal de un programa.

Cabe resaltar que, dado que pueden concatenarse varios de los argumentos listados, se proporcionó la facilidad de que el usuario pueda pasarlos combinados del modo -[argumento][parámetros adicionales].

Un ejemplo de esto, es que el usuario puede ingresar por consola tanto `./bin/lab3 -a -j` como `./bin/lab3 -aj`.

Teniendo esto en cuenta, las combinaciones posibles de argumentos y parámetros a ingresar son:
```
-h
-a
-a -j
-a -d
-a -j -d
-aj -d
-ajd
-s
-s -j
-s -d
-s -j -d
-sj -d
-sjd
-d
```

Como fue especificado anteriormente, la opción `-d` tiene por defecto el formato cJSON; por lo que si el usuario ingresa el comando `-adj` tratando de "forzar" el formato cJSON a la opción `-d`, el programa salvará este conflicto aplicando el formato cJSON al output de la opción `-a`. Cualquier "conflicto" de este tipo con los demás argumentos se resolverá de la misma forma a menos que no se pueda y, en ese caso, se mostrará un error por pantalla especificando el problema.

Cualquier otro argumento ingresado de manera errónea (sin el '-' inicial), y cualquier argumento/parámetro no permitido por el programa será motivo para detener la ejecución del mismo mediante un mensaje de error que indique el problema y devuelva el código de terminación errónea del programa (-1).

## Condiciones

- Este programa sólo admite ejecutar un ejercicio a la vez. Esto quiere decir que **los argumentos `-a` y `-s` son excluyentes**. El usuario puede ingresar cualquier combinación entre, por ejemplo, `-a`, `-j` y `-d` pero a ello no puede agregarle `-s`.
- Para correr el programa se necesita al menos 1 (un) argumento y no más de 3 (tres) por la condición de exclusividad mencionada. Si el usuario corre el programa sin ningún argumento o más de 3 (tres), se mostrará un mensaje de error y el programa finalizará con el código de terminación errónea del programa (-1).

## Issues conocidos

- Si se ejecuta el programa desde una ruta que no sea el directorio donde se contiene el proyecto, habrán problemas con la carga de la librería dinámica.

# Respuestas

- **¿Cuáles son los tipos de file descriptors que podemos encontrar en /proc/[PID]/fd?**
    Los tipos de *file descriptors* que podemos encontrar en la carpeta `fd` en el directorio de `/proc/[PID]` de un cierto proceso son:
  - **BLK**: Block device.
  - **CHR**: Character device.
  - **DIR**: Directory.
  - **IFO**: FIFO / Pipe.
  - **LNK**: Symlink.
  - **REG**: Regular file.
  - **SOCK**: Socket.
  - **UNKNOWN**: Unknown.
- **Suponiendo que un usuario está ejecutando el proceso _pid 1212_, ¿es válida la ejecución del siguiente comando desde una terminal nueva?:**
`% echo “Hello, world.” >> /proc/1212/fd/1`
    - Sí. Lo que se consigue con esto es poner en el stdout del file descriptor del proceso *1212* el string "Hello, world.".
  
- **¿Qué diferencia hay entre _hard limits_ y _soft limits_?**
    - El *hard limit* es el valor máximo para el sobrepaso del *soft limit*. El *soft limit* es el valor máximo de recursos del sistema que se le proporciona a usuarios o grupos. La diferencia es que el *soft limit* puede sobrepasarse temporalmente sólo hasta alcanzar el valor máximo establecido por el *hard limit*. Cuando se llega a este punto, ya no se puede sobrepasar más.
