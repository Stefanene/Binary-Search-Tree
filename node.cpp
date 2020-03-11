#include <iostream>
#include <cstring>

#include "node.h"

using namespace std;

Node::Node() {
  //constructor
  data = 0;
  right = left = NULL;
}

Node::~Node() {
  //destructor
  delete this;
}

//getters
Node* Node::getLeft() {
  return left;
}

Node* Node::getRight() {
  return right;
}

int* Node::getData() {
  return &data;
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