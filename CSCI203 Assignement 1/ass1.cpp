//CSCI203 Assignment 1
//Name: Kazi Swad Abdullah
//UOW ID: ksa255

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

// Word Structure stores information about each word in the array of words stored
struct Word
{
 int start; //  index in array where the word begins
 int length; // length of the word
 int count; // number of occurences of the word
};

// Node Structure
struct Node
{
 int key;
 int height;
 Node *left;
 Node*right;
};

char array[200000];
Word WORDS[10000];

// The processWord function uses the standard library functions isalpha
// to only keep the alpahbetical characters and tolower to convert it
// to lowercase
char *processWord(char * newWord)
{
 int i, j, k = (int) strlen(newWord);
 for ( i=0, j=0; i < k; i++ )
  if (isalpha(newWord[i]))
   newWord[j++] = (char) tolower(newWord[i]);
  newWord[j] = '\0';
 return newWord;
}

int stringCompare(const Word *str1, const char *str2)
{
 for ( int i=0; i < min(str1->length, (int) strlen(str2)); i++ )
 {
  if ( array[str1->start + i] < str2[i] ) return 1;
  if ( array[str1->start + i] > str2[i] ) return -1;
 }
  if ( str1->length < strlen(str2) ) return 1;
  if ( str1->length > strlen(str2) ) return -1;

 return 0;
}

Node *search(Node *root, char *word)
{
 if ( root == NULL ) return NULL;
 if ( stringCompare(&WORDS[root->key], word) == 0 ) return root;
 else if ( stringCompare(&WORDS[root->key], word) < 0 ) search(root->left, word);
 else search(root->right, word);
}

int wordCompare(const Word *A, const Word *B)
{
 for ( int i=0; i < min(A->length, B->length); i++ )
 {
  if ( array[A->start + i] < array[B->start + i] ) return -1;
  if ( array[A->start + i] > array[B->start + i] ) return 1;
 }
  if ( A->length < B->length ) return -1;
  if ( A->length > B->length ) return 1;

 return 0;
}

int compare(Word *A, Word *B)
{
 if ( A->count < B->count ) return -1;
 else if ( A->count > B->count ) return 1;
 else return wordCompare(A, B);
}

// Quick Sort Algorithm Implementation
void swap(Word *a, Word *b)
{
 Word temp = *a;
 *a = *b;
 *b = temp;
}

int partition(Word arr[], int low, int high)
{
 Word *pivot = &arr[high];
 int i = (low - 1);
 for ( int j = low; j <= high - 1; j++ )
 {
  if ( compare(&arr[j], pivot) >= 0 )
  {
   i++;
   swap(&arr[i], &arr[j]);
  }
 }
 swap(&arr[i + 1], &arr[high]);
 return (i + 1);
}

void quickSort(Word arr[], int low, int high)
{
 if ( low < high )
 {
  int pi = partition(arr, low, high);
  quickSort(arr, low, pi- 1);
  quickSort(arr, pi + 1, high);
 }
}

// AVL tree Algotithm Implementaion

int max(int a, int b)
{
 return (a > b)? a : b;
}

int min(int a, int b)
{
 return (a < b)? a : b;
}

int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;

    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;

    return y;
}

Node *insert(Node *node, int key)
{
 if ( node == NULL )
 {
  Node *newNode = new Node();
  newNode->key = key;
  newNode->left = newNode->right = NULL;
  newNode->height = 1;
  return newNode;
 }

 if ( wordCompare(&WORDS[key], &WORDS[node->key]) == 0 )
        return node;
 else if ( wordCompare(&WORDS[key], &WORDS[node->key]) < 0 )
        node->left = insert(node->left, key);
 else if ( wordCompare(&WORDS[key], &WORDS[node->key]) > 0 )
        node->right = insert(node->right, key);

 node->height = 1 + max(height(node->left), height(node->right));

 int balance = getBalance(node);

 if ( balance > 1 && wordCompare(&WORDS[key], &WORDS[(node->left)->key]) < 0 )
     return rightRotate(node);

 if ( balance < -1 && wordCompare(&WORDS[key], &WORDS[(node->right)->key]) > 0 )
     return leftRotate(node);

 if ( balance > 1 && wordCompare(&WORDS[key], &WORDS[(node->left)->key]) > 0 )
 {
  node->left = leftRotate(node->left);
  return rightRotate(node);
 }

 if ( balance < -1 && wordCompare(&WORDS[key], &WORDS[(node->right)->key]) < 0 )
 {
  node->right = rightRotate(node->right);
  return leftRotate(node);
 }
 return node;
}

// Driver Function
int main()
{
 string file1;
 cerr<< "Insert file name: "; // Ask file name from user
 cin>>file1;
 ifstream readFile;
 readFile.open(file1); // Open file opened by user
 if (!readFile)
 {
  cerr <<"\nFILE ERROR : The file " << file1 << " could not be opened or does not exist."<<endl; // Error message if file cannot be opened
  exit(1);
 }

 char newWord[20]; // store word in array of characters of length 20
 Node *TREE = NULL; // Create a root for the tree
 int Counter1 = 0;
 int Counter2 = 0;

 while ( readFile >> newWord ) // Read until their is next word available
 {
 char *processedWord = processWord(newWord); // Process word read in the function processWord
 Node *result = search(TREE, processedWord);
 if ( result != NULL )
 {
  WORDS[result->key].count += 1;
 }
 else
 {
  Word Structure;
  Structure.start = Counter1;
  Structure.count = 1;
  Structure.length = 0;
  while ( Structure.length < strlen(processedWord) )
    array[Counter1++] = processedWord[Structure.length++];

   WORDS[Counter2] = Structure;
   TREE = insert(TREE, Counter2);
   Counter2++;
  }
 }
 readFile.close();
 int n = Counter2 - 1;

 quickSort(WORDS, 0, n);

 cout<<"FIRST 10 WORDS:"<<endl;
 cout<<"Count          Word\n"<<endl;

 for ( int i=0; i < 10; i++ )
 {
  cout<<WORDS[i].count;
  cout<<"              ";
  for ( int k=0; k < WORDS[i].length; k++ ) cout<<array[(WORDS[i].start) + k];
  cout<<endl;
 }

 cout<<"\nLAST 10 WORDS: "<<endl;
 cout<<"Count          Word\n"<<endl;

 for ( int m=n; m > (n - 10); m-- )
 {
  cout<<WORDS[m].count;
  cout<<"              ";
  for ( int i=0; i < WORDS[m].length; i++ ) cout<<array[(WORDS[m].start)++];
  cout<<endl;;
 }
}
