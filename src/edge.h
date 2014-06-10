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

        void SetMark(int i);
        int GetMark() const;
    private:
        Vertex* from;
        Vertex* to;
        bool bidirectional;
        int mark;
};

#endif /* EDGE_H */
