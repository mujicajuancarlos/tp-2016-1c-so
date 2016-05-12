/*
 * fileHandler.h
 *
 *  Created on: 5/5/2016
 *      Author: utnso
 */

#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

#include "configuration.h"

typedef char* pagina;

//representa una fila en la tabla de paginas del Swap (estructura de control)
typedef struct tableRow {
	int pid;
	int page;
}tableRow;

void inicializarSwap(Configuration* conf);
void crearBitMap();
int getFirstAvailableBlock(int cantPaginas);
void escribirPaginaEnFrame(int frame, pagina pag);
void escribirPaginasEnFrame(int frame, pagina* paginas, int cantPaginas);
int getFileSize();
void cerrarArchivoSwap();
pagina leerPaginaFromFrame(int frame);
void crearArchivoSwap();
void crearTablaDePaginas();
void destroyTabla();
void ejemploPagina();
t_bitarray* getBitMap();
tableRow* getTablaDePaginas();
void guardarPrograma(int frame, int pid, int cantPaginas, pagina* paginas);
void eliminarPrograma(int pid);
int buscarFramePorPagina(int pid, int pagina);
pagina leerPaginaDeProceso(int pid, int paginaNro);
void escribirPaginaDeProceso(int pid, int paginaNro, pagina pag);


#endif /* FILEHANDLER_H_ */