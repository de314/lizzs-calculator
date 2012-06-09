#ifndef EQ_PARSER_h
#define EQ_PARSER_h

#include "Arduino.h"
#include <math.h>

#define ERROR_CONST 0x0001

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

// _CONST
#define PI 3.1415926535
#define E  2.7182818284


// public
Node* pre_parse1(Node* eq);
Node* pre_parse2(Node* eq);
Node* pre_parse3(Node* eq);
float evaluate(char* eq);
int hasError(char* eq);
char isNum(char c);
float parse_num(char* eq, int *i);

// private
Node* pre_parse(Node* eq, char c1, char c2);
float parse_eq(char* eq);
float ex(char* eq, int* i);
float ex2(char* eq, int* i);
float op2(char* eq, int* i);
float _op2(char* eq, int* i);
float op1(char* eq, int* i);
float _op1(char* eq, int* i);
float geo(char* eq, int* i);
float _geo(char* eq, int* i);
float arg(char* eq, int* i);
float _num(char* eq, int* i);
float _const(char* eq, int* i);

#endif
