//Excercise 2 - Implementing a Heap
//Name: Kazi Swad Abdullah
//UOW ID: ksa255

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;

int index = 0;
int heap[100];


void makeheap();
void siftdown(int);
void swap(int*, int*);

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
  if (index<120)
  {
   heap[index] = stoi(word);
   index++;
  }
 }
 readFile.close();

 makeheap();


 for (int i = 0;  i<5; i++)
 {
  cout<<heap[i]<<", ";
 }

 return 0;
}

void makeheap()
{
 for (int i = (index / 2) - 1; i >= 0; i--)
 {
  siftdown(i);
 }
}

void siftdown(int i)
{
    int left_child = (i * 2) + 1;
    int right_child = (i * 2) + 2;

    if (left_child >= index) return;
    int min_index = i;

    if (heap[i] < heap[left_child])
        min_index = left_child;
    if ((right_child < index) && (heap[min_index] < heap[right_child]))
        min_index = right_child;

    if (min_index != i) {
        swap(&heap[i], &heap[min_index]);
        siftdown(min_index);
    }
}

void swap(int *v1, int *v2)
{
     int temp = *v1;
     *v1 = *v2;
     *v2 = temp;
}

