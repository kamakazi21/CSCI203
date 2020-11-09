//Excercise 10 - Matrix Multiplication
//Name: Kazi Swad Abdullah
//UOW ID: ksa255

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <climits>
#include <iostream>

using namespace std;

int MatrixChainOrder(int* p, int n)
{
	n++;
	int m[n][n];
	int i, j, k, L, q;

	for (i = 0; i < n; i++)
		m[i][i] = 0;

	for (L = 2; L < n; L++)
	{
		for (i = 1; i < n - L + 1; i++)
		{
			j = i + L - 1;

			m[i][j] = INT_MAX;
			for (k = i; k <= j - 1; k++)
			{
				q = m[i][k] + m[k + 1][j]
					+ p[i - 1] * p[k] * p[j];

				if (q < m[i][j]) {
					m[i][j] = q;
				}
			}
		}
	}
	return m[1][n - 1];
}

int main()
{
 string file1;
 string word;
 int size1;
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
 size1 = stoi(word);
 int counter = 0;
 int arr[size1];

 while (counter<size1-1)
 {
  readFile >> word;
  arr[counter] =stoi(word);
  counter++;
  readFile >> word;
 }
  readFile >> word;
  arr[counter] =stoi(word);
  counter++;
  readFile >> word;
  arr[counter] =stoi(word);

 cout << "Minimum number of multiplications is "<< MatrixChainOrder(arr, size1)<<endl;
 getchar();
 return 0;
}


