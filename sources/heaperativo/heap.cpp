#include "heap.hpp"

///===================== PRIVATE INTERFACE =====================

/// @brief
/// @param index
void MinHeap::heapify_up(size_t index)
{}

/// @brief
/// @param index
void MinHeap::heapify_down(size_t index)
{}

/// @brief
/// @param i
/// @param j
void MinHeap::swap_nodes(size_t i, size_t j)
{}

/// @brief
/// @param index
/// @return
int MinHeap::key(size_t index) const 
{}

///===================== PUBLIC INTERFACE =====================

/// @brief
/// @param queue
/// @return
MinHeap MinHeap::convert_queue_to_heap(Queue *queue) 
{}

/// @brief
/// @return
Queue *MinHeap::convert_heap_to_queue() const 
{}

/// @brief
/// @param process_id
void MinHeap::update_key(unsigned int process_id) 
{}

/// @brief
/// @return
bool MinHeap::is_empty() const noexcept 
{}

/// @brief
/// @return
size_t MinHeap::size() const noexcept 
{}

/// @brief
/// @param index
/// @return
Process *MinHeap::get_process_at(size_t index) noexcept 
{}

/// @brief
/// @param process
void MinHeap::insert(const Process &process) 
{}

/// @brief
/// @return
Process MinHeap::extract_min() 
{}