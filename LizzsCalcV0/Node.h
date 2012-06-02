#ifndef NODE_h
#define NODE_h

#include "Arduino.h"

typedef struct Node {
	char state;
	data *big_double;
	Node *child;
	Node *next;
} Node;

#endif
