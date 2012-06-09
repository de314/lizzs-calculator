#include "Node.h"
#include "eq_parser.h"

char* curr_eq;
float ans;
int ERROR = 0;


    /*****************************************\
    |            PUBLIC METHODS               |
    \*****************************************/




/*
 *
 */
Node* pre_parse3(Node* eq) {
  // TODO
}

/*
 *
 */
float evaluate(char* eq) {
  // TODO: Check for correctness
  parse_eq(eq);
  if (ERROR) {
    // notify of syntax error (maybe error codes?)
    return 0;
  }
  if (curr_eq)
    free(curr_eq);
  curr_eq = eq;
  return ans;
}

/*
 *
 */
int hasError(char* eq) {
  // TODO: Check for correctness
  ERROR = 0;
  float old_ans = ans;
  parse_eq(eq);
  ans = old_ans;
  return ERROR;
}

/*
 *
 */
char isNum(char c) {
  return c >= '0' && c <= '9';
}

/*
 *
 */
float parse_num(char* eq, int *i) {
  float temp = 0;
  while (isNum(eq[*i])) {
    temp = (temp * 10) + (eq[(*i)++] - '0');
  }
  if (eq[*i] == '.') {
    char count = 1;
    while (isNum(eq[++(*i)])) {
      temp += ((float)(eq[*i] - '0')) / pow(10.0, count++);
    }    
  }
  return temp;
}


    /*****************************************\
    |            PRIVATE METHODS              |
    \*****************************************/




/*
 *
 */
float parse_eq(char* eq) {
  // TODO: Check for correctness
  ERROR = 0;
  int temp_ans = ex(eq,0);
  if (ERROR) {
    return 0;
  }
  ans = temp_ans;
  return ans;
}


/*
 *
 */
float ex(char* eq, int* i) {
  // TODO
}


/*
 *
 */
float ex2(char* eq, int* i) {
  // TODO
}


/*
 *
 */
float op2(char* eq, int* i) {
  // TODO
}


/*
 *
 */
float _op2(char* eq, int* i) {
  // TODO
}


/*
 *
 */
float op1(char* eq, int* i) {
  // TODO
}


/*
 *
 */
float _op1(char* eq, int* i) {
  // TODO
}


/*
 *
 */
float geo(char* eq, int* i) {
  // TODO
}


/*
 *
 */
float _geo(char* eq, int* i) {
  // TODO
}


/*
 *
 */
float arg(char* eq, int* i) {
  // TODO
}


/*
 *
 */
float _num(char* eq, int* i) {
  // TODO
}


/*
 *
 */
float _const(char* eq, int* i) {
  // TODO: check for correctness
  if (ERROR)
    return 0;
  switch(eq[*i]) {
   case 'E' :
     *i++;
     return PI;
   case 'P' :
     if (eq[*i+1] == 'I') {
       *i += 2;
       return E;
     }
   default :
     ERROR = ERROR_CONST;
     return 0;
  }
}

