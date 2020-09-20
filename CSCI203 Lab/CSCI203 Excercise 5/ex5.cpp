//Excercise 5 - Hashing
//Name: Kazi Swad Abdullah
//UOW ID: ksa255

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

#define MAX(a,b) ( (a > b) ? a : b )

using namespace std;

void insert(int key);

struct Node
{
 int key;
 Node *next;
};

Node hashtable[100];
int longestChain = 0;
int chainLength = 0;
int emptyEntries = 0;

int main()
{
 string file1;
 string word;
 cerr<< "Insert file name: ";
 cin>>file1;
 ifstream readFile;
 readFile.open(file1);
 if (!readFile)
 {
  cerr <<"\nFILE ERROR : The file " << file1 << " could not be opened or does not exist."<<endl;
  exit(1);
 }

 while (readFile >> word)
 {
  insert(stoi(word));
 }

 readFile.close();

 for (int i = 0; i < 200; i++)
 {
  if ( hashtable[i].key == 0 )
  {
   emptyEntries++;
  }
 }

 cout <<"Empty entries: " << emptyEntries <<endl;
 cout <<"Longest chain: " << chainLength <<endl;

 return 0;
}


void insert(int key)
{
 int index = key%100;
 if (hashtable[index].key == 0)
 {
  Node newNode;
  newNode.key = key;
  newNode.next = NULL;
  hashtable[index] = newNode;
  chainLength = 1;
 }
 else
 {
  Node temp;
  temp.key = hashtable[index].key;
  temp.next = hashtable[index].next;
  Node newNode;
  newNode.key = key;
  newNode.next = &temp;
  hashtable[index] = newNode;
  chainLength++;
  longestChain = MAX(longestChain, chainLength);
 }
}
