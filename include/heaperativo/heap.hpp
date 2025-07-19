#ifndef HEAP_HPP
#define HEAP_HPP

#include "process.hpp"
#include <functional>
#include <unordered_map>
#include <vector>

/// @brief
class MinHeap {
private:
  //> Armazenamento dos processos
  std::vector<Process> heap_;
  //> Mapeamento ID -> índice
  std::unordered_map<unsigned int, size_t> index_map_;

  void swap_nodes(size_t i_node_idx, size_t j_node_idx);

  //> Calcula a chave (time_to_kill - time_used)
  int key(size_t index) const;

  //> Esses métodos são privados porque não devem ser chamados diretamente
  void heapify_up(size_t index);
  void heapify_down(size_t index);

public: 
  //> Funções de conversão entre fila e heap
  static MinHeap convert_queue_to_heap(Queue *queue); //> não apaga a fila original (se precisar fazer isso, chamar free_queue)
  Queue *convert_heap_to_queue() const; //> usa insert_in_queue e init_queue mas não apaga a heap original (por isso const)
  //> funções de conversão em geral não devem apagar a estrutura original
  //> é responsabilidade do usuário apagar a estrutura original se necessário
  //> pode ser bem contraintuitivo e inesperada a exclusão dependendo do uso
  //> Exemplo:
  /*
    MinHeap active_processes = [...];
    Queue *backup = active_processes.convert_heap_to_queue();
  */
  //> seria ideal se os processos fossem apagados?
  //> não! métodos devem sempre fazer coisas previsíveis
  //> antes de fazer algo assim, pense:
  //> "em TODAS as situações X TEM DE acontecer DENTRO de Y?"
  //> onde X é a exclusão e Y é a conversão nesse caso
  //> mas existe um equilibrio, claro
  //> então ao menos se limite à função fazer
  //> apenas o que o nome dela diz que ela faz
  //> aula gratis :3

  //> Demais funções
  void update_key(unsigned int process_id);
  bool is_empty() const noexcept;
  size_t size() const noexcept;
  bool remove_root_if_zero(); //> Retorna true se o root for removido
  int root_key() const; //> Retorna a chave do root
  void insert(const Process &process);
  Process extract_min();
};

#endif // HEAP_HPPulamento