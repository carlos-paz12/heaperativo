#ifndef HEAP_HPP
#define HEAP_HPP

#include "process.hpp"
#include <functional>
#include <vector>
#include <unordered_map>
#include "queue.hpp"
#include "node.hpp"

/// @brief
class MinHeap
{
private:
  //> Armazenamento dos processos
  std::vector<Process> heap_;
  //> Mapeamento ID -> índice
  std::unordered_map<unsigned int, size_t> index_map_;

  void heapify_up(size_t index);
  void heapify_down(size_t index);

  void swap_nodes(size_t i, size_t j);
  
  //> Calcula a chave (time_to_kill - time_used)
  int key(size_t index) const;

public:
  static MinHeap convert_queue_to_heap(Queue *queue);
  //> usa insert_in_queue e init_queue
  Queue *convert_heap_to_queue() const;

  void update_key(unsigned int process_id);

  bool is_empty() const noexcept;
  size_t size() const noexcept;

  //> Acesso seguro
  Process *get_process_at(size_t index) noexcept;

  void insert(const Process &process);
  Process extract_min();
};

#endif // HEAP_HPP