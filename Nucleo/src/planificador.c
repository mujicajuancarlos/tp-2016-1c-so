/*
 * planificador.c
 *
 *  Created on: 28/4/2016
 *      Author: utnso
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <commons/log.h>
#include <commons/config.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include <mllibs/sockets/server.h>
#include <mllibs/sockets/client.h>
#include <mllibs/sockets/package.h>
#include <mllibs/log/logger.h>
#include "Nucleo.h"
#include "configuration.h"
#include "PCB.h"
#include "planificador.h"

void planificar(void* arguments){
	arg_struct *args = arguments;
	t_list* listaCPUs = args->listaCPUs;
	Estados* estados = args->estados;
	int socketServidor;				/* Descriptor del socket servidor */
	int socketCliente[MAX_CONEXIONES];/* Descriptores de sockets con clientes */
	int numeroClientes = 0;			/* Número clientes conectados */
	fd_set descriptoresLectura;	/* Descriptores de interes para select() */
	//int buffer;							/* Buffer para leer de los socket */
	int maximo;							/* Número de descriptor más grande */
	int i;								/* Para bubles */

	inicializarSockets(socketCliente);
	socketServidor = args->socketServerPlanificador;

	logTrace("Iniciando Planificador");

	/* Bucle infinito.
	 * Se atiende a si hay más clientes para conectar y a los mensajes enviados
	 * por los clientes ya conectados */
	while (1)
	{
		/* Cuando un cliente cierre la conexión, se pondrá un -1 en su descriptor
		 * de socket dentro del array socketCliente. La función compactaClaves()
		 * eliminará dichos -1 de la tabla, haciéndola más pequeña.
		 *
		 * Se eliminan todos los clientes que hayan cerrado la conexión */
		compactaClaves (socketCliente, &numeroClientes);

		/* Se inicializa descriptoresLectura */
		FD_ZERO (&descriptoresLectura);

		/* Se añade para select() el socket servidor */
		FD_SET (socketServidor, &descriptoresLectura);

		/* Se añaden para select() los sockets con los clientes ya conectados */
		for (i=0; i<numeroClientes; i++)
			FD_SET (socketCliente[i], &descriptoresLectura);

		/* Se el valor del descriptor más grande. Si no hay ningún cliente,
		 * devolverá 0 */
		maximo = dameMaximo (socketCliente, numeroClientes);

		if (maximo < socketServidor)
			maximo = socketServidor;

		logTrace("Planificador: Esperando conexiones");

		/* Espera indefinida hasta que alguno de los descriptores tenga algo
		 * que decir: un nuevo cliente o un cliente ya conectado que envía un
		 * mensaje */
		select (maximo + 1, &descriptoresLectura, NULL, NULL, NULL);

		logTrace("Planificador: Nueva solicitud");

		/* Se comprueba si algún cliente ya conectado ha enviado algo */
		for (i=0; i<numeroClientes; i++)
		{
			logTrace("Planificador: Solicitud %d",socketCliente[i]);
			if (FD_ISSET (socketCliente[i], &descriptoresLectura))
			{
				Package package;
				/* Se lee lo enviado por el cliente y se escribe en pantalla */
				//if ((leerSocket (socketCliente[i], (char *)&buffer, sizeof(int)) > 0))
				if(recieve_and_deserialize(&package,socketCliente[i]) > 0){
					logDebug("Thread %d envía [message code]: %d, [Mensaje]: %s", i+1, package.msgCode, package.message);
					if(package.msgCode==CPU_LIBRE || package.msgCode==PROGRAM_READY){
						atenderProcesos(estados,listaCPUs);
					}
				}
				else
				{
					/* Se indica que el cliente ha cerrado la conexión y se
					 * marca con -1 el descriptor para que compactaClaves() lo
					 * elimine */
					logDebug("Thread %d ha cerrado la conexión", i+1);
					socketCliente[i] = -1;
				}
			}
		}

		/* Se comprueba si algún cliente nuevo desea conectarse y se le
		 * admite */
		if (FD_ISSET (socketServidor, &descriptoresLectura)){
			nuevoCliente (socketServidor, socketCliente, &numeroClientes, MAX_CONEXIONES);
			logInfo("Planificador: Aceptado nuevo cliente");
		}
	}
}


void atenderProcesos(Estados* estados, t_list* listaCPUs){
	CPU* cpu = getCPUlibre(listaCPUs);
	while(cpu!=NULL && hayProcesosEnREADY(estados)){
		startExec(estados,cpu->cpuFD);
		cpu->libre = 0;

		cpu = getCPUlibre(listaCPUs);
	}
}

bool hayProcesosEnREADY(Estados* estados){
	return (estados->ready->elements->elements_count)>0;
}

CPU* getCPUlibre(t_list* listaCPUs){
	int i;
	for(i=0;i<listaCPUs->elements_count;i++){
		CPU* cpu = list_get(listaCPUs,i);
		if(cpu->libre){
			return cpu;
		}
	}
	return NULL;
}

void inicializarSockets(int* sockets){
	int i;
	for(i=0;i<MAX_CONEXIONES;i++){
		sockets[i]=-1;
	}
}