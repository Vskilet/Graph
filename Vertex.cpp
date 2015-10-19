/*
 * INFO 01 - AG44
 * Victor SENE
 * victor.sene@utbm.fr
 */

#include "Vertex.h"

Vertex::Vertex(int n):_num(n), _leave(), _come(){
    _flag = false;
    _mark = false;
    _plus = false;
    _moins = false;
}
