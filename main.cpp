/* Binary Search by Stefan Ene
   Works Cited:
     Reused input and parse method from my previous Heap code
     Visual tree printing from //www.techiedelight.com/c-program-print-binary-tree/
       ^ includes Trunk struct and showTrunk function
     Remove function references from www.geeksforgeeks.org/binary-search-tree-set-2-delete/
*/

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>

#include "node.h"

using namespace std;

//struct Trunk for print method
struct Trunk {
  Trunk *prev;
  char* str;

  Trunk(Trunk *prev, char* str) {
    this -> prev = prev;
    this -> str = str;
  }
};

void showTrunks(Trunk *p) {//helper method for printing
  if (p == NULL)
    return;

  showTrunks(p -> prev);

  cout << p -> str;
}

//functions
void parse(char* in, int* modif, int &count);
void insert(Node* &head, Node* &curr, Node* &prev, int val);
void printTree(Node* root, Trunk *prev, bool isLeft);
Node* search (Node* curr, int val);
Node* remove (Node* &root, int k);

int main() {
  //variables
  char inp[10];
  char fileName[30];
  char input[10000];
  int count = 0;  //number of chars
  int modif[100];
  int siz = 0; //for modif array size
  for (int i = 0; i < 100; i++) {
    modif[i] = 0;  //clear int array
  }
  //program
  cout << "=========================" << endl;
  cout << "Welcome to my Binary Search Tree program." << endl;
  bool run = true;
  while (run) {
    for (int c = 0; c < 100; c++) {
      modif[c] = 0; //clear array
    }
    count = 0;  //clear array size index
    cout << endl << "You can: tree, quit." << endl;
    cin.get(inp, 10);
    cin.clear();
    cin.ignore(10000, '\n');
    if (strcmp(inp, "tree") == 0) {
      cout << "=========Entered========" << endl;
      cout << "How would you like to input? file or type:" << endl;
      cin.get(inp, 10);
      cin.clear();
      cin.ignore(10000, '\n');
      bool tr = false;
      if (strcmp(inp, "file") == 0) {
	tr = true;
	//Credit Omar Nassar's Heap project for file input code
	cout << endl << "What is the name of the file?" << endl << ">> ";
	cin.get(fileName, 30);
	cin.clear();
	cin.ignore(100000, '\n');
	streampos size;
	ifstream file(fileName, ios::in | ios::binary | ios::ate);
	if (file.is_open()) {
	  size = file.tellg();
	  file.seekg(0, ios::beg);
	  file.read(input, size);
	  file.close();
	  parse(input, modif, count);  //parse input to modif array
	  cout << "IN: ";
	  for (int i = 0; i < 100; i++) {
	    if (modif[i] == 0) break;
	    cout << modif[i] << " ";
	  }
	  cout << endl;
	}
      }
      else if (strcmp(inp, "type") == 0) {
	tr = true;
	cout << "Enter numbers separated by space:" << endl;
	char in[10000];
	cin.get(in, 10000);
	cin.clear();
	cin.ignore(1000000, '\n');
	//parse input by spaces
	parse(in, modif, count);  //parse input to modif array
	cout << ">> IN: ";
	for (int i = 0; i < 100; i++) {
	  if (modif[i] == 0) break;
	  cout << modif[i] << " ";
	  siz++;
	}
	cout << endl << " Size: " << siz << endl;      
      }
      else {
	tr = false;
	cout << "No such input method. Try again." << endl;
      }
      if (tr) {
	//create tree
	Node* head = NULL;  //tree root
	Node* curr = NULL;  //current node
	Node* prev = NULL;  //previous node
	for (int i = 0; i < siz; i++) {
	  curr = head;
	  insert(head, curr, prev, modif[i]);
	  cout << modif[i] << endl;
	}
	cout << "========Tree=Built=======" << endl;
	// print constructed binary tree
	cout << endl;
	printTree(head, NULL, false);
	cout << endl;
	cout << "======Work=in=Tree=======" << endl;
	bool r = true;
	char resp[10];
	while (r) {
	  cout << endl << "You can: search, add, remove, or done:" << endl;
	  cin.get(resp, 10);
	  cin.clear();
	  cin.ignore(10000, '\n');
	  if (strcmp(resp, "search") == 0) {
	    int val;
	    cout << ">Search value: ";
	    cin >> val;
	    cin.clear();
	    cin.ignore(10000, '\n');
	    Node* temp = search(head, val);
	    if (temp != NULL) {
	      cout << endl << val << " is part of the tree." << endl;
	    } else {
	      cout << endl << val << " is NOT in the tree." << endl;
	    }
	  } else if (strcmp(resp, "remove") == 0) {
	    int val;
	    cout << ">Remove value: ";
	    cin >> val;
	    cin.clear();
	    cin.ignore(10000, '\n');
	    head = remove(head, val);
	    cout << endl << val << " has been removed:" << endl;
	    cout << endl;
	    printTree(head, NULL, false);
	    cout << endl;
	  } else if (strcmp(resp, "add") == 0) {
	    int val;
	    cout << ">Add value: ";
	    cin >> val;
	    cin.clear();
	    cin.ignore(10000, '\n');
	    Node* curr = head;
	    Node* prev = NULL;
	    insert(head, curr, prev, val);
	    cout << endl << val << " has been added:" << endl;
	    cout << endl;
	    printTree(head, NULL, false);
	    cout << endl;
	  } else if (strcmp(resp, "done") == 0) {
	    cout << "=========================" << endl;
	    cout << "Discarded current tree." << endl;
	    r = false;
	    cout << "=========================" << endl;
	  } else {
	    cout << endl << "Invalid operation. Try again." << endl;
	  }
	}
      }
    }
    else if (strcmp(inp, "quit") == 0) {
      cout << endl << "Thank you for using my program!" << endl;
      cout << "=========================" << endl;
      run = false;
    }
    else {
      cout << endl << "Invalid input. Try again." << endl;
    }
  }
  return 0;
}

