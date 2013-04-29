#include "vertex.h"

Vertex::Vertex(): edges(){}

unsigned Vertex::size() const{
    return edges.size();
}

void Vertex::Add(Edge* element){
    edges.insert(element);
}

void Vertex::Remove(Edge* element){
    edges.erase(element);
}

