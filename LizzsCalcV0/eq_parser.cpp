#ifndef EQ_PARSER_h
#define EQ_PARSER_h

#include "Arduino.h"

#define EX     0
#define EX2    1
#define OP2    2
#define _OP2   3
#define OP1    4
#define _OP1   5
#define GEO    6
#define _GEO   7
#define ARG    8
#define NUM    9
#define CONST  10

// _OP2
#define ADD  0
#define SUB  1
#define MULT 2
#define DIV  3
#define EXP  4

// _OP1
#define LG   0
#define LN   1
#define SQRT 2

// _GEO
#define ARC -
#define SIN 0
#define COS 1
#define TAN 2

char* curr_eq;
// Node* curr_tree;
// big_double ans;

int ERROR = 0;



// private
char* pre_parse(char* eq, char c1, char c2) {
  int i=0;
  int count = 0;
  int state = 0;
  while(eq[i]){
    if(eq[i] == c1 || eq[i++] == c2)
      count++;
  }
  char* eq_new = (char*)malloc(i+count*1+2);
  i = 0;
  int i2 = 0;
  while(eq[i]){
    if(eq[i] == c1 || eq[i] == c2) {
      eq_new[i2++] = ')';
      eq_new[i2++] = eq[i++];
      eq_new[i2++] = '(';
    } else
      eq_new[i2++] = eq[i++];
  }
  eq_new[i2++] = ')';
  eq_new[i2] = 0;
  free(eq);
  return eq_new;  
}

// public
char* pre_parse1(char* eq) {
  return pre_parse(eq, '+', '-');
}

// public
char* pre_parse2(char* eq) {
  return pre_parse(eq, '*', '/');
}

// public
char* pre_parse3(char* eq) {
  
}

/*
// public
big_double evaluate(char* eq) {
  Node* tree = parse_eq(eq);
  if (error) {
    // notify of syntax error (maybe error codes?)
    return 0;
  }
  if (curr_tree)
    free(curr_tree);
  curr_tree = tree;
  if (curr_eq)
    free(curr_eq);
  curr_eq = eq;
  process_tree();
  return ans;
}
*/

// public
int hasError(char* eq) {
  //parse_eq(eq);
  return ERROR;
}

/*
// private
Node* parse_eq(char* eq) {
  ERROR = 0;
  Node* root = (char*)malloc(sizeof(Node));
  ex(eq,0,root);
  if (ERROR) {
    free(root);
    return 0;
  }
  return root;
}

// private
void process_tree() {
  // TODO: remember to set ans
}

// private
int ex(char* eq, int i, Node* curr) {
  
}

// private
int ex2(char* eq, int i, Node* curr) {
  
}

// private
int op2(char* eq, int i, Node* curr) {
  
}

// private
int _op2(char* eq, int i, Node* curr) {
  
}

// private
int op1(char* eq, int i, Node* curr) {
  
}

// private
int _op1(char* eq, int i, Node* curr) {
  
}

// private
int geo(char* eq, int i, Node* curr) {
  
}

// private
int _geo(char* eq, int i, Node* curr) {
  
}

// private
int arg(char* eq, int i, Node* curr) {
  
}

// private
int num(char* eq, int i, Node* curr) {
  
}

// private
int const(char* eq, int i, Node* curr) {
  if (ERROR)
    return i;
  switch(eq[i]) {
   case 'E' :
     curr->data = E;
     return i+1;
   case 'P' :
     if (eq[i+1] == 'I') {
       curr->data = E;
       return i+2;
     }
   default :
     ERROR = ERROR_CONST;
     return i;
  }
}
*/

#endif
