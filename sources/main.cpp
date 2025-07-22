#include "heap.hpp"
#include "process.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << argv[0] << " simula o gerenciamento de N processos.\n";
    return EXIT_FAILURE;
  }

  int n_process = std::atoi(argv[1]);

  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  Queue *q = create_queue_of_process(n_process + 1);
  MinHeap heap = MinHeap::convert_queue_to_heap(q);

  print_queue_of_process(q);

  while (!heap.is_empty()) {
    // Executa o processo com maior prioridade (raiz)
    Process proc = heap.extract_min();

    execute_Process(&proc);
  }

  return EXIT_SUCCESS;
}
