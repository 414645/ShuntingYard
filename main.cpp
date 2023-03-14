#include <iostream>
#include "node.h"

using namespace std;

//shunting yard programm
//Ryan Veith

void printLinear (Node* current, Node* newNode);

//Stack (lifo) is built with the idea if it works it works
void push(Node* &head, Node* current,  Node* newNode);
char pop();
char peek();

int main() {
  cout << "hello world" << endl;
  Node* stackOne = NULL;
  //cout >> stackOne->getThing() >> endl;
  Node* a = new Node('1');
  push(stackOne, stackOne, a);
  printLinear(stackOne, a);

}
void printLinear (Node* current, Node* newNode) {
  if (current != NULL) {
    //cout << current << endl;
    cout << " :" << current->getThing() << endl;
  }
    else {
      cout << "current = null" << endl;
    }
}

void push(Node* &head, Node* current, Node* newNode) {
  if (head == NULL) {
    head = newNode;
  }
  else if (current->getRight() == NULL) {
    current->setRight(newNode);
  }
  else {
    push(head, current->getRight(), newNode);
  }
}

char pop() {
  return 'a';
}

char peek() {
  return 'a';
}
