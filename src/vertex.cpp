#include "vertex.h"

Vertex::Vertex(): edges(), mark(0){}

const Vertex* Vertex::operator[](size_t index){
    return edges[index].To();
}

const Edge& Vertex::operator()(size_t index){
    return edges[index];
}

unsigned Vertex::size() const{
    return edges.size();
}

bool Vertex::Add(const Edge& element){
    if(element.From() != this){
        std::cerr << "Trying to add a edge that is not from this vertex" << std::endl;
        return false;
    }
    for(auto edge: edges){
        if(edge.To() == element.To()){
            return false;
        }
    }
    edges.push_back(element);
    return true;
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


void Vertex::SetMark(int i){
    mark = i;
}

int Vertex::GetMark() const{
    return(mark);
}

bool operator==(const Vertex& rhs, const Vertex& lhs){
    if(&rhs == &lhs)
        return true;
    return false;
}
