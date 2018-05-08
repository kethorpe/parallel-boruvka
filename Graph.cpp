#include <iostream>
#include <cstdlib>
#include "Graph.h"

using namespace std;

Graph::Graph(){

}

void Graph::createGraph(int E, int *arr){
    this->E = E;
    this->edge = new Edge[E];
    for(int i = 0; i < E; i++){
       addEdge(i, arr[3*i], arr[3*i + 1],arr[3*i + 2]);
    }
}

void Graph::addEdge(int i, int src, int dest, int weight){
    this->edge[i].src = src;
    this->edge[i].dest = dest;
    this->edge[i].weight = weight;
}

void Graph::printGraph(){
  for(int e = 0; e < this->E; e++){
    cout << this->edge[e].src << "->" << this->edge[e].weight << "->" << this->edge[e].dest << endl;
  }
}
