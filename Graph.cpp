/*
* Victor SENE
* victor.sene@utbm.fr
* INFO 01 - AG44
*/


#include "Graph.h"

using namespace std;

Graph::Graph(){

}
Graph::Graph(const Graph& g){

}
Graph::~Graph(){

}

Graph vector<Vertex*> tarjan(){
    int v = 0;
    stack stack = new stack();
    Graph tempGraph = new Graph();

    function(Vertex v){
        v._number;
        for (vertex w : v->_next){
            if (w._number = NULL){
                function(w);
                v.
            }
        }
    }

}

void Graph::readFile(const char* fileName){
    string line;
    ifstream myFile(fileName);
    if (myFile.is_open())
    {
        while ( getline (myFile,line) )
        {
            cout << line << '\n';
        }
        myFile.close();
    }
    else{
        cout << "Unable to open file";
    }
}
