#ifndef NODE_H
#define NODE_H

#include "process.h"

/**
 *
 * Estrutura para representar os node em uma fila
 *
 */
struct Node {
  Process process;
  Node *next;
};

#endif //!< NODE_H