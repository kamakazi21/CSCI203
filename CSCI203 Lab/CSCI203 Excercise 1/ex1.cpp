//Excercise 1 - Implementing a Stack
//Name: Kazi Swad Abdullah
//UOW ID: ksa255

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;

int index = 0;
string words[120];

void push(string word);
string pop();
string top();
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
 while (readFile >> word)
 {
  push(word);
 }
 index--;
 readFile.close();

 while (!isEmpty())
 {
  cout<<top()<<" ";
  pop();
 }

 cout<<endl;
 return 0;
}

void push(string word)
{
 if (index<120)
 {
  words[index] = word;
  index++;
 }
}

string pop()
{
 if (index>-1)
 {
  string temp = words[index];
  index--;
  return temp;
 }
}

string top()
{
 string temp = words[index];
 return temp;
}

bool isEmpty()
{
 return(index<0);
}