void parse(char* in, int* modif, int &count) {
  int l = 0;  //keeps track of # of chars before space
  for (int i = 0; i < strlen(in); i++) {
    if (in[i] == ' ') {
      if (l == 1) {
	int temp = 0;
	temp = in[i-1] - '0';
	modif[count] = temp;
	count++;
	l = 0;
      } else {
	int temp = 0;
	for (int a = 0; a < l; a++) {
	  temp = 10 * temp + (in[i-l+a] - '0');
	}
	modif[count] = temp;
	count++;
	l = 0;
      }
    } else {
      int temp = 0;
      l++;
      if (i == strlen(in) - 1) {  //last possible pair of chars
	for (int a = 0; a < l; a++) {
	  temp = 10 * temp + (in[i+a+1-l] - '0');
	}
	modif[count] = temp;
	count++;
      }
    }
  } 
}

//insert function adds nodes with values recursively to tree
void insert(Node* &head, Node* &curr, Node*& prev, int val) {
  if (head == NULL) {
    head = new Node();
    head->setData(val);
  } else {
    if (val <= *curr->getData()) {  //lower goes left
      prev = curr;
      curr = curr->getLeft();
      if (curr == NULL) {  //if empty then insert
	curr = new Node();
	curr->setData(val);
	prev->setLeft(curr);
      } else {  //if !empty then keep going
	insert(head, curr, prev, val);
      }
    }
    else {
      prev = curr;
      curr = curr->getRight();  //higer goes right
      if (curr == NULL) {  //if empty then inset
	curr = new Node();
	curr->setData(val);
	prev->setRight(curr);
      } else {  //if !empty then keep going
	insert(head, curr, prev, val);
      }
    }
  }
}


//print functions with help from //www.techiedelight.com/c-program-print-binary-tree
void printTree(Node* root, Trunk *prev, bool isLeft) {
  if (root == NULL) {
    return;
  }
  char* prev_str = (char*)("    ");
  Trunk *trunk = new Trunk(prev, prev_str);
  printTree(root->getLeft(), trunk, true);
  if (!prev) {
    trunk -> str = (char*)("---");
  }
  else if (isLeft) {
    trunk -> str = (char*)(".---");
    prev_str = (char*)("   |");
  }
  else {
    trunk -> str = (char*)("`---");
    prev -> str = prev_str;
  }
  showTrunks(trunk);
  cout << *root->getData() << endl;

  if (prev) {
    prev -> str = prev_str;
  }
  trunk -> str = (char*)("   |");
  printTree(root->getRight(), trunk, false);
}

//search function returns node with inputted value
Node* search(Node* curr, int val) {
  if (val == *curr->getData()) {
    return curr;
  }
  else if (val < *curr->getData()) {  //lower goes left
    if (curr->getLeft() != NULL) {
      search(curr->getLeft(), val);  //recursion
    } else {
      return NULL;  //no lower node
    }
  } else {  //higher goes right
    if (curr->getRight() != NULL) {
      search(curr->getRight(), val);  //resursion
    } else {
      return NULL;  //no higher node
    }
  } 
}

//remove function with help from //www.geeksforgeeks.org/binary-search-tree-set-2-delete/
Node* remove(Node* &root, int k) {  
  if (root == NULL) {  //base case
    return root; 
  }
  //recursive calls
  if (*root->getData() > k) {
    Node* l = root->getLeft();
    root->setLeft(remove(l, k)); 
    return root; 
  } 
  else if (*root->getData() < k) {
    Node* r = root->getRight();
    root->setRight(remove(r, k)); 
    return root; 
  }
  //if one child is empty
  if (root->getLeft() == NULL) {  //left null, go right
    Node* temp = root->getRight(); 
    root->~Node();  //delete root
    root = NULL;
    return temp; 
  } 
  else if (root->getRight() == NULL) {  //right null, go left
    Node* temp = root->getLeft(); 
    root->~Node();  //delete root
    root = NULL;
    return temp; 
  } 
  //if both children exist 
  else { 
    Node* succParent = root->getRight(); 
    
    // Find successor 
    Node *succ = root->getRight(); 
    while (succ->getLeft() != NULL) { 
      succParent = succ; 
      succ = succ->getLeft(); 
    } 
    
    //successors right child becomes parent's left child 
    succParent->setLeft(succ->getRight()); 
    
    //copy successor data to root 
    root->setData(*succ->getData()); 
    
    //delete Successor and return root
    succ->~Node();
    succ = NULL;
    return root; 
  } 
} 
