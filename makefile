# author: Bonino, Francisco Ignacio.
# version: 1.2.1
# since: 2021-08-31

# Flags a utilizar.
CC = gcc
CFLAGS = -Wall -Werror -pedantic
SLIBF = ar rcs
DLIBF = -fPIC

all: lab3 # En caso de ejecutar 'make' sin argumento, se aplica el target indicado.

# Directorios donde se guardarán los archivos.
build_folders:
	mkdir -p ./obj ./slib ./dlib ./bin

# Librería estática propia: file_utilities.
libfile_utilities.a: file_utilities.o
	$(SLIBF) slib/libfile_utilities.a

file_utilities.o: src/include/file_utilities.c src/include/file_utilities.h
	$(CC) $(CFLAGS) -c src/include/file_utilities.c -o obj/file_utilities.o

# Librería estática propia: labs_utilities.
liblabs_utilities.a: file_utilities.o lab2_utilities.o lab3_utilities.o cjson.o cjson_x.o
	$(SLIBF) slib/liblabs_utilities.a obj/file_utilities.o obj/lab2_utilities.o obj/lab3_utilities.o obj/cjson.o obj/cjson_x.o

lab2_utilities.o: src/include/lab2_utilities.c src/include/lab2_utilities.h
	$(CC) $(CFLAGS) -c src/include/lab2_utilities.c -o obj/lab2_utilities.o

lab3_utilities.o: src/include/lab3_utilities.c src/include/lab3_utilities.h
	$(CC) $(CFLAGS) -c src/include/lab3_utilities.c -o obj/lab3_utilities.o

cjson_x.o: src/include/cjson_x.c src/include/cjson_x.h
	$(CC) $(CFLAGS) -c src/include/cjson_x.c -o obj/cjson_x.o

# Librería estática: cJSON.
libcjson.a: cjson.o
	$(SLIBF) slib/libcjson.a

cjson.o: src/include/cJSON.c src/include/cJSON.h
	$(CC) $(CFLAGS) -c src/include/cJSON.c -o obj/cjson.o

# Librería dinámica propia: fsys_utilities.
libfsys_utilities.so: fsys_utilities.o file_utilities.o cjson.o
	$(CC) -shared -o dlib/libfsys_utilities.so obj/fsys_utilities.o obj/file_utilities.o obj/cjson.o

fsys_utilities.o: src/include/fsys_utilities.c src/include/fsys_utilities.h
	$(CC) $(CFLAGS) $(DLIBF) -c src/include/fsys_utilities.c -o obj/fsys_utilities.o

# Ejecutable final.
lab3.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o obj/lab3.o

lab3: build_folders lab3.o libfile_utilities.a liblabs_utilities.a libcjson.a libfsys_utilities.so
	$(CC) $(CFLAGS) -o bin/lab3 obj/lab3.o slib/libfile_utilities.a slib/libcjson.a slib/liblabs_utilities.a dlib/libfsys_utilities.so -ldl

clean:
	rm -r ./bin
	rm -r ./obj
	rm -r ./slib
	rm -r ./dlib