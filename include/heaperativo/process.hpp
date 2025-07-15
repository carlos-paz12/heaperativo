#ifndef PROCESS_HPP
#define PROCESS_HPP

#include "unix_program.hpp"
#include <time.h>

#define IDMAXREF 500

/**
 *
 * Estrutura para representar processos de programas Unix em execução
 *
 */
struct Process {
  unsigned int id;
  unix_program name;
  unsigned int time_to_kill;
  unsigned int time_used;
};

/**
 *
 * Função que irá criar processos de forma pseudo-aleatória
 *
 */
Process create_process();

/**
 *
 * Função que atualiza o valor do time_used de um process
 */
void update_used_time(Process *&p, int time);

/**
 *
 * Função que simula a execução de um processo p
 */
void execute_Process(Process *&p);

#endif // PROCESS_HPP