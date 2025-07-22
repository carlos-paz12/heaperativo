#include "heap.hpp"

///===================== PRIVATE INTERFACE =====================
/// @brief
/// @param i
/// @param j
void MinHeap::swap_nodes(size_t i_node_idx, size_t j_node_idx) {}

/// @brief Calcula a chave de prioridade de um processo na heap.
/// @param index Índice do processo.
/// @return A chave de prioridade de `index`.
int MinHeap::key(size_t index) const {
  const auto &p{m_processes[index]};
  return p.time_to_kill - p.time_used;
}

/// @brief Reorganiza a heap de baixo para cima a partir de um índice.
///
/// Esse método é usado após a inserção de um novo processo no heap.
/// Ele compara a chave do processo inserido com a do seu pai e,
/// caso a chave do filho seja menor (maior prioridade), realiza uma troca.
/// O processo sobe na árvore até que a propriedade de min-heap seja restaurada.
///
/// @param index Índice do novo elemento inserido.
void MinHeap::heapify_up(size_t index) {
  while (index > 0) {
    size_t parent{(index - 1) / 2};
    if (key(index) < key(parent)) {
      swap_nodes(index, parent);
      index = parent;
    } else {
      break;
    }
  }
}

/// @brief
/// @param index
void MinHeap::heapify_down(size_t index) {
  size_t left, right, smallest;

  while (true) {
    left = 2 * index + 1;
    right = 2 * index + 2;
    smallest = index;

    // Compara com filho esquerdo
    if (left < m_size && key(left) < key(smallest)) {
      smallest = left;
    }

    // Compara com filho direito
    if (right < m_size && key(right) < key(smallest)) {
      smallest = right;
    }

    // Se o menor já é o próprio índice
    if (smallest == index) break;

    // Troca com o menor filho e continua
    swap_nodes(index, smallest);
    index = smallest;
  }
}

///===================== PUBLIC INTERFACE =====================
/// @brief Converte uma fila em uma min-heap.
/// @param queue Fila a ser convertida.
/// @returns A min-heap contendo os elementos da fila.
MinHeap MinHeap::convert_queue_to_heap(Queue *queue) {
  MinHeap heap;
  Node *current = queue->start;
  while (current) {
    heap.insert(current->process);
    current = current->next;
  }
  return heap;
}

/// @brief Converte a min-heap em uma fila.
/// @returns A fila contendo os elementos da min-heap.
Queue *MinHeap::convert_heap_to_queue() const {
  Queue *q = init_queue();
  for (const Process &process : m_processes) {
    insert_in_queue(q, process);
  }
  return q;
}

/// @brief Verifica se a heap está vazia.
/// @return `true` se a heap estiver vazia. `false` caso contrário.
bool MinHeap::is_empty() const noexcept { return m_processes.empty(); }

/// @brief Retorna o número atual de processos armazenados na heap.
/// @return Quantidade de processos válidos presentes na estrutura.
size_t MinHeap::size() const noexcept { return m_size; }

/// @brief Retorna a capacidade total de armazenamento da heap.
///
/// Representa o número total de elementos possíveis no vetor subjacente,
/// independentemente de quantos processos válidos estão presentes.
///
/// @return Capacidade total do vetor interno da heap.
size_t MinHeap::capacity() const noexcept { return m_processes.size(); }

/// @brief Insere um novo processo na heap.
///
/// Adiciona o processo ao final do vetor e reorganiza o heap utilizando
/// `heapify_up` para garantir a propriedade de min-heap.
/// O processo também é registrado no mapa `id_to_index` para acesso eficiente.
///
/// @param process Processo a ser inserido.
void MinHeap::insert(const Process &process) {
  m_processes.push_back(process);
  size_t index{m_processes.size() - 1};
  id_to_index[process.id] = index;
  heapify_up(index);
}

/// @brief
/// @return
Process MinHeap::extract_min() {}

/// @brief
/// @return
int MinHeap::root_key() const {}

/// @brief
/// @param process_id
void MinHeap::update_key(unsigned int process_id) {
  auto it = id_to_index.find(process_id);
  if (it == id_to_index.end()) return; // ID não encontrado

  size_t index = it->second;

  // Tenta reequilibrar para cima e para baixo
  heapify_up(index);
  heapify_down(index);
}

/// @brief
/// @return
bool MinHeap::remove_root_if_zero() {}