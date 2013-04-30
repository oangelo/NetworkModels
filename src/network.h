#ifndef NETWORK_H
#define NETWORK_H 

#include <vector>

#include "vertex.h"


class Network{
    public:
        Network(unsigned size);
        virtual ~Network() = 0;

        const std::vector<Vertex> get_vertexes();
    private:
        std::vector<Vertex> vertexes;
        void CreateEdge(Vertex* v1, Vertex* v2);
};

#endif /* NETWORK_H */
