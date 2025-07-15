#ifndef UNIX_PROGRAM
#define UNIX_PROGRAM

/**
 *
 * Enum para representar programas Unix
 *
 */
enum UnixProgram {
  VI,
  EX,
  AWK,
  SED,
  CC,
  MAKE,
  NROFF,
  TROFF,
  TBL,
  EQN,
  YACC,
  LEX,
  ADB,
  DB,
  CSH,
  EMACS,
  TIP,
  CRON,
  FTP,
  TELNET,
  PROGRAM_COUNT // usado para saber o total de programas
};

/**
 *
 * Função para obter o nome do programa como string
 *
 */
const char *get_program_name(UnixProgram program);

/**
 *
 * Função que pega um UnixProgram aleatoriamente
 *
 */
UnixProgram get_random_program();

#endif //!< UNIX_PROGRAM