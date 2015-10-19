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
void Graph::addEdge(Vertex* vi, Vertex* vj){
    _edges.push_back(new Edge(vi, vj, _numEdge));
    _numEdge++;
    vi->_leave.push_back(vj);
    vj->_come.push_back(vi);
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
                    addEdge(_vertex[i], _vertex[j]);
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
    cout << "Mes vertex : " ;
    for (int k = 0; k < _vertex.size(); k++) {
        cout << _vertex[k]->_num << " ";
    }
    cout << endl;
    //Liste des suivants
    for (size_t i = 0; i < _vertex.size(); i++) {
        cout << endl << "Suivant de Vertex " << i << ": ";
        for (size_t j = 0; j < _vertex[i]->_leave.size(); j++) {
            cout << _vertex[i]->_leave[j]->_num << " ";
        }
    }
    cout << endl;
    //Liste des précédents
    for (size_t i = 0; i < _vertex.size(); i++) {
        cout << endl << "Précédent de Vertex " << i << ": ";
        for (size_t j = 0; j < _vertex[i]->_come.size(); j++) {
            cout << _vertex[i]->_come[j]->_num << " ";
        }
    }
    cout << endl;

}

vector<vector<Vertex*> > Graph::stronglyConnected(){

    vector<Vertex*>::iterator it;
    vector<Vertex*>::iterator it2;

    vector<vector<Vertex*> > out;
    vector<Vertex*> tmp;
    Vertex* flagReply = noFlagElement();
    while (flagReply != NULL) {

        for (int i = 0; i < _vertex.size(); i++) {
            _vertex[i]->_plus = false;
            _vertex[i]->_moins = false;
        }
        falseForAll();
        flagReply->_plus = flagReply->_moins = true;
        for (it = _vertex.begin(); it != _vertex.end(); ++it) {
            if ((**it)._plus && !(**it)._mark && !(**it)._flag) {
                (**it)._mark = true;
                for (it2 = (**it)._leave.begin(); it2 != (**it)._leave.end() ; ++it2){
                    (**it2)._plus = true;
                }
            }
        }

        falseForAll();
        for (it = _vertex.begin(); it!=_vertex.end(); ++it) {
            if ((**it)._moins && !(**it)._mark && !(**it)._flag) {
                (**it)._mark = true;
                for (it2 = (**it)._come.begin(); it2 != (**it)._come.end() ; ++it2){
                    (**it2)._moins = true;
                }
            }
        }

        for (it = _vertex.begin(); it!=_vertex.end(); ++it) {
            if ((**it)._plus && (**it)._moins) {
                tmp.push_back(*it);
                (**it)._flag = true;
            }
        }
        out.push_back(tmp);
        tmp.clear();
        flagReply = noFlagElement();
    }
    return out;
}

void Graph::falseForAll(){
    for (int i = 0; i < _vertex.size(); i++) {
        _vertex[i]->_mark = false;
    }
}

Vertex* Graph::noFlagElement(){
    for (vector<Vertex*>::iterator i = _vertex.begin(); i != _vertex.end(); ++i) {
        if (!(**i)._flag) {
            return (*i);
        }
    }
    return NULL;
}

void Graph::matrixLevel(){
    vector<vector<Vertex*> > out = stronglyConnected();
    cout << endl << "Liste des places par level" << endl;
    for (vector<vector<Vertex*> >::iterator it = out.begin(); it != out.end(); ++it) {

        for (size_t i = 0; i < (*it).size(); i++) {
            cout << (*it)[i]->_num << " ";
        }
        cout << endl;
    }
    cout << endl;

    reduceMatrixLevel(out);

}

void Graph::reduceMatrixLevel(vector<vector<Vertex*> > out){
    int start, end;
    vector<vector<int> > reduceMatrix(out.size());
    for (int i = 0; i < reduceMatrix.size(); i++) {
        reduceMatrix[i] = vector<int>(out.size());
    }
    for(vector<Edge*>::iterator it = _edges.begin(); it != _edges.end(); ++it){
        start = vertexLevel((**it)._start, out);
        end = vertexLevel((**it)._end, out);
        if (start != end) {
            reduceMatrix[start][end]++;
        }
    }

    //On Screen
    cout << "Matrice de réduite :" << endl;
    for (vector<vector<int> >::iterator it = reduceMatrix.begin(); it != reduceMatrix.end(); ++it) {

        for (int i = 0; i < (*it).size(); i++) {
            cout << (*it)[i] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int Graph::vertexLevel(Vertex* v, vector<vector<Vertex*> > out){
    for(vector<vector<Vertex*> >::iterator it = out.begin(); it != out.end(); ++it){
        for(vector<Vertex*>::iterator it2 = (*it).begin(); it2 != (*it).end(); ++it2){
            if (((**it2)._num) == ((*v)._num)){
                return (it - out.begin());
            }
        }
    }
}

void Graph::longestPath(){
    vector<Vertex*> longPath;

    falseForAll();
    Vertex* current = _vertex[0];



    cout << "Longuest path :";
    for (vector<Vertex*>::iterator it = longPath.begin(); it != longPath.end(); ++it) {
        cout << (**it)._num << " ";
    }
    cout << endl;
}

Vertex* Graph::recursiveLgPath(Vertex* current){
    if (current._leave.size() != 0) {
        current._mark == true;
        longPath.push_back(recursiveLgPath((*current)._leave);
    }
    else{
        return current;
    }
}
