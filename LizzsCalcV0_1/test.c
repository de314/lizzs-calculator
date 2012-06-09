/*
#include "eq_parser.h"
#include "Arduino.h"

void test_number_parser() {
  static int count = 0;
  if (Serial.available()) {
    delay(10);
    int avail = Serial.available();
    Serial.println(avail);
    char* numStr = (char*)malloc(avail+1);
    for (int i=0;i<avail;i++)
      numStr[i] = Serial.read();
    numStr[avail] = 0;
    Serial.print("\nNumber ");
    Serial.print("Available: ");
    Serial.println(count++, DEC);
    for (int i=0;i<avail;i++)
      Serial.print(numStr[i]);
    Serial.println();
    Serial.println(isNum(numStr[0]) ? "true" : "false");
    int i = 0;
    float num = parse_num(numStr, &i);
    Serial.print("Final Answer: ");
    Serial.println(num);
    Serial.print("Final Index: ");
    Serial.println(i);
    free(numStr);
  }
}
*/
