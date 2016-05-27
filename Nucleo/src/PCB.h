/*
 * PCB.h
 *
 *  Created on: 26/4/2016
 *      Author: utnso
 */

#ifndef PCB_H_
#define PCB_H_

#include <commons/collections/queue.h>
#include <commons/collections/list.h>
#include <parser/metadata_program.h>
#include <mllibs/nucleoCpu/interfaz.h>
#include <mllibs/umc/interfaz.h>


/*
 * Estructura con las colas de Estados
 */
typedef struct Estados {
	t_queue* new;
	t_queue* ready;
	t_list* execute;
	t_queue** block;//array de colas de solicitud_io
	t_queue* exit;
} Estados;

typedef struct io_arg_struct {
    Estados* estados;
    int io_index;//posicion del dispositivo en los arrays
    int socketPlanificador;
} io_arg_struct;

//wrapper que se crea con cada solicitud de I/O de un proceso
//va a la cola de bloqueados correspondiente al dispositivo (io_id)
typedef struct solicitud_io {
    PCB* pcb;
    char* io_id;
	int cant_operaciones;
} solicitud_io;


//funciones
PCB* buildNewPCB(int consolaFD, char* programa);
int getNextPID();
Estados* inicializarEstados();
void destroyEstados(Estados* estados);
void destroy_solicitud_io(solicitud_io* self);
void sendToNEW(PCB* pcb, Estados* estados);
PCB* getNextFromNEW(Estados* estados);
solicitud_io* getNextFromBlock(Estados* estados, int io_index);
PCB* getNextFromREADY(Estados* estados);
void sendToREADY(PCB* pcb, Estados* estados);
void sendToEXEC(PCB* pcb, Estados* estados);
void sendToBLOCK(solicitud_io* solicitud, int io_index, Estados* estados);
void sendToEXIT(PCB* pcb, Estados* estados);
void sendFromEXECtoREADY(Estados* estados, int pid);
void abortFromREADY(Estados* estados,int index);
void abortFromBLOCK(Estados* estados,int index, int io_index);
void abortFromNEW(Estados* estados,int index);
void abortFromEXEC(Estados* estados,int pid);
PCB* removeFromEXEC(Estados* estados, int pid);
PCB* removeNextFromEXIT(Estados* estados);
PCB* getFromEXEC(Estados* estados, int pid);
bool hayProcesosEnREADY(Estados* estados);
int addQuantumToExecProcess(PCB* proceso, int quantum);
void quantumFinishedCallback(Estados* estados, int pid, int quantum, int socketCPU, int socketPlanificador);
void contextSwitchFinishedCallback(Estados* estados, PCB* pcbActualizado, int socketPlanificador);
void notifyProcessREADY(Estados* estados, PCB* pcb, int socketPlanificador);
void finalizarPrograma(Estados* estados, PCB* pcb, int socketCPU, int socketPlanificador);
void actualizarPCB(PCB* local, PCB* actualizado);
void switchProcess(Estados* estados, int pid, int socketCPU);
void abortProcess(Estados* estados, int pid, int socketCPU);
void continueExec(int socketCPU, PCB* pcb);
void startExec(Estados* estados, int socketCPU);
void informarEjecucionCPU(int socketCPU, int accion, PCB* pcb);
void informarCPU(int socketCPU, int accion, int pid);
void iniciarPrograma(Estados* estados, int consolaFD, int socketPlanificador, char* programa);
void abortarPrograma(Estados* estados, int consolaFD);
bool findAndExitPCBnotExecuting(Estados* estados, int consolaFD);
void findAndExitPCBexecuting(Estados* estados, int consolaFD);
void informarPlanificador(int socketPlanificador, int accion, int pid);
void getCodeIndex(PCB* pcb, char* programa);
int esInstruccionValida(char* str, int offset, int length);
int getCantidadPaginasPrograma(char* programa, int size_pagina);
int getCantidadPaginasNecesarias(char* programa, int size_pagina, int stack_size);
pagina* getPaginasFromPrograma(char* programa, int size_pagina);
void destroyPaginas(pagina* paginas, int cantidad);
void launch_IO_threads(Estados* estados, int socketPlanificador);
void ejecutarIO(void* arguments);
void atenderSolicitudDispositivoIO(Estados* estados, uint32_t pid, char* io_id, uint32_t cant_operaciones);
void destroy_io_arg_struct(io_arg_struct *args);
int getPosicionDispositivo(char** lista_ids, int len, char* io_id);
void free_solicitud_io(solicitud_io* solicitud);

#endif /* PCB_H_ */
