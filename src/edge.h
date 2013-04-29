#ifndef EDGE_H
#define EDGE_H 

#include "vertex.h"

class Vertex;

class Edge{
    public:
        Edge(Vertex* from, Vertex* to, bool bidirectional = false);
        Vertex* From() const;
        Vertex* To() const;
        bool IsBidirectional() const;
    private:
        Vertex* from;
        Vertex* to;
        bool bidirectional;
};

#endif /* EDGE_H */
