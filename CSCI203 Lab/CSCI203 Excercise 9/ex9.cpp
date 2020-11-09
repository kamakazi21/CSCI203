//Excercise 9 - Crazy Eights
//Name: Kazi Swad Abdullah
//UOW ID: ksa255

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;

#define MAX(a,b) ( ((a) > (b)) ? (a) : (b) )

struct Card
{
  char rank;
  char suit;
};

int mlength = 0;
int fNode = 0;
int lNode = 0;

int crazy_up();

Card DECK[52];
int counter = 0;

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
  Card c;
  c.rank = word[0];
  c.suit = word[1];
  DECK[counter] = c;
  counter++;
 }
  crazy_up();
  cout << "The length of the longest sequence "<<mlength<<endl;
  cout << "The first card in the sequence " << DECK[fNode].rank << DECK[fNode].suit << endl;
  cout << "The last card in the sequence " << DECK[lNode].rank << DECK[lNode].suit << endl;
}

int crazy_up()
{
 int length[counter];
 length[0] = 0;

 for (int i = 1; i < counter; i++)
 {
  int len = 1;
  for (int j = i-1; j >= 0; j--)
  {
   if (DECK[i].rank == DECK[j].rank || DECK[i].suit == DECK[j].suit ||DECK[i].rank == '8' || DECK[j].rank == '8')
   {
    len = MAX(len, length[j] + 1);
   }
  if (len == mlength)
  {fNode = j;}
  }
  length[i] = len;
  if (mlength != MAX(len, mlength))
  {
   lNode = i;
   mlength = MAX(len, mlength);
  }
  else
  mlength = MAX(mlength, len);
 }
}
