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
    void addEdge(Vertex* vi, Vertex* vj);
    void print();
    vector<vector<Vertex*> > stronglyConnected();
    void falseForAll();
    Vertex* noFlagElement();
    void matrixLevel();
    void reduceMatrixLevel(vector<vector<Vertex*> > out);
    int vertexLevel(Vertex* v, vector<vector<Vertex*> > out);
    void longestPath();
    Vertex* recursiveLgPath(Vertex* current);




};
#endif
