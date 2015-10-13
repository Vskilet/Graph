/*
* Victor SENE
* victor.sene@utbm.fr
* INFO 01 - AG44
*/
#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <vector>

using namespace std;

class Vertex{
    friend class Graph;

    private :
        bool _mark;
        bool _plus;
        bool _moins;

        int _num;
        vector<Vertex*> _next;
        vector<Vertex*> _before;

    public :
        Vertex(int n);
        ~Vertex();


};
#endif
