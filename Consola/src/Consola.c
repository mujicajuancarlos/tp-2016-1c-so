/*
 ============================================================================
 Name        : Consola.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "consola.h"

int main(int argc, char* argv[]){

	Parameters* parametros;
	FILE* fp;

	//Crear el logger
	t_log* logger = log_create("consola.log","ELESTAC",true, LOG_LEVEL_DEBUG);

	//Obtener parametros
	parametros = interpretar_parametros(argc, argv);
	//Cierro el logger
	log_destroy(logger);

	initLogMutex("consola2.log","ELESTAC",true,LOG_LEVEL_DEBUG);

	logInfo("Consola iniciada");

	if(parametros->programa == NULL){
		logDebug("No fue espesificado un programa, en este momento la consola deberia permitir usar linea de comandos para acceder al archivo");
		return EXIT_FAILURE;
	}

	logInfo("Ejecutando: %s\n",parametros->programa);

	//Hay que decidir si mandamos el programa asi como esta o lo pasamos por el parcer primero
	if((fp=fopen(parametros->programa,"r"))==NULL){
		logError("Error al abrir el programa %s",parametros->programa);
		return EXIT_FAILURE;
	}

	while(!feof(fp)){
		printf("%c",fgetc(fp));
	}
	//----------------------------------------------------------------------------------------------------------------------------/

	comunicacionConNucleo(parametros->config);

	logInfo("Fin programa\n");

	//Libero la memoria
	liberar_parametros(parametros);

	//Cierro el archivo ansisop
	fclose(fp);

	return EXIT_SUCCESS;
}
