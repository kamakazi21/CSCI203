//Excercise 3 - Virtual Initialization
//Name: Kazi Swad Abdullah
//UOW ID: ksa255

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>


using namespace std;

int Data[100], Forward[100], Backward[100];
int Count = 0;

void Insert(int, int);
bool Check(int);

int main(int argc, const char* argv[] )
{
 string file1;
 string line;
 string temp;
 int what,where,probe;
 bool BK = false;
 cerr<< "Insert file name: ";
 cin>>file1;
 ifstream readFile (file1);

 if (!readFile)
 {
  cerr <<"\nFILE ERROR : The file " << file1 << " could not be opened or does not exist."<<endl;
  exit(1);
 }

  while (BK == false)
  {
   readFile >> what >> where;
   if (what > 0 && where > 0)
    Insert(what,where);
   else
    BK = true;
  }

  BK = false;

  while (BK == false)
  {
   readFile >> probe;
   if (probe > 0)
   {
    if (Check(probe))
     cout<<"Position "<<probe<<" has been initialized to value "<<Data[probe]<<endl;
    else
     cout<<"Position "<<probe<<" has not been initialized. "<<endl;
   }
   else
    BK = true;
  }

 return 0;
}

void Insert(int what, int where)
{
    Count++;
    Data[where] = what;
    Forward[Count] = where;
    Backward[where] = Count;
}

bool Check(int probe)
{
 return Backward[probe] > 0 &&
  Backward[probe] <= Count &&
   Forward[Backward[probe]] == probe ?
    true : false;
}
