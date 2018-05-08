#include <iostream>
#include <cstdlib>

using namespace std;

class Boruvka
{
        public:
                Boruvka(); //default Constructor
                int* findCheapestEdge(int *localEdges, int E, int* parentArray, int my_rank);
                void addToMST(int &MSTweight, int *cheapestArray, int *parentArray, int *edgeArray, int p);

                int find(int *parentArray, int i);
                void Union(int *parentArray, int *cheapestArray, int p);

        private:


};
