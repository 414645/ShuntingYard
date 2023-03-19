#include <iostream>
#include "node.h"

using namespace std;

//shunting yard programm
//Ryan Veith
//I did not want to write another node class so singe lists use the
//right side of node

//printLiner goes though a linked list and cout (right side)
void printLinear (Node* current);

//used for testing since this was coded using the 1 million monkeys stratgy
//delete if have free time to clean up couts
int global = 0;

//Stack (lifo) is built with the idea if it works it works (right path)
void push(Node* &head, Node* current,  Node* newNode);
char pop(Node* &head, Node* current, Node* previous);
char peek(Node* &head, Node* current, Node* previous);
//for binary tree (same as pop but returns a node vs char)
Node* popNode(Node* &head, Node* current, Node* previous);
//Queue (fifo) same idea
void enque(Node* &head, Node* current,  Node* newNode);
char deque(Node* &head, Node* current, Node* previous);

int main() {
  //cout << "hello world" << endl;
  //using the same node class as said above
  Node* stackOne = NULL;
  Node* queueOne = NULL;

  cout << "Input a mathematical expresion" << endl;
  cout << "Only use single diget integers, +, -, *, /, ^ (, and )." << endl;
  cout << "enter S when done to start the shunting yard program" << endl;
  
  //until we get a invalid input let the user add numbers
  //cin breaks on spaces so it is easy
  bool quit = false;
  while(quit == false) {
    char temp = ' ';
    cin >> temp;
    //only take in operators + numbers
    //yes I realize in retrospect that
    //if temp == '+' would have been easier
    if((int)temp == 43 || //+
       (int)temp == 45 || //-
       (int)temp == 42 || //*
       (int)temp == 47 || ///
       (int)temp == 94 || //^
       (int)temp == 40 || //(
       (int)temp == 41 || //)
       ((int)temp > 47 && (int)temp < 58)) { //num
      Node* nodify = new Node(temp);
      //SHUNTING YARD ALGORITHEM STARTS HERE

      //if its a number
      if ((int)temp > 47 && (int)temp < 58) {
	cout << "number -> queue" << endl;
	//it goes straight to the queue
        enque(queueOne, queueOne, nodify);
      }
      //if its an operation
      else {
	//start a loop until we have handeled the operation
	bool tempthing = true;
	while(tempthing == true) {
	  //if it is a  ( it goes straight to stack
	  if (temp == '(') {
	    push(stackOne, stackOne, nodify);
	    //we have handled it
	    tempthing = false;
	  }
	  //if it is a ) get rid of stack to queue until ( then delte (
	  if (temp == ')') {
	    cout << "not done yet" << endl;
	    bool endless = true;
	    while(endless == true) {
	      if (peek(stackOne, stackOne, NULL) != '(') {
		//if it is not ( send it to queue
		//names are a little wierd since I don't know what to
		//call them since temp is used aready
		char uniqueName = pop(stackOne, stackOne, NULL);
		Node* newNodeNumberQuestionMark = new Node(uniqueName);
		enque(queueOne, queueOne, newNodeNumberQuestionMark);
	      }
	      else {
		//get rid of ( and exit while
		pop(stackOne, stackOne, NULL);
		endless = false;
	      }
	    }
	    //we have handeled it
	    tempthing = false;
	  }
	  
	  //find the precidence of operators
	  int precidence = 0;
	  int myPre;
	  char pre = peek(stackOne, stackOne, NULL);
	  if (pre == '(') {
	    precidence = 4;
	  }
	  if (pre == '^') {
	    precidence = 3;
	  }
	  if (pre == '*' || pre == '/') {
	    precidence = 2;
	  }
	  if (pre == '+' || pre == '-' ) {
	    precidence = 1;
	  }
	  if (temp == '^') {
	    myPre = 3;
	  }
	  if (temp == '*' || pre == '/') {
	    myPre = 2;
	  }
	  if (temp == '+' || pre == '-' ) {
	    myPre = 1;
	  }
	  //if myprecidence is smaller then the thing is stack
	  cout << "myPree:" << myPre << "  pre:" << precidence << endl;
	  if (myPre <= precidence) {
	    //get move the top thing in the stack to the queue

	    char thing = pop(stackOne, stackOne, NULL);
	    //cout << "thing: " << thing << endl;
	    Node* newNode = new Node(thing);
	    //cout << "newNode: " << newNode << endl;
	    enque(queueOne, queueOne, newNode);
	    //cout << "enqued newnode" << endl;
	    
	  }
	  else {
	    //add me to stack
	    cout << "add to stack" << endl;
	    push(stackOne, stackOne, nodify);
	    //and we have handeled the operation
	    tempthing = false;
	  }
	}
      }
      
    }
    else if (temp == ' ') {
      quit = true;
      //never happens since cin breaks on spaces
    }
    else {
      quit = true;
    }
  }
  //shunting yard is almost done
  //now the rest of the stack needs to go to the queue

  //some prints to make sure it was working correctly
  /*
  cout << "stack1" << endl;
  printLinear(stackOne);
  cout << "qeueue1" << endl;
  printLinear(queueOne);
  */

  //loop until stack1 head = null
  bool whileLoop = true;
  while (whileLoop == true) {
    //if it is not empty move
    if (peek(stackOne, stackOne, NULL) != ' ') {
      //move the top thing in the stack to the queue
      
      char thing = pop(stackOne, stackOne, NULL);
      //cout << "thing: " << thing << endl;
      Node* newNode = new Node(thing);
      //cout << "newNode: " << newNode << endl;
      enque(queueOne, queueOne, newNode);
      //cout << "enqued newnode" << endl;
	    
    }
    else {
      //we are done
      whileLoop = false;
    }
  }
  //shuntingyard is officialy done!
  //Now move the queue to a binary tree
  cout << "stack1" << endl;
  printLinear(stackOne);
  cout << "qeueue1" << endl;
  printLinear(queueOne);

  //to turn postfix into a binary tree
  //move the queue into a stack and anytime an operator is added it is the
  //root of a "tree" and then the root is added to the stack

  //storage of things until they go into tree
  //it will store nodes istead of chars since it needs to be able to
  //store the roots of smaller trees
  //the final one will be asigned to tree
  //since it is then the root of all trees
  Node* stackTwo = NULL;
  //tree
  Node* tree = NULL;

  //while loop to go though queue
  bool time = true;
  while (time == true) {
    char b = deque(queueOne, queueOne, NULL);
    cout << "b: " << b << endl;
    if (b != ' ') {
      //we are still in the queue
      //so check if its  a number
      if ((int)b > 47 && (int)b < 58) {
	//make it into a node
	Node* newNode = new Node(b);
	//create a node(for the stack)  holding that node (for the tree)
	Node* nodeNew = new Node(newNode);
	//add it to stack2 (since this will be a
	//part of a the tree we want nodes not chars
	push(stackTwo, stackTwo, nodeNew);
      }
      else {
	//pop node twice and shove root back into stack
	//for a,b. b is first pop as is second since fifo
	Node* bNode = popNode(stackTwo, stackTwo, NULL);
	Node* aNode = popNode(stackTwo, stackTwo, NULL);
	//my creatvity for names is horrible
	//anyways the operator is the root of two numbers in binary tree
	//so this does that

	//(a or b could be a function too)
	//so node was rewored to be able to hold a node too
	//and getNode get that node so we now have the fuciton as a or b
	Node* op = new Node(b);
        op->setRight(bNode);
	op->setLeft(aNode);
	cout << "operator: " << op->getThing() << endl;

	//ifs since the tree doens not necairly have two children
	if (op->getRight() != NULL) {
	  cout << "right: " << op->getRight()->getNode() << endl;
	}
	if (op->getLeft() != NULL) {
	  cout << "left: " << op->getLeft()->getNode() << endl;
	}
      }
      
      
    }
    else {
      //we are done with the list
      time = false;

      //couts for testing
      cout << "hi" << endl;
      //tree = popNode(stackTwo, stackTwo, NULL);
      //cout << "root: " << tree->getThing() << endl;
    }
  }

  //ask what way they want to cout notation
  cout << "Would you like to output the expresision as:" << endl;
  cout << "1 infix" << endl;
  cout << "2 prefix" << endl;
  cout << "3 postfix" << endl;
  
  
  
}
void printLinear (Node* current) {
  if (current != NULL) {
    //cout << current << endl;
    cout << " :" << current->getThing() << endl;
    printLinear(current->getRight());
  }
  else {
    //cout << "current = null" << endl;
  }
}

