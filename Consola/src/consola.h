/*
 * consola.h
 *
 *  Created on: 21/4/2016
 *      Author: utnso
 */

#ifndef CONSOLA_H_
#define CONSOLA_H_

//codigos de operaciones de la Consola
//esto tenemos que ver bien despues que decidimos hacer para codificarlas
#define NEW_ANSISOP_PROGRAM 10
#define ANSISOP_PROGRAM 11
#define HANDSHAKE 12
//---------------------

typedef struct Configuration {
	int puerto_nucleo;
	char* ip_nucleo;
} Configuration;

//prototipos de funciones
void handshake(Package* package,int serverSocket);
void comunicacionConNucleo(Configuration* config);
Configuration* configurar ();
void iniciarProgramaAnsisop(Package* package,int serverSocket);

#endif /* CONSOLA_H_ */
