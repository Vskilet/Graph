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
    cout << "My vertex : " ;
    for (int k = 0; k < _vertex.size(); k++) {
        cout << _vertex[k]->_num << " ";
    }
    cout << endl;
    //Liste des suivants
    for (size_t i = 0; i < _vertex.size(); i++) {
        cout << endl << "Son of Vertex " << i << ": ";
        for (size_t j = 0; j < _vertex[i]->_leave.size(); j++) {
            cout << _vertex[i]->_leave[j]->_num << " ";
        }
    }
    cout << endl;
    //Liste des précédents
    for (size_t i = 0; i < _vertex.size(); i++) {
        cout << endl << "Parents of Vertex " << i << ": ";
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
        Vertex* plusElement = plusMark();
        while (plusElement != NULL) {
            (*plusElement)._mark = true;
            for (it2 = (*plusElement)._leave.begin(); it2 != (*plusElement)._leave.end() ; ++it2){
                (**it2)._plus = true;
            }
            plusElement = plusMark();
        }

        falseForAll();
        Vertex* moinsElement = moinsMark();
        while (moinsElement != NULL) {
            (*moinsElement)._mark = true;
            for (it2 = (*moinsElement)._come.begin(); it2 != (*moinsElement)._come.end() ; ++it2){
                (**it2)._moins = true;
            }
            moinsElement = moinsMark();
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

Vertex* Graph::plusMark(){
    for (vector<Vertex*>::iterator i = _vertex.begin(); i != _vertex.end(); ++i) {
        if ((**i)._plus && !(**i)._mark && !(**i)._flag) {
            return (*i);
        }
    }
    return NULL;
}

Vertex* Graph::moinsMark(){
    for (vector<Vertex*>::iterator i = _vertex.begin(); i != _vertex.end(); ++i) {
        if ((**i)._moins && !(**i)._mark && !(**i)._flag) {
            return (*i);
        }
    }
    return NULL;
}

void Graph::matrixLevel(){
    vector<vector<Vertex*> > out = stronglyConnected();
    cout << endl << "Places peer level" << endl;
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
    cout << "Reduce Matrix of Level :" << endl;
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

void Graph::longestPath(const int id){
    vector<Vertex*> oldLongPath;
    vector<Vertex*> newLongPath;
    Vertex *current = _vertex[id];
    falseForAll();
    recursiveLgPath(*current, newLongPath, oldLongPath);


    cout << "Longuest path :";
    for (vector<Vertex*>::iterator it = oldLongPath.begin(); it != oldLongPath.end(); ++it) {
        cout << (**it)._num << " ";
    }
    cout << endl;
}

vector<Vertex*> Graph::recursiveLgPath(Vertex &current, vector<Vertex*> &newLongPath, vector<Vertex*> &oldLongPath){
    current._mark = true;
    newLongPath.push_back(&current);
    if (newLongPath.size() > oldLongPath.size()) {
        oldLongPath.clear();
        for(vector<Vertex*>::iterator it = newLongPath.begin(); it != newLongPath.end(); ++it){
            oldLongPath.push_back(*it);
        }
    }
    for(vector<Vertex*>::iterator it = current._leave.begin(); it != current._leave.end(); ++it){

        if (!(**it)._mark) {
            recursiveLgPath((**it), newLongPath, oldLongPath);
        }

    }
    current._mark = false;
    newLongPath.pop_back();
    return newLongPath;
}
