/*
* Victor SENE
* victor.sene@utbm.fr
* INFO 01 - AG44
*/


#include "Graph.h"

using namespace std;

int main(int argc, char const *argv[]) {
    Graph graph("mat1.txt");
    graph.print();
    graph.matrixLevel();
    graph.longestPath();
    return 0;
}
