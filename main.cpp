#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
#include "mpi.h"
#include "Graph.h"
#include "Boruvka.h"

using namespace std;

int E = 640;
int V = 500;

void Write(int *sortedArray){
   ofstream myfile;
   myfile.open("out.txt");
   if(myfile.fail()){
        cout << "Unable to open file to write";
        return;
   }
   for(int i = 0; i < 3*E; i++){
       myfile << sortedArray[i] << " ";
   }
   myfile.close();
}
void PrintEdgeArray(int *arr){
  for (int i = 0; i < E; i++)
    {
        cout << arr[3*i] << ' ' << arr[3*i + 1] << " " << arr[3*i+2] << endl;
    }
   cout << endl << endl;
}

void PrintArray(int *arr, int size){
   for(int i = 0; i < size; i++){
      cout<< arr[i] << " ";
   }
   cout << endl;
}
 
void RandomWrite(){
   /* initialize random seed: */
   srand(time(NULL));
   int random;
   ofstream myfile;
   myfile.open("in.txt");
   if(myfile.fail()){
        cout << "Unable to open file to write";
        return;
   }
   for(int i = 0; i <= E; i++){
      int V1  = rand() % V;
      int V2 = rand() % V;
      int weight = rand() % 80;
      myfile << V1 << " " << V2 << " " << weight << " ";
   }
   myfile.close();
}

void InitializeParentArray(int *arr){

   for(int i=0; i < V; i++){
      arr[i] = i;
   }

}

void ReadInFile(int *arr){
   int V1, V2, weight;
   ifstream din;
 
   din.open("in.txt");
   if (din.fail()) {
        cout << "Unable to open file to read";
        return;
    }
   for(int i = 0; i < E; i++){
        din >> V1 >> V2 >> weight;;
        arr[3*i] = V1;
        arr[3*i + 1] = V2;
        arr[3*i + 2] = weight;
   }
  din.close();
}

main(int argc, char* argv[])
{
  int my_rank;       /* rank of process      */
  int p;             /* number of processes  */
  int source;        /* rank of sender       */
  int dest;          /* rank of receiver     */
  int tag = 0;       /* tag for messages     */
  MPI_Status status;        /* return status for receive */
  int elementsPerProc;   /*Edges per processor */
  int *edgeArray, *parentArray, *localEdgeArray, *cheapestArray; /*local array for each proc */
  int *localCheapest; /*local Cheapest edge*/
  int MSTweight;    /*holds weight of MST*/

  /* Start up MPI */
  MPI_Init(&argc, &argv);

  /* Find out process rank  */
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  
  /* Find out number of processes */
  MPI_Comm_size(MPI_COMM_WORLD, &p);

   if(my_rank == 0){
       edgeArray = (int*)malloc(sizeof(int) * (3*E));
       MSTweight = 0;
       RandomWrite();
       ReadInFile(edgeArray);
       //PrintEdgeArray(edgeArray);
       //PrintParentArray(parentArray);
       cout<< "leaving rank 0" << endl;
   }
    cheapestArray = (int*)malloc(sizeof(int)*(p*3));
    parentArray = (int*)malloc(sizeof(int) * (V));
    localCheapest = (int*)malloc(sizeof(int) * (3));
    InitializeParentArray(parentArray);

   elementsPerProc = (3*E) / p;

   localEdgeArray = (int*)malloc(sizeof(int) * elementsPerProc);
 
   MPI_Scatter(edgeArray, elementsPerProc, MPI_INT, localEdgeArray, elementsPerProc, MPI_INT, 0, MPI_COMM_WORLD);

   Boruvka b;

   for(int i = 0; i < elementsPerProc / 3; i++){
      
      MPI_Bcast(parentArray, V, MPI_INT, 0, MPI_COMM_WORLD);

      localCheapest = b.findCheapestEdge(localEdgeArray, (elementsPerProc / 3), parentArray, my_rank);

      MPI_Gather(localCheapest, 3, MPI_INT, cheapestArray, 3, MPI_INT, 0, MPI_COMM_WORLD);

      if(my_rank == 0){
           cout<<"proc0 on iteration: " << i <<  endl;
           b.addToMST(MSTweight, cheapestArray, parentArray, edgeArray, p);
           //PrintArray(parentArray, V);
      }
  }

  if(my_rank == 0){
     PrintArray(parentArray, V);
  }

   /* Shut down MPI */
   MPI_Finalize();
}

