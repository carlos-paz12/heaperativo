#include "process.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char *getProgramName(UnixProgram program) {
  switch (program) {
  case VI:
    return "vi";
  case EX:
    return "ex";
  case AWK:
    return "awk";
  case SED:
    return "sed";
  case CC:
    return "cc";
  case MAKE:
    return "make";
  case NROFF:
    return "nroff";
  case TROFF:
    return "troff";
  case TBL:
    return "tbl";
  case EQN:
    return "eqn";
  case YACC:
    return "yacc";
  case LEX:
    return "lex";
  case ADB:
    return "adb";
  case DB:
    return "db";
  case CSH:
    return "csh";
  case EMACS:
    return "emacs";
  case TIP:
    return "tip";
  case CRON:
    return "cron";
  case FTP:
    return "ftp";
  case TELNET:
    return "telnet";
  default:
    return "unknown";
  }
}

UnixProgram getRandomProgram() { return (UnixProgram)(rand() % PROGRAM_COUNT); }

Process create_Process() {
  UnixProgram program = getRandomProgram();
  int id = (rand() % IDMAXREF) + 1;
  int t_kill = (rand() % 999) + 1;
  Process process;
  process.id = id;
  process.name = program;
  process.time_to_kill = t_kill;
  process.time_used = 0;
  return process;
}

void update_used_time(Process *p, unsigned int time) { p->time_used = time; }

void execute_Process(Process *p) {
  std::cout << "Executing process: " << getProgramName(p->name) << '\n';
  unsigned int quantum_time = (rand() % 100) + 1; // Quantum de tempo de 1 a 100
  // Incrementa o tempo usado, mas não excede time_to_kill
  unsigned int new_time_used = p->time_used + quantum_time;
  if (new_time_used > p->time_to_kill) {
    new_time_used = p->time_to_kill;
  }
  
  update_used_time(p, new_time_used);
}

Queue *init_queue() {
  Queue *q = (Queue *)malloc(sizeof(Queue));
  q->size = 0;
  q->start = NULL;
  q->end = NULL;
  return q;
}

void insert_in_queue(Queue *q, Process p) {
  // Node *n = malloc(sizeof(Node));
  Node *n = new Node;
  n->process = p;
  n->next = NULL;
  if (q->size == 0) {
    q->start = n;
    q->end = n;
    q->size = q->size + 1;
  } else {
    q->end->next = n;
    q->end = n;
    q->size = q->size + 1;
  }
}

Queue *create_queue_of_process(int n) {
  Queue *q = init_queue();
  while (q->size < n) {
    Process p = create_Process();
    insert_in_queue(q, p);
  }
  return q;
}

void print_queue_of_process(Queue *q) {
  srand((unsigned)time(NULL));
  Node *wanderer = q->start;
  while (wanderer != NULL) {
    printf("Process id=%d, Program=%s, time_to_kill=%d, time_used=%d \n", wanderer->process.id,
           getProgramName(wanderer->process.name), wanderer->process.time_to_kill, wanderer->process.time_used);
    wanderer = wanderer->next;
  }
}

void free_queue(Queue *q) {
  Node *current = q->start;
  while (current) {
    Node *next = current->next;
    delete current;
    current = next;
  }
  delete q;
}
