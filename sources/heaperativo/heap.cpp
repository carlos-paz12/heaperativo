#include "heap.hpp"

///===================== PRIVATE INTERFACE =====================

/// @brief
/// @param index
void MinHeap::heapify_up(size_t index)
{
}

/// @brief
/// @param index
void MinHeap::heapify_down(size_t index)
{
}

///===================== PUBLIC INTERFACE =====================

/// @brief
/// @return
bool MinHeap::remove_root_if_zero()
{
}

/// @brief
/// @param i
/// @param j
void MinHeap::swap_nodes(size_t i_node_idx, size_t j_node_idx)
{
}

/// @brief
/// @param index
/// @return
int MinHeap::key(size_t index) const
{
}

/// @brief Converte uma fila em uma min-heap.
/// @param queue Fila a ser convertida.
/// @returns A min-heap contendo os elementos da fila.
MinHeap MinHeap::convert_queue_to_heap(Queue *queue)
{
  MinHeap heap;
  Node *current = queue->start;
  while (current)
  {
    heap.insert(current->process);
    current = current->next;
  }
  return heap;
}

/// @brief Converte a min-heap em uma fila.
/// @returns A fila contendo os elementos da min-heap.
Queue *MinHeap::convert_heap_to_queue() const
{
  Queue *q = init_queue();
  for (const Process &process : heap_)
  {
    insert_in_queue(q, process);
  }
  return q;
}

/// @brief
/// @param process_id
void MinHeap::update_key(unsigned int process_id)
{
}

/// @brief
/// @return
bool MinHeap::is_empty() const noexcept
{
}

/// @brief
/// @return
size_t MinHeap::size() const noexcept
{
}

/// @brief
/// @param process
void MinHeap::insert(const Process &process)
{
}

/// @brief
/// @return
Process MinHeap::extract_min() {}

/// @brief
/// @return
bool MinHeap::remove_root_if_zero() {}

/// @brief
/// @return
int MinHeap::root_key() const
{
}