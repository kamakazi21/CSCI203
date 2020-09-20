//Excercise 6 - Karpin Rabin String Search Algorithm
//Name: Kazi Swad Abdullah
//UOW ID: ksa255

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>

using namespace std;

void search(char[], char[]);

int main()
{
 string file1;
 char letter;
 cerr<< "Insert file name: ";
 cin>>file1;
 ifstream readFile;
 readFile.open(file1);
 if (!readFile)
 {
  cerr <<"\nFILE ERROR : The file " << file1 << " could not be opened or does not exist."<<endl;
  exit(1);
 }

 char T[5000];
 char S[10];
 int i = 0;
 string line1;
 string line2;
 getline(readFile, line1);
 getline(readFile, line2);
 istringstream fin1(line1);
 while ( fin1>> letter)
 {
  T[i] = letter;
  i++;
 }
 i = 0;
 istringstream fin2(line2);
 while (fin2>> letter)
 {
  S[i] = letter;
  i++;
 }
 readFile.close();
 search(T,S);
 return 0;
}

void search(char T[], char S[])
{
    int M = strlen(S);
    int N = strlen(T);
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;

    for (i = 0; i < M - 1; i++)
        h = (h * 256) % 101;

    for (i = 0; i < M; i++)
    {
     p = (256 * p + S[i]) % 101;
     t = (256 * t + T[i]) % 101;
    }

    for (i = 0; i <= N-M; i++)
    {
     if (p == t)
     {
      for (j = 0; j < M; j++)
      {
       if (T[i+j] != S[j]) break;
      }

       if (j == M) cout<<i<<" ";
      }

      if (i < N - M)
      {
       t = (256 * (t - T[i] * h) + T[i + M]) % 101;

       if (t < 0) t = (t+101);
      }
    }
}
