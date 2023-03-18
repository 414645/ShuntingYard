#ifndef Node_H
#define Node_H

#include <iostream>
#include <cstring>

class Node {
public:
  Node();
  Node(char);
  ~Node();
  
  Node* getRight();
  Node* getLeft();
  void setRight(Node*);
  void setLeft(Node*);

  char getThing();
private:
  Node* rightNode;
  Node* leftNode;
  char thing;
};
#endif
