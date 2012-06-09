

#include "eq_parser.h"

#define BUTTONS_LENGTH 5

int buttons[BUTTONS_LENGTH];
int last_button;

void setup () {6
  Serial.begin(9600);
  
  buttons[0] = 3;
  buttons[1] = 4;
  buttons[2] = 5;
  buttons[3] = 6;
  buttons[4] = 7;
}

void loop() {
  static int count = 0;
  if (Serial.available()) {
    Serial.println("3...");
    delay(1000);
    Serial.println("2...");
    delay(1000);
    Serial.println("1...");
    delay(1000);
    int avail = Serial.available();
    Serial.println(avail);
    char* numStr = (char*)malloc(avail+1);
    for (int i=0;i<avail;i++)
      numStr[i] = Serial.read();
    numStr[avail] = 0;
    for (int i=0;i<avail;i++)
      Serial.print(numStr[i]);
    Serial.println();
    int i = 0;
    numStr = pre_parse1(numStr);
    while(numStr[i])
      Serial.print(numStr[i++]);
    Serial.println();
    numStr = pre_parse2(numStr);
    i=0;
    while(numStr[i])
      Serial.print(numStr[i++]);
    Serial.println();
    free(numStr);
  }
}

int getButtonState() {
  return 0;
}

/*
 *
 */
char* pre_parse(char* eq, char c1, char c2) {
  // FIXME: needs to be evaluated recursively
  int i=0;
  int count = 1;
  while(eq[i]){
    if(eq[i] == c1 || eq[i] == c2 || eq[i] == ')')
      count++;
    i++;
  }
  char* eq_new = (char*)malloc(i+count*2+2);
  i = 0;
  int i2 = 0;
  int mode = 1;
  eq_new[i2++] = '(';
  while(eq[i]){
    if(eq[i] == c1 || eq[i] == c2) {
      eq_new[i2++] = ')';
      eq_new[i2++] = eq[i++];
      eq_new[i2++] = '(';
      mode = 1;
    } if(eq[i] == ')' && mode) {
      eq_new[i2++] = ')';
      eq_new[i2++] = eq[i++];
      mode = 0;
    } else
      eq_new[i2++] = eq[i++];
  }
  eq_new[i2++] = ')';
  eq_new[i2] = 0;
  i2 = 0;
  free(eq);
  return eq_new;
}

/*
 *
 */
char* pre_parse1(char* eq) {
  return pre_parse(eq, '+', '-');
}

/*
 *
 */
char* pre_parse2(char* eq) {
  return pre_parse(eq, '*', '/');
}
