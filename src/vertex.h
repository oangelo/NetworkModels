#ifndef VERTEX_H
#define VERTEX_H 

#include <vector>
#include <cstddef>
#include <iostream>
#include <map>

#include "edge.h"


//Class vertex are use to model the nodes of the network and it properties
class Edge;

class Vertex{
    public:
        Vertex();

        Vertex& operator[](size_t index);
        Edge& operator()(size_t index);

        Edge* FindIncoming(Vertex* vertex);
        
        unsigned size() const;

        bool Add(const Edge& element);
        void AddIncoming(Vertex* vertex, Edge* edge);
        void Remove(const Edge& element);


        void SetMark(int i);
        int GetMark() const;
        
    private:
        Vertex& operator=(Vertex&);
        std::vector<Edge> edges; 
        int mark;
        std::map<Vertex*,Edge*> incoming;
};

bool operator==(const Vertex& rhs, const Vertex& lhs);

#endif /* VERTEX_H */
