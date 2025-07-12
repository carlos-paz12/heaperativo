#ifndef UNIX_PROGRAM
#define UNIX_PROGRAM

/**
 *
 * Enum para representar programas Unix
 *
 */
enum unix_program {
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
const char *get_program_name(unix_program program);

/**
 *
 * Função que pega um UnixProgram aleatoriamente
 *
 */
unix_program get_random_program();

#endif //!< UNIX_PROGRAM