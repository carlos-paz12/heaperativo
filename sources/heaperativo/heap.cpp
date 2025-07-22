#include "heap.hpp"
#include <stdexcept>

///===================== PRIVATE INTERFACE =====================
/// @brief Troca dois processos de posição na heap e atualiza o mapa de índices.
///
/// Essa função é fundamental para manter a consistência entre o vetor `m_processes`
/// e o mapa `id_to_index`, garantindo que os IDs sempre apontem para os índices corretos.
///
/// @param i_node_idx Índice do primeiro processo.
/// @param j_node_idx Índice do segundo processo.
void MinHeap::swap_nodes(size_t i_node_idx, size_t j_node_idx) {
  std::swap(m_processes[i_node_idx], m_processes[j_node_idx]);

  id_to_index[m_processes[i_node_idx].id] = i_node_idx;
  id_to_index[m_processes[j_node_idx].id] = j_node_idx;
}

/// @brief Calcula a chave de prioridade de um processo na heap.
/// @param index Índice do processo.
/// @return A chave de prioridade de `index`.
int MinHeap::key(size_t index) const {
  if (index >= m_processes.size()) {
    throw std::out_of_range("Índice inválido em MinHeap::key()");
  }
  const auto &p = m_processes[index];
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
  while (true) {
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;
    size_t smallest = index;

    // Verifique os limites usando m_size e m_processes.size()
    if (left < m_size && left < m_processes.size() && key(left) < key(smallest)) {
      smallest = left;
    }
    if (right < m_size && right < m_processes.size() && key(right) < key(smallest)) {
      smallest = right;
    }

    if (smallest == index)
      break;

    swap_nodes(index, smallest);
    index = smallest;
  }
}

///===================== PUBLIC INTERFACE =====================

/// @brief Converte uma fila em uma min-heap.
/// @param queue Fila a ser convertida.
/// @returns A min-heap contendo os elementos da fila.
MinHeap MinHeap::convert_queue_to_heap(Queue *queue) {
  MinHeap heap{};
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

bool MinHeap::is_empty() const noexcept {
  return m_size == 0; // Use m_size em vez de m_processes.empty()
}
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
  m_size++;
  heapify_up(index);
}

/// @brief Remove e retorna o processo com maior prioridade (raiz da heap).
///
/// Após remover o processo da raiz, o último elemento da heap é movido para a raiz
/// e `heapify_down` é chamado para restaurar a propriedade de min-heap.
///
/// @return O processo de menor chave (maior prioridade).
Process MinHeap::extract_min() {
  if (is_empty()) {
    throw std::runtime_error("Não é possível extrair de uma heap vazia.");
  }

  Process min_process = m_processes[0];
  id_to_index.erase(min_process.id);
  m_size--; // Mova esta linha para antes da remoção

  if (m_size > 0) {
    // Move o último elemento para a raiz
    m_processes[0] = m_processes[m_size]; // Use m_size em vez de back()
    id_to_index[m_processes[0].id] = 0;
    heapify_down(0);
  }

  m_processes.resize(m_size); // Redimensione o vetor após a remoção
  return min_process;
}

/// @brief Retorna a chave de prioridade do processo raiz da heap.
///
/// A raiz da heap é sempre o processo com maior prioridade (menor chave).
///
/// @return A chave de prioridade da raiz, ou -1 se heap estiver vazia.
int MinHeap::root_key() const {
  if (is_empty())
    return -1;
  return key(0);
}

/// @brief
/// @param process_id
void MinHeap::update_key(unsigned int process_id) {
  auto it = id_to_index.find(process_id);
  if (it == id_to_index.end())
    return; // ID não encontrado

  size_t index = it->second;

  // Tenta reequilibrar para cima e para baixo
  heapify_up(index);
  heapify_down(index);
}

/// @brief
/// @return
bool MinHeap::remove_root_if_zero() {
  if (is_empty())
    return false;

  if (root_key() == 0) {
    extract_min(); // remove a raiz
    return true;
  }

  return false;
}
