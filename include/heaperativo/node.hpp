#ifndef NODE_HPP
#define NODE_HPP

#include "process.hpp"

/// @brief 
struct Node
{
  Process process;
  Node *next;
};

#endif //!< NODE_HPP