#include <iostream>
#include "node.h"

using namespace std;

//shunting yard programm
//Ryan Veith

void printLinear (Node* current);

//Stack (lifo) is built with the idea if it works it works
void push(Node* &head, Node* current,  Node* newNode);
char pop();
char peek();

int main() {
  cout << "hello world" << endl;
  //using the same node class for all since I don't want to create anohter
  Node* stackOne = NULL;


  //Node* a = new Node('1');
  //push(stackOne, stackOne, a);
  //printLinear(stackOne);

  cout << "Input a mathematical expresion" << endl;
  cout << "Only use single diget integers, +, -, *, /, ^ (, and )." << endl;
  char a = ')';
  cout << "a:" << (int)a << endl;;
  bool quit = false;
  while(quit == false) {
    char temp = ' ';
    cin >> temp;
    if((int)temp == 43 || //+
       (int)temp == 45 || //-
       (int)temp == 42 || //*
       (int)temp == 47 || ///
       (int)temp == 94 || //^
       (int)temp == 40 || //(
       (int)temp == 41) { //)
      Node* nodify = new Node(temp);
      push(stackOne, stackOne, nodify);
      printLinear(stackOne);
    }
    else if (temp == ' ') {
      quit = true;
      cout << "done" << endl;
    }
  }

}
void printLinear (Node* current) {
  if (current != NULL) {
    //cout << current << endl;
    cout << " :" << current->getThing() << endl;
    printLinear(current->getRight());
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
