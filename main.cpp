/* Binary Search by Stefan Ene
   Works Cited:
     Reused input and parse method from my previous Heap code
     Binarty insertion from http://www.cplusplus.com/forum/general/166384/
     BTS print: https://www.techiedelight.com/c-program-print-binary-tree/
*/

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
//#include "node.h"

using namespace std;

//node struct
struct node {
  int data;
  node* left;
  node* right;
};

struct Trunk {
  Trunk *prev;
  char str[10];
  
  Trunk(Trunk *prev, char str[10])
  {
    this->prev = prev;
    strcpy(str, this->str);
  }
};

// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
    if (p == nullptr)
        return;

    showTrunks(p->prev);
    
    cout << p->str;
}

//functions
void parse(char* in, int* modif, int &count);
void buildTree(int* modif, node** head, int size);
void insert(node** curr, int val);
void printTree(node *root, Trunk *prev, bool isLeft);


int main() {
  //variables
  char inp[10];
  char fileName[30];
  char input[10000];
  int count = 0;  //number of chars
  int modif[100];
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
      if (strcmp(inp, "file") == 0) {
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
	}
	cout << endl;      
      }
      else {
	cout << "No such input method. Try again." << endl;
      }
      //get size of modif array
      int siz = 0;
      for (int i = 0; i < 100; i++) {
	if(modif[i] != 0) {
	  siz++;
	} else break;
      }
      //create tree
      node* head = NULL;
      buildTree(modif, &head, siz);
      cout << "========Tree=Built=======" << endl;
      cout << head->data << endl;
      cout << (head->left)->data << endl;
      cout << (head->right)->data << endl;
      // print constructed binary tree
      cout << endl;
      printTree(head, nullptr, false);
      cout << "======Work=in=Tree=======" << endl;
      bool r = true;
      char resp[10];
      while (r) {
	cout << "YOu can: search, remove, or done:" << endl;
	cin.get(resp, 10);
	cin.clear();
	cin.ignore(10000, '\n');
	if (strcmp(resp, "search") == 0) {
	  
	} else if (strcmp(resp, "remove") == 0) {
	  
	} else if (strcmp(resp, "done") == 0) {
	  cout << endl << "Discarded current heap." << endl;
	  r = false;
	  cout << "=========================" << endl;
	} else {
	  cout << endl << "Invalid operation. Try again." << endl;
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

void buildTree(int* modif, node** head, int size) {
  for (int i = 0; i < size; i++) {
    insert(head, modif[i]);
    cout << "inserted " << modif[i] << endl;
  }
}

//insert function from GeeksforGeeks
void insert(node** curr, int val) { 
  node* current = NULL;
  if (*curr == nullptr) {
    *curr = new node;
    (*curr)->left = (*curr)->right = NULL;
    (*curr)->data = val;
  }
  else if (val <= (*curr)->data) {  //lower goes left
    current = (*curr)->left;
    insert(&current, val);
  }
  else {  //higher goes right 
    current = (*curr)->right;
    insert(&current, val);
  }
}

//https://www.techiedelight.com/c-program-print-binary-tree/
// Recursive function to print binary tree
// It uses inorder traversal
void printTree(node *root, Trunk *prev, bool isLeft) {
  if (root == nullptr) {
       return;
  }
  char prev_str[10];
  strcpy(prev_str, "    ");
  Trunk *trunk = new Trunk(prev, prev_str);
    
  printTree(root->left, trunk, true);
  
  if (!prev) {
    strcpy(trunk->str, "---");
  }
  else if (isLeft) {
    strcpy(trunk->str, ".---");
    strcpy(prev_str, "   |");
  }
  else {
    strcpy(trunk->str, "`---");
    strcpy(prev_str, prev->str);
  }
  showTrunks(trunk);
  cout << root->data << endl;
  
  if (prev) {
    strcpy(prev_str, prev->str);
  }
  strcpy(trunk->str, "   |");
  
  printTree(root->right, trunk, false);
}
