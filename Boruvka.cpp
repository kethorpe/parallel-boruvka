#include <iostream>
#include <cstdlib>
#include "Graph.h"
#include "Boruvka.h"

using namespace std;

Boruvka::Boruvka(){
 //cout << "instantiated Boruvka" << endl; 
}

int* Boruvka::findCheapestEdge(int* localEdges, int E, int* parentArray, int my_rank){
   
    int currentWeight = 1000;
    int currentEdge = -1;
    int currentSet;
    int *returnEdge = (int*)malloc(sizeof(int) * 3);

    for (int i=0; i<E; i++)
    {
        int set1 = find(parentArray, localEdges[3*i]);
        int set2 = find(parentArray, localEdges[3*i+1]);

        if(set1 == set2) continue;

        if(localEdges[3*(parentArray[set2]%11)+2] < localEdges[3*i+2] && localEdges[3*i+2] < currentWeight){
          currentEdge = i;
          currentSet = set2;
          currentWeight =  localEdges[3*i+2];
        }
    }
   returnEdge[0] = localEdges[3*currentEdge];
   returnEdge[1] = localEdges[3*currentEdge+1];
   returnEdge[2] = localEdges[3*currentEdge+2];

   return returnEdge;

}

void Boruvka::addToMST(int &MSTweight, int* cheapestArray, int *parentArray, int* edgeArray, int p){

   for(int i = 0; i < p; i++){
      if(cheapestArray[3*i + 2] != 0){
         MSTweight += cheapestArray[3*i + 2];
         cout << "new MSTweight is: " << MSTweight << endl;
         Union(parentArray, cheapestArray,  p);
      }
   }
}

int Boruvka::find(int *parentArray, int i){
  if (parentArray[i] != i){
      parentArray[i] = find(parentArray, parentArray[i]);
  }

    return parentArray[i];
}

void Boruvka::Union(int *parentArray, int *cheapestArray, int p){
    for(int i = 0; i < p; i++){
       int xroot = find(parentArray, cheapestArray[3*i]);
       int yroot = find(parentArray, cheapestArray[3*i+1]);
       parentArray[xroot] = yroot;
   }
}
