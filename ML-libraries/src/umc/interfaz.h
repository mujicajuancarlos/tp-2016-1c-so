/*
 * interfaz.h
 *
 *  Created on: 19/5/2016
 *      Author: utnso
 */

#ifndef UMC_INTERFAZ_H_
#define UMC_INTERFAZ_H_

#include <stdarg.h>
#include "../sockets/server.h"
#include "../sockets/client.h"
#include "../sockets/package.h"

#define INICIALIZAR_PROGRAMA_UMC 1
#define LEER_PAGINA_UMC 2
#define ESCRIBIR_PAGINA_UMC 3
#define FINALIZAR_PROGRAMA_UMC 4
#define RESULTADO_OPERACION 5

//tipo pagina universal
typedef char* pagina;

//Interfaz---------------------------------------------
int inicializar_programa(uint32_t,uint32_t,char*);
char* leer_pagina(uint32_t,uint32_t);
int escribir_pagina(uint32_t,uint32_t,char*);
int finalizar_programa(uint32_t);
void definir_socket_umc(int*);
//-----------------------------------------------------

#endif /* UMC_INTERFAZ_H_ */