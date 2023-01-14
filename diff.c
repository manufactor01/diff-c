#define _GNU_SOURCE
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool comparar_lineas(char *linea1, char *linea2, ssize_t c1, ssize_t c2){
	strtok(linea1, "\n");
	strtok(linea2, "\n");
	if(c1 == -1 || c2 == -1 ) return false;
	return strcmp(linea1, linea2) == 0;
}

void mostrar_lineas(char *linea1, char *linea2, size_t c1, size_t c2, size_t i){
	fprintf(stdout, "Diferencia en linea %ld\n", i);
	if(c1 != -1) fprintf(stdout, "<%s\n", linea1);
	else
		fprintf(stdout, "%s","<\n");
	fprintf(stdout, "%s\n", "---");
	if(c2 != -1) fprintf(stdout, ">%s\n", linea2);
	else
		fprintf(stdout, "%s", ">\n");
}

int main(int argc, char const *argv[])
{
	if(argc != 3){
		fprintf(stderr, "%s\n", "Cantidad de parametros erronea");
		return 1;
	}
	FILE *archivo1 = fopen(argv[1], "rt"); 
	FILE *archivo2 = fopen(argv[2], "rt");

	if(!archivo1 || !archivo2){
		fprintf(stderr, "%s\n", "Error al abrir archivo");
		return 1;
	}

	char *linea1 = NULL, *linea2 = NULL;
	size_t capacidad1, capacidad2;
	ssize_t leidos1, leidos2;

	bool ok1 = true, ok2 = true, son_distintos = false;
	size_t i = 1;

	while((ok1 || ok2) && !son_distintos){
		ok1 = ((leidos1 = getline(&linea1, &capacidad1, archivo1)) != -1);
		ok2 = ((leidos2 = getline(&linea2, &capacidad2, archivo2)) != -1);

		son_distintos = !comparar_lineas(linea1, linea2, leidos1, leidos2);
		if(!son_distintos){
			i++;
		}else{
			mostrar_lineas(linea1, linea2, leidos1, leidos2, i);
		}
	}
	if(linea1) free(linea1);
	if(linea2) free(linea2);
	fclose(archivo1);
	fclose(archivo2);
	return 0;
}