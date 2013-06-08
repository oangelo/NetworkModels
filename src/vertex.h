#ifndef VERTEX_H
#define VERTEX_H 

#include <vector>
#include <cstddef>
#include <iostream>

#include "edge.h"


//Class vertex are use to model the nodes of the network and it properties
class Edge;

class Vertex{
    public:
        Vertex();
        const Vertex* operator[](size_t index);
        const Edge& operator()(size_t index);
        unsigned size() const;
        bool Add(const Edge& element);
        void Remove(const Edge& element);
        
    private:
        Vertex& operator=(Vertex&);
        std::vector<Edge> edges; 
};

bool operator==(const Vertex& rhs, const Vertex& lhs);

#endif /* VERTEX_H */
