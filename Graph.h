/*
* Victor SENE
* victor.sene@utbm.fr
* INFO 01 - AG44
*/

#ifndef GRAPH_H
#define  GRAPH_H

#include <iostream>
#include <fstream>

#include <stack>
#include <vector>

#include "Edge.h"

using namespace std;

class Graph{
    private :
    int _size;
    int _numVertex;
    int _numEdge;
    vector<Vertex*> _vertex;
    vector<Edge*> _edges;

    public :
    Graph();
    Graph(const char* fileName);
    ~Graph();


    void readFile(const char* fileName);
    void addVertex();
    void addEdge(const int i, const int j);
    void print();
    void stronglyConnected();


};
#endif