//stack
void push(Node* &head, Node* current, Node* newNode) {
  //an exit so ^c is not needed if something goes
  //wrong with input that is not caught in the if
  //this should not be possible but... yeah
  //1*10^6 monkey's and inf time = shake spear
  if (current == newNode) {
    cout << "There was an unexped error, ";
    cout << "please check that your input was correct" << endl;
    exit(1);
  }

  //normal stack code
  //if head is null relace it
  //otherwise go throught until next is NULL and make next me
  if (head == NULL) {
    head = newNode;
    //should be null aready but does not hurt to make sure
    newNode->setRight(NULL);
  }
  else if (current->getRight() == NULL) {
    //this if was added since I managed to mess up shuntingyard so much
    //that it would send the same node twice somehow
    //agian milion monkey and typwriters
    if (current != newNode) {
      //if the next node is null make the next node me:
      current->setRight(newNode);
    }
    //bug testing not needed (global variable definily not needed)
    cout << current << ", " << current->getRight() << endl;
    cout << "printstack" << endl;
    if (global < 1) {
      printLinear(head);
    }
    else {
      cout << "noprint" << endl;
    }
    //if (global > -1) {
    //exit(1);
    //}
    global++;

    //end of not needed
  }
  else {
    //recursion to go though the list
    push(head, current->getRight(), newNode);
  }
}

