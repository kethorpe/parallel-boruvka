#include <iostream>
#include <cstdlib>

using namespace std;

class Graph
{
        public:
                Graph(); 
                void createGraph(int E, int *arr);

                void addEdge(int i, int src, int dest, int weight);
                void printGraph();
                struct Edge
                {
                    int src, dest, weight;
                };

                int V;
                int E; 
                Edge* edge;
};
