/*
* Victor SENE
* victor.sene@utbm.fr
* INFO 01 - AG44
*/

#include <iostream>
#include <fstream>
#include <string>

#include <stack>
#include <vector>

#include "Vertex.h"

class Graph{
    private :
    char* _name;
    int _size;
    vector<Vertex*> _vertex;

    public :
    Graph();
    Graph(const Graph& g);
    ~Graph();


    void readFile(const char* fileName);
};


//vector<Vertex*> tarjan()
