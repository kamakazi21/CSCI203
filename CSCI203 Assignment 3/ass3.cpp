//Assignment 3 -  Single Source-Single Destination Shortest Path Problem
//Name: Kazi Swad Abdullah
//UOW ID: ksa255

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define min(a,b) ((a)<(b)?(a):(b))
#define INT_MAX 2147483647

using namespace std;

vector<int> length; //global variable length is a vector which stores the k shortest lengths between src and the dst
vector<int> path; //global variable path is a vector which stores the path nodes for k shortest lengths between src and the dst in ascedning order.
vector<vector<int>>graph; //global variable graph is a two dimensional vector of ints which will hold the weight of the edges between the respective nodes
int edges; // global variable edges holds the number of edges
int vertices; // global variable vertices holds the number of vertices

// A utility function which recursively iterates all elements in the parent array and add them
// to the global variable path
void iterate(int parent[], int child)
{
 if (child == - 1)  return;
 iterate(parent,parent[child]);
 path.push_back(child);
}

// Function implements Dijkstras Single Source-Single Destination Shortest Path Problem
// which accepts the the desired source and destination as arguments.
void dijkstra(int src, int dest)
{
 int distances[vertices]; // an array of distances hold the shortest distances from src to i
 bool spt[vertices]; // an shortest path tree aray which which is true if vertices are in shortest
                     // path  and if shortest distance has been found

 for (int i = 0; i < vertices; i++) // Loop for the number of vertices
 {
  distances[i] = INT_MAX; // initializes all elements in distances to infinity
  spt[i] = false; // initilizes all elements in spt as false
 }

  distances[src] = 0; //set the distance from the source node to itself as 0
  int parent[vertices]; //create an array parent which holds the predecesoors of the source node
  parent[src] = -1; // set the predecessor of the src node as -1

  // Iterate for all the vertices in the graph
  for (int i = 0; i < vertices ; i++)
  {
   int min = INT_MAX; // Initiate variable min to infinity
   int minIndex = -1; // Initiate variable minIndex to -1

   // Iterate for all the vertices in the graph
   for (int v = 0; v < vertices; v++)
   if (spt[v] == false && distances[v] <= min) //if v not included spt and and distance[v] is less than the minimum
    min = distances[v], minIndex = v; //set the minimum to distance[v] and set the index to v.

   int u = minIndex; // set u to the vertex with the minimum distance value
   spt[u] = true; // set the vertex value of that as being in the path

// Iterate for all the vertices in the graph
   for (int v = 0; v < vertices; v++)
   {
    if (!spt[v] && graph[u][v] && distances[u] + graph[u][v] < distances[v]) // Condition occurs if the node is not in the current path, there is an edge from u to v and the weight from src to v through u is smaller the current value for distance[v]
    {
      distances[v] = distances[u] + graph[u][v]; // update distance[v]
      parent[v] = u; //set parent of v as u
    }
     else if (!spt[v] && graph[v][u] && distances[u] + graph[v][u] < distances[v]) // Condition occurs if the node is not in the current path, there is an edge from v to u and the weight from src to v through u is smaller the current value for distance[v]
    {
     distances[v] = distances[u] + graph[v][u]; // update distance[v]
     parent[v] = u; //set parent of v as u
    }
   }
  }

 length.push_back(distances[dest]); //push the shortest length of src to det to the vector length
 iterate(parent,dest); //function call to iterate
}

