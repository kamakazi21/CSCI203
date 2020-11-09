//Excercise 8 - Stacks Revisited
//Name: Kazi Swad Abdullah
//UOW ID: ksa255

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;

int index = 0;
int sze;
void push(int word, int words[]);
int pop(int []);
int top(int []);
bool isEmpty();

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
 readFile >> word;
 sze = stoi(word);
 int *words,*q;
 words=(int *)malloc(sze*sizeof(int));
 while (readFile >> word)
 {
  if (word == "pop")
  {
   pop(words);
  }
  else if (word == "push")
  {
   readFile >> word;
   push(stoi(word), words);
  }
  else
  {
   word.erase (0,4);
   push(stoi(word), words);
  }
  if (index>=sze)
  {
   q=(int *)malloc(2*sze*sizeof(int));
   for(int i=0;i<sze;i++)
   q[i]=words[i];
   free(words);
   words=q;
   q=NULL;
   cout<<"Stack doubled from "<<sze<<" to "<<sze*2<<"."<<endl;
   sze = sze*2;
  }
 }
 cout<<"Stack contains "<<index+1<<" entries."<<endl;
 readFile.close();

 cout<<endl;
 return 0;
}

void push(int word, int words[])
{
 words[index] = word;
 index++;
}

int pop(int words[])
{
 if (index>-1)
 {
  int temp = words[index];
  index--;
  return temp;
 }
}

int top(int words[])
{
 int temp = words[index];
 return temp;
}

bool isEmpty()
{
 return(index<0);
}