//return the value of last thing in the stack (+ delete it)
char pop(Node* &head, Node* current, Node* previous) {
  //if it is empty return ' '
  if (head == NULL) {
    return ' ';
  }
  else if (head->getRight() == NULL) {
    //if the head is only thing in list
    //save the thing to return as int
    int a = head->getThing();
    delete current;
    head = NULL;
    return a;
  }
  //if we are at the end of the list
  else if (current->getRight() == NULL) {
    //save the thing to retun as int
    int a = current->getThing();
    //set previous to point to NULL
    if (previous != NULL) {
      previous->setRight(NULL);
      cout << "!!!" << endl;
    }
    else {
      //printLinear(head);
    }

    //delete the current node and return
    cout << "delete current pop" << endl;
    delete current;
    return a;
  }
  else {
    //go though the list since we are not at the end
    return pop(head, current->getRight(), current);
  }
}

char peek(Node* &head, Node* current, Node* previous) {
  if (head == NULL) {
    return ' ';
  }
  else if (current->getRight() == NULL) {
    return current->getThing();
    if (previous == NULL) {
      cout <<  "this should be an impossible situation";
    }
    //previous->setRight(NULL);
  }
  else {
    return peek(head, current->getRight(), current);
  }
}

//queue
void enque(Node* &head, Node* current,  Node* newNode) {
  if (head == NULL) {
    head = newNode;
  }
  else if (current->getRight() == NULL) {
    //if the next node is NULL make the next node me
    current->setRight(newNode);

    //prints so I can see what is happening
    //cout << "print queue" << endl;
    //printLinear(head);
  }
  else {
    push(head, current->getRight(), newNode);
  }
}

char deque(Node* &head, Node* current, Node* previous) {
  if (head == NULL) {
    //if there is nothing return ' '
    return ' ';
  }
  else {
    //otherwise save thing to return and overwrite head
    char temp = head->getThing();
    head = head->getRight();
    return temp;
  }
}

						     
//stack but nodes
//this is the exact code as pop but using a node as return insead of char
Node* popNode(Node* &head, Node* current, Node* previous) {
  //if it is empty return ' '
  if (head == NULL) {
    return NULL;
  }
  else if (head->getRight() == NULL) {
    Node* a = head->getNode();
    delete current;
    head = NULL;
    return a;
  }
  else if (current->getRight() == NULL) {
    Node* a = current->getNode();
    if (previous != NULL) {
      previous->setRight(NULL);
    }
    delete current;
    return a;
  }
  else {
    return popNode(head, current->getRight(), current);
  }
}

/*
Node* popNode(Node* &head, Node* current, Node* previous) {
  //if it is empty return ' '
  if (head == NULL) {
    //NULL not ' '
    return NULL;
  }
  else if (head->getRight() == NULL) {
    //no needto save head = current at this point
    head = NULL;
    return current;
  }
  //if we are at the end of the list
  else if (current->getRight() == NULL) {
    //exact code as above -cout
    if (previous != NULL) {
      previous->setRight(NULL);
    }
    else {
      //printLinear(head);
    }

    //return insead of deleting
    return current;
  }
  else {
    //go though the list since we are not at the end
    return popNode(head, current->getRight(), current);
  }
}
*/
