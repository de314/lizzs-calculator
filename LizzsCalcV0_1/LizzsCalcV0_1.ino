#include "Node.h"
#include "eq_parser.h"

#define BUTTONS_LENGTH 5

int buttons[BUTTONS_LENGTH];
int last_button;

void setup () {
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
    char* numStr = (char*)malloc(avail+1);
    for (int i=0;i<avail;i++)
      numStr[i] = Serial.read();
    numStr[avail] = 0;
    Node* eq = generateList(numStr);
    printList(eq);
    free(numStr);
    eq = pre_parse1(eq);
    printList(eq);
    eq = pre_parse2(eq);
    printList(eq);
    freeList(eq);
  }
}

void freeList(Node* probe) {
  Node* next;
  while(probe) {
    next = probe->next;
    free(probe);
    probe = next;
  }
}

void printList(Node* probe) {
  while(probe) {
    Serial.print(probe->c);
    probe = probe->next;
  }
  Serial.println();
}

Node* generateList(char* eq) {
  Node* head = (Node*)malloc(sizeof(Node));
  head->c = eq[0];
  head->prev = 0;
  head->next = 0;
  Node* probe = head;
  for (int i=1;eq[i];i++) {
    probe->next = (Node*)malloc(sizeof(Node));
    probe->next->prev = probe;
    probe->next->next = 0;
    probe->next->c = eq[i];
    probe = probe->next;
  }
  return head;
}

int getButtonState() {
  return 0;
}

/*
 *
 */
Node* pre_parse(Node* eq, char c1, char c2) {
  Node* probe = eq;
  Node* ip = eq;
  while (probe && probe->next) {
    if (probe->c == c1 || probe->c == c2) {
      surround(ip, probe);
      if (ip == eq && ip->prev)
        eq = ip->prev;
      ip = probe->next;
    }
    if (probe->c == '(')
      probe = pre_parse(probe->next, c1, c2);
    else if(probe->c == ')') {
      surround(ip, probe);
      return probe->next;
    } 
    else
      probe = probe->next;
  }
  if (!probe)
    return eq;
  if (!eq->prev) {
    if (ip != eq) {
      insertBefore(ip, '(');
      if (ip == eq && ip->prev)
        eq = ip->prev;
      Node* temp = new Node();
      temp->prev = probe;
      temp->c = ')';
      probe->next = temp;
    }
    return eq;
  }
  if (ip != eq)
    surround(ip, probe);
  return probe->next;
}

char validateParentheses(Node* probe) {
  Node arr[10];
  int count = 0;
  int curr = 0;
  while (probe) {
    if (probe->c == '(')
      arr[curr++] = probe;
    else if(probe->c == ')') {
      arr[--curr]->match = count;
      probe->match = count++;
    }
    probe = probe->next;
  }
  return count == 0;
}

void surround(Node* ip, Node* probe) {
  if ((ip->prev && ip->prev->c != '(' && ip->c != '(') || (probe->c != ')' && probe->prev->c != ')')) {
    // insert left side
    insertBefore(ip, '(');
    // insert right side
    insertBefore(probe, ')');
  }
}

void insertBefore(Node* curr, char c) {
  Node* temp = (Node*)malloc(sizeof(Node));
  if (curr->prev)
    curr->prev->next = temp;
  temp->next = curr;
  temp->prev = curr->prev;
  curr->prev = temp;
  temp->c = c;
}

/*
 *
 */
Node* pre_parse1(Node* eq) {
  return pre_parse(eq, '+', '-');
}

/*
 *
 */
Node* pre_parse2(Node* eq) {
  return pre_parse(eq, '*', '/');
}



