#include "heap.hpp"
#include "process.hpp"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int n_process;
  if (argc != 2) {
    fprintf(stderr, "%s simula o gereciamento de 0 processos\n", argv[0]);
    return 1;
  }
  n_process = atoi(argv[1]);
  if (n_process <= 0) {
    fprintf(stderr, "A quantidade de processo deve ser maior que 0.\n");
    return 1;
  }
  Queue *q = create_queue_of_process(n_process + 1);

  MinHeap heap;

  // estamos assumindo que

  while (heap.is_empty() /*teste para manter o loop até o heap ficar vazio*/) {

    int n = (rand() % (n_process + 1));

    // nao vamos considerar o 0 porque nao existe logicamente (vejam os
    // slides!!!!!!) vamos de 1 até random_number%(n_process+1) caso n_process
    // for 4: vamos de 1 até mod 5, que eh 4
    //    | | | |
    //    v v v v
    // 0 1 2 3 4
    // ^ nao consideramos

    for (int i = 1; i <= n; i++) {
      // execute_Process(heap.heap_[i]);   // isso aqui tá dando errado porque
      // nao sabemos como a heap sera implementada
      //  o nosso objetivo eh pegar o process de indice i e executá-lo
      heap.update_key(i);
      heap.heapify_up(i); // atualizamos o key, devemos fazer o heapify para
                          // manter as propriedades de uma min heap
      // heap.remove_if();
    }
  }

  return 0;
}