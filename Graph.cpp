/*
* Victor SENE
* victor.sene@utbm.fr
* INFO 01 - AG44
*/


#include "Graph.h"


Graph::Graph():_size(0), _numVertex(0), _numEdge(0), _vertex(), _edges(){}
Graph::Graph(const char* fileName):_size(0), _numVertex(0), _numEdge(0), _vertex(), _edges(){
    readFile(fileName);
}
Graph::~Graph(){
    _vertex.clear();
    _edges.clear();
}

void Graph::addVertex() {
    _vertex.push_back(new Vertex(_numVertex));
    _numVertex++;

}
void Graph::addEdge(const int i, const int j){
    _edges.push_back(new Edge(_vertex[i], _vertex[j], _numEdge));
    _numEdge++;
    _vertex[i]->_next.push_back(_vertex[j]);
    _vertex[j]->_before.push_back(_vertex[i]);

}

void Graph::readFile(const char* fileName){
    ifstream myFile(fileName);

    if (myFile.is_open())
    {
        myFile >> _size;
        for (int h = 0; h < _size; h++) {
            addVertex();
        }

        for (int i = 0; i < _size; i++) {
            for (int j = 0; j < _size; j++) {
                int temp;
                myFile >> temp;
                if (temp == 1) {
                    addEdge(i,j);
                }
            }
        }
        myFile.close();
    }
    else{
        cout << "Unable to open file";
    }
}

void Graph::print(){
    for (int k = 0; k < _vertex.size(); k++) {
        cout << _vertex[k]->_num << endl;
    }

    //Liste des suivants
    for (size_t i = 0; i < _vertex.size(); i++) {
        cout << endl << "Suivant de Vertex " << i << ": ";
        for (size_t j = 0; j < _vertex[i]->_next.size(); j++) {
            cout << _vertex[i]->_next[j]->_num << " ";
        }
    }
    cout << endl;
    //Liste des précédents
    for (size_t i = 0; i < _vertex.size(); i++) {
        cout << endl << "Précédent de Vertex " << i << ": ";
        for (size_t j = 0; j < _vertex[i]->_before.size(); j++) {
            cout << _vertex[i]->_before[j]->_num << " ";
        }
    }
    cout << endl;

}

void stronglyConnected(){


}
