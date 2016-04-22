/*
 * config.h
 *
 *  Created on: 18/4/2016
 *      Author: utnso
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#define NUCLEO_CONFIG_PATH "../nucleo.conf"
#define PUERTO_PROG "PUERTO_PROG"
#define PUERTO_CPU "PUERTO_CPU"
#define IP_NUCLEO "IP_NUCLEO"
#define QUANTUM "QUANTUM"
#define QUANTUM_SLEEP "QUANTUM_SLEEP"
#define SEM_IDS "SEM_IDS"
#define SEM_INIT "SEM_INIT"
#define IO_IDS "IO_IDS"
#define IO_SLEEP "IO_SLEEP"
#define SHARED_VARS "SHARED_VARS"

typedef struct Configuration {
	int puerto_nucleo_cpu;
	int puerto_nucleo_prog;
	char* ip_nucleo;
} Configuration;

#endif /* CONFIGURATION_H_ */
