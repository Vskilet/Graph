/*
* Victor SENE
* victor.sene@utbm.fr
* INFO 01 - AG44
*/

#include <iostream>
#include <std::list>

class Edge;

class Vertex{
    private :
        bool _flag;
        int _number;

    public :
        Vertex();
        ~Vertex();
        vector<Vertex*> _next;
        vector<Vertex*> _before;

}
