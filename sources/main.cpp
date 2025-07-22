#include "heap.hpp"
#include "process.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#define p(q) std::cout << q << "\n"

// Função para inicializar o arquivo de log
void init_log() {
  std::ofstream logFile("log.txt");
  if (logFile.is_open()) {
    logFile << "=== SIMULADOR DE ESCALONAMENTO DE PROCESSOS ===\n";
    logFile << "Inicio da simulacao: " << std::time(nullptr) << "\n\n";
    logFile.close();
  }
}

// Função para escrever no log
void write_to_log(const std::string& message) {
  std::ofstream logFile("log.txt", std::ios::app);
  if (logFile.is_open()) {
    logFile << message << "\n";
    logFile.close();
  }
}

// Função para logar o estado inicial da fila
void log_initial_queue(Queue *q) {
  write_to_log("=== ESTADO INICIAL DA FILA ===");
  Node *current = q->start;
  int position = 1;
  
  while (current != NULL) {
    std::string log_entry = "Posicao " + std::to_string(position) + 
                           ": ID=" + std::to_string(current->process.id) +
                           ", Program=" + std::string(getProgramName(current->process.name)) +
                           ", time_to_kill=" + std::to_string(current->process.time_to_kill) +
                           ", time_used=" + std::to_string(current->process.time_used);
    write_to_log(log_entry);
    current = current->next;
    position++;
  }
  write_to_log("");
}

// Função para logar execução de processo
void log_process_execution(const Process& proc, int execution_round) {
  std::string log_entry = "=== ROUND " + std::to_string(execution_round) + " ===";
  write_to_log(log_entry);
  
  log_entry = "Executando processo: " + std::string(getProgramName(proc.name));
  write_to_log(log_entry);
  
  log_entry = "Process ID: " + std::to_string(proc.id);
  write_to_log(log_entry);
  
  log_entry = "Time to Kill: " + std::to_string(proc.time_to_kill);
  write_to_log(log_entry);
  
  log_entry = "Time Used: " + std::to_string(proc.time_used);
  write_to_log(log_entry);
  
  if (proc.time_used >= proc.time_to_kill) {
    log_entry = "*** PROCESSO FINALIZADO ***";
    write_to_log(log_entry);
  } else {
    log_entry = "Processo reinserido no heap (ainda nao terminou)";
    write_to_log(log_entry);
  }
  write_to_log("");
}

// Função para logar estado atual da fila
void log_current_queue_state(Queue *q) {
  if (q->size == 0) {
    write_to_log("Fila vazia - todos os processos foram finalizados");
    return;
  }
  
  write_to_log("--- Estado atual da fila ---");
  Node *current = q->start;
  int position = 1;
  
  while (current != NULL) {
    std::string log_entry = "Pos " + std::to_string(position) + 
                           ": ID=" + std::to_string(current->process.id) +
                           ", " + std::string(getProgramName(current->process.name)) +
                           ", restante=" + std::to_string(current->process.time_to_kill - current->process.time_used);
    write_to_log(log_entry);
    current = current->next;
    position++;
  }
  write_to_log("");
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << argv[0] << " simula o gerenciamento de N processos.\n";
    return EXIT_FAILURE;
  }

  int n_process = std::atoi(argv[1]);
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  
  // Inicializa o sistema de log
  init_log();

  Queue *q = create_queue_of_process(n_process + 1);
  MinHeap heap = MinHeap::convert_queue_to_heap(q);

  // Log do estado inicial
  std::cout << "Estado inicial da fila:\n";
  print_queue_of_process(q);
  log_initial_queue(q);

  int execution_round = 1;
  
  while (!heap.is_empty()) {
    // Executa o processo com maior prioridade (raiz)
    Process proc = heap.extract_min();

    std::cout << "\n=== ROUND " << execution_round << " ===\n";
    execute_Process(&proc);
    
    // Log da execução
    log_process_execution(proc, execution_round);
    
    // Se o processo ainda não terminou (time_used < time_to_kill), reinsere no heap
    if (proc.time_used < proc.time_to_kill) {
      heap.insert(proc);
    }
    
    // Converte o heap atualizado para fila e imprime
    Queue *updated_q = heap.convert_heap_to_queue();
    std::cout << "\nEstado atual da fila:\n";
    print_queue_of_process(updated_q);
    
    // Log do estado atual
    log_current_queue_state(updated_q);
    
    free_queue(updated_q);
    execution_round++;
  }

  write_to_log("=== SIMULACAO FINALIZADA ===");
  write_to_log("Todos os processos foram executados com sucesso!");
  
  std::cout << "\nSimulacao finalizada! Verifique o arquivo log.txt para detalhes.\n";

  free_queue(q);
  return EXIT_SUCCESS;
}
