#ifndef NODE_h
#define NODE_h

#include "Arduino.h"

typedef struct Node {
  char c;
  char match;
  Node *prev;
  Node *next;
} 
Node;

#endif

