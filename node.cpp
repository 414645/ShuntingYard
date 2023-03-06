#include <iostream>
#include "node.h"

using namespace std;

Node::Node() {
  cout << "blank node created" << endl;
}

Node::Node(char newThing) {
  cout << newThing << " node created" << endl;
}
/*
Node::~Node() {
  cout << "node destroyed" << endl;
}
*/
