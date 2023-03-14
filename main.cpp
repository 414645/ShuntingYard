#include <iostream>
#include "node.h"

using namespace std;

//shunting yard programm
//Ryan Veith

void printLinear (Node* current);

//Stack (lifo) is built with the idea if it works it works (right path)
void push(Node* &head, Node* current,  Node* newNode);
char pop(Node* &head, Node* current, Node* previous);
char peek(Node* &head, Node* current, Node* previous);
//Queue (fifo) same idea
void enque(Node* &head, Node* current,  Node* newNode);
char deque(Node* &head, Node* current, Node* previous);

int main() {
  cout << "hello world" << endl;
  //using the same node class for all since I don't want to create another
  Node* stackOne = NULL;
  Node* queueOne = NULL;


  cout << "Input a mathematical expresion" << endl;
  cout << "Only use single diget integers, +, -, *, /, ^ (, and )." << endl;

  //until we get a invalid input let the user add numbers
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
       (int)temp == 41 || //)
      ((int)temp > 47 && (int)temp < 58)) { //num
      Node* nodify = new Node(temp);
      //SHUNTING YARD ALGORITHEM HERE
      //if its a number
      if ((int)temp > 47 && (int)temp < 58) {
	push(stackOne, stackOne, nodify);
      }
      //if its an operation
      else {
	
      }
      //enque(stackOne, stackOne, nodify);
    }
    else if (temp == ' ') {
      quit = true;
      //never happens since cin breaks on spaces
    }
    else {
      quit = true;
    }
  }
  cout << "done" << endl;
  cout << "stack1" << endl;
  printLinear(stackOne);
  cout << "qeueue1" << endl;
  printLinear(queueOne);
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

//stack
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

char pop(Node* &head, Node* current, Node* previous) {
  if (head == NULL) {
    return ' ';
  }
  else if (current->getRight() == NULL) {
    return current->getThing();
    previous->setRight(NULL);
    delete current;
  }
  else {
    return pop(head, current->getRight(), current);
  }
}

char peek(Node* &head, Node* current, Node* previous) {
  if (head == NULL) {
    return ' ';
  }
  else if (current->getRight() == NULL) {
    return current->getThing();
    //previous->setRight(NULL);
  }
  else {
    return pop(head, current->getRight(), current);
  }
}

//queue

void enque(Node* &head, Node* current,  Node* newNode) {
  if (head == NULL) {
    head = newNode;
  }
  else {
    newNode->setRight(current);
    head = newNode;
  }
}

char deque(Node* &head, Node* current, Node* previous) {
    if (head == NULL) {
    return ' ';
  }
  else {
    return head->getThing();
    head = head->getRight();
    delete head;
  }
}

						     
