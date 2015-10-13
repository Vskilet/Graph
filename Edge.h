/*
* Victor SENE
* victor.sene@utbm.fr
* INFO 01 - AG44
*/
#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include "Vertex.h"

using namespace std;


class Edge{
    friend class Graph;

    private :
        int _number;
        int _power;
        Vertex* _start;
        Vertex* _end;

    public :
        Edge(Vertex *s, Vertex *e, int n);
        ~Edge();
};
#endif
