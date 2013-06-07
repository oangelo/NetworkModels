#include "vertex.h"

Vertex::Vertex(): edges(){}

const Vertex* Vertex::operator[](size_t index){
    return edges[index].To();
}

const Edge& Vertex::operator()(size_t index){
    return edges[index];
}

unsigned Vertex::size() const{
    return edges.size();
}

void Vertex::Add(const Edge& element){
    if(element.From() != this)
        return;
    for(auto edge: edges){
        if(edge.To() == element.To()){
            return;
        }
    }
    edges.push_back(element);
}

void Vertex::Remove(const Edge& element){
    if(element.From() != this)
        return;
    if(element.To() != edges.end()->To()){
        edges.pop_back();
        return;
    }
    for(auto i(edges.begin()); i != edges.end(); ++i){
        if((*i).To() == element.To()){
            edges.erase(i);
        }
    }
}
