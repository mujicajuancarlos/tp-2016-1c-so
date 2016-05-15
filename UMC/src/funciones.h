/*
 * funciones.h
 *
 *  Created on: 8/5/2016
 *      Author: utnso
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <mllibs/sockets/server.h>
#include <mllibs/sockets/client.h>
#include <mllibs/sockets/package.h>
#include <stdlib.h>
#include "configuration.h"

#define MAX_CLIENTES 10 //cantidad maxima de conexiones por socket (CPUs)

//codigos de operaciones de la UMC
//esto tenemos que ver bien despues que decidimos hacer para codificarlas
#define INIT_PROGRAM 1
#define SOLICITAR_BYTES_PAGINA 2
#define ALMACENAR_BYTES_PAGINA 3
#define END_PROGRAM 4
#define HANDSHAKE 5
#define SWITCH_PROCESS 6
//---------------------
//operaciones SWAP
#define SOLICITAR_PAGINA_SWAP 20
#define ALMACENAR_PAGINA_SWAP 21
#define ALMACENAR_NUEVO_PROGRAMA_SWAP 22
#define ELIMINAR_PROGRAMA_SWAP 23
//---------------------
//codigos de operacion con el Nucleo
#define HANDSHAKE_NUCLEO 100
//---------------------
//codigos de operacion con los CPU's
#define HANDSHAKE_CPU 80

typedef struct tableRow {
	int pid;
	int page;
}tableRow;

typedef struct arg_thread_cpu {
	int socket_cpu,
		socket_swap;
} t_arg_thread_cpu;

typedef char* pagina;
typedef void* memoria; //TODO No me convence mucho el nombre pero es lo primero que se me ocurrio, sean libres de modificarlo

void handleClients(Configuration*);
void comunicarSWAP(int, int);
int conectarConSwap(Configuration*);
void inicializarUMC(Configuration*);
tableRow* crearTablaDePaginas(int);
void handle_cpu(t_arg_thread_cpu*);

#endif /* FUNCIONES_H_ */