//Driver Program to test the prgram functionalities.
int main()
{
 string file1; //File1 variable stores the name of the file
 string word; // Word variable stores the words as they are read.
 cout<< "Insert file name: "; //Asks the user in console for the file name.
 cin>>file1; //Stores the user input from console in variable file1.

 ifstream readFile; //Creates ifstream object readFile
 readFile.open(file1); //Assigns file1 to the readFile object and opens it.
 if (!readFile) // Shows error message if the file cannot be opened
 {
  cerr <<"\nFILE ERROR : The file " << file1 << " could not be opened or does not exist."<<endl; // Outputs error message to cerr
  exit(1); // Exits Program
 }

 readFile >> word; // Reads the first word in the file which is the number of vertices
 vertices = stoi(word); // Converts word to int and stores it in the variable vertices
 readFile >> word; // Reads the second word in the file which is the number of edges.
 edges = stoi(word); // Converts word to int and stores it in the variable edges.

 int counter1 = 0; // initiates counter1 and sets to 0
 int counter2 = 0; // initiates counter2 and sets to 0

 int nodes[vertices]; // initiatees an array of ints called nodes and sets its size to the number of vertices.
 double xCord[vertices]; // initiatees an array of doubles called xCord and sets its size to the number of vertices.
 double yCord[vertices]; // initiatees an array of doubles called yCord and sets its size to the number of vertices.

 while (counter1<vertices) // while loop that iterates till counter is less than teh number of vertices.
 {
  readFile >> word; // Reads the first word in the ensuing line which is the node number.
  nodes[counter1] =stoi(word); // Converts word to int and stores it in the array of nodes.
  readFile >> word; // Reads the second word in the ensuing line which is the x coordinate of the node.
  xCord[counter1] =stoi(word); // Converts word to double and stores it in the array of x cooridnates.
  readFile >> word; // Reads the third word in the ensuing line which is the y coordinate of the node.
  yCord[counter1] =stoi(word); // Converts word to double and stores it in the array of y cooridnates.
  counter1++; //increments counter1
 }

 for (int i = 0; i<vertices; i++) //Iterates for the number of vertices
 {
  vector<int> v1; // Initiates a temporary vector v1
  for (int j = 0; j<vertices; j++) //Iterates for the number of vertices
  {
   v1.push_back(0); // pushes the value of 0 into vector.
  }
  graph.push_back(v1); // pushes the vector v1 into the two dimensional graph
 }

 int node1; //variable node1 holds the first node of the edge
 int node2; //variable node2 holds the first node of the edge
 int weight; //variable weight holds the first weight of the edge

 while (counter2<edges) //Iterates for the number of vertices
 {
  readFile >> word; // Reads the first word in the ensuing line which is the number for node 1.
  node1 =stoi(word);  // Converts word to int and stores it in the node1 variable
  readFile >> word; // Reads the second word in the ensuing line which is the number for node 2.
  node2 =stoi(word); // Converts word to int and stores it in the node2 variable
  readFile >> word; // Reads the thirsd word in the ensuing line which is the weight for the edge.
  weight =stoi(word); // Converts word to int and stores it in the weight variable
  if ((graph[node2-1][node1-1] == 0) && (graph[node1-1][node2-1] == 0)) // if the edge node1->node2 and node2->node1 is 0
  {
   graph[node1-1][node2-1] = weight; //set edge node1->node2 to the assocaiated weight
  }
  else
  {
   graph[node1-1][node2-1] = min((graph[node2-1][node1-1]),weight); //set edge node1->node2 to the minimum of weight and edge node2->node1
  }
  counter2++; //increments counter2
 }

  readFile >> word; // Reads the first word in the last line which is the source node number.
  int src =stoi(word); // Initiates a int variable src, converts word to int and stores teh value of the source node number.
  readFile >> word; // Reads the second word in the last line which is the destination node number.
  int dest =stoi(word);  // Initiates a int variable dest, converts word to int and stores teh value of the destination node number.

  dijkstra(src-1, dest-1); // Function call to the dijkstra function with the source src and destination dest as arguments

  path[0] = src-1; // Sets the the first element in the path to source

  //  Removes the first edge in the shortest path
  graph[path[0]][path[1]] = 0;
  graph[path[1]][path[0]] = 0;

  dijkstra(src-1, dest-1); // Function call to the dijkstra function with the source src and destination dest as arguments

  counter1 = 0; // sets counter1 to 0
  counter2 = 0; // sets counter2 to 0

  // Prints output to console.
  // 1) Shortest Path between src and dest including the x and y coordinates
  // 2) Length of Shortest Path between src and dest
  // 3) Second Shortest Path between src and dest including the x and y coordinates
  // 4) Length of Second Shortest Path between src and dest

  cout<<"The vertices on the shortest path from node "<<src<<" to node "<<dest<<" is: "<<endl;
  while (counter1 != dest) // Loop for as long as counter1 is not equal destination node
  {
  cout<<path[counter2]+1<<"("<<xCord[path[counter2]]<<","<<yCord[path[counter2]]<<")"<<endl;
  counter1 = path[counter2]+1;
  counter2++; // Increment counter2
  }
  cout<<endl;
  cout<<"The length of the shortest path from node "<<src<<" to node "<<dest<<" is "<<length[0]<<"."<<endl;
  cout<<endl;

  counter1=0; // sets counter1 to 0

  cout<<"The vertices on the second shortest path from node "<<src<<" to node "<<dest<<" is: "<<endl;
  while (counter1 != dest) // Loop for as long as counter1 is not equal destination node
  {
  cout<<path[counter2]+1<<"("<<xCord[path[counter2]]<<","<<yCord[path[counter2]]<<")"<<endl;
  counter1 = path[counter2]+1;
  counter2++; // Increment counter2
  }
  cout<<endl;
  cout<<"The length of the second shortest path from node "<<src<<" to node "<<dest<<" is "<<length[1]<<"."<<endl;

  return 0;
}
