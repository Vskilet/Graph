/*
* Victor SENE
* victor.sene@utbm.fr
* INFO 01 - AG44
*/

#include "Edge.h"

Edge::Edge(Vertex *s, Vertex *e, int n){
    _number = n;
    _power = 0;
    _start = s;
    _end = e;
}
Edge::~Edge(){
}
