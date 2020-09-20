//Excercise 4 - BST Sort
//Name: Kazi Swad Abdullah
//UOW ID: ksa255

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef struct Node {
    int key;
    struct Node *left, *right;
    int height;
} Node;

int COUNTER = 0;

Node* insert_first(int);
void  insert(Node*, int);
void  sort(Node*);

int main()
{
 string file1;
 cerr<< "Insert file name: ";
 cin>>file1;
 ifstream readFile;
 readFile.open(file1);
 if (!readFile)
 {
  cerr <<"\nFILE ERROR : The file " << file1 << " could not be opened or does not exist."<<endl;
  exit(1);
 }

 Node *ROOT = NULL;
 int key;

 while (readFile >> key)
 {
  if ( ROOT == NULL ) ROOT = insert_first(key);
  else insert(ROOT, key);
 }

 readFile.close();
 sort(ROOT);
 return 0;
}

Node* insert_first(int key)
{
 Node *first = (Node *)malloc(sizeof(Node));
 first->key = key;
 first->height = 0;
 first->left = first->right = NULL;
 return first;
}

void insert(Node* node, int key)
{
 Node *next = NULL;
 bool left;

 if ( key == node->key )  return;
 else if ( key < node->key )
 {
  next = node->left;
  left = true;
 }
 else
 {
  next = node->right;
  left = false;
 }

 if ( next != NULL ) insert(next, key);
 else
 {
  Node *New = (Node *)malloc(sizeof(Node));
  New->key = key;
  New->left = New->right = NULL;
  New->height = 0;
  if ( left ) node->left = New;
  else node->right = New;
 }
}

void sort(struct Node* tree)
{
 if ( tree != NULL )
 {
  if ( tree->left != NULL ) sort(tree->left);
  COUNTER++;
  cout<<tree->key<<", ";
  if ( tree->right != NULL ) sort(tree->right);
 }
}
