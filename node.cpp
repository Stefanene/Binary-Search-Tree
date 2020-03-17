#include <iostream>
#include <cstring>

#include "node.h"

using namespace std;

Node::Node() {
  //constructor
  data = 0;
  left = NULL;
  right = NULL;
}

Node::~Node() {
  //destructor
  //delete &data;
  left = NULL;
  right = NULL;
}

//getters
Node* Node::getLeft() {
  return left;
}

Node* Node::getRight() {
  return right;
}

int Node::getData() {
  return data;
}

//setters
void Node::setLeft(Node* newL) {
  left = newL;
}

void Node::setRight(Node* newR) {
  right = newR;
}

void Node::setData(int newD) {
  data = newD;
}
