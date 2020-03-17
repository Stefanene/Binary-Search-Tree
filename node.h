#ifndef NODE_H
#define NODE_H

using namespace std;

class Node {
 public:
  Node();
  ~Node();
  //getters
  Node* getLeft();
  Node* getRight();
  int getData();
  //setters
  void setLeft(Node*);
  void setRight(Node*);
  void setData(int);
 private:
  int data;
  Node* left;
  Node* right;
};
#endif
