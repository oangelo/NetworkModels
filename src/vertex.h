#ifndef VERTEX_H
#define VERTEX_H 

#include <set>

#include "edge.h"


//Class vertex are use to model the nodes of the network and it properties
class Edge;

class Vertex{
    public:
        Vertex();
        unsigned size() const;
        void Add(Edge* element);
        void Remove(Edge* element);
    private:
        std::set<Edge*> edges; 
};

#endif /* VERTEX_H */
