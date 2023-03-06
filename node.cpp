#include <iostream>
#include "node.h"

using namespace std;

Node::Node() {
  cout << "blank node created" << endl;
  rightNode = NULL;
  leftNode = NULL;
  thing = '0';
}

Node::Node(char newThing) {
  cout << newThing << " node created" << endl;
  rightNode = NULL;
  leftNode = NULL;
  thing = newThing;
}

Node::~Node() {
  cout << "node destroyed" << endl;
}
Node* Node::getRight() {
  return rightNode;
}
Node* Node::getLeft() {
  return leftNode;
}
void Node::setRight(Node* newRight) {
  rightNode = newRight;
}
void Node::setLeft(Node* newLeft) {
  leftNode = newLeft;
}
char Node::getThing() {
  return thing;
}


