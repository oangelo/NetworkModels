#include "network.h"

Network::Network(unsigned size)
:vertexes(size){}

const std::vector<Vertex> Network::get_vertexes() {
    return vertexes;
}

void Network::CreateEdge(Vertex* v1, Vertex* v2) {
//    Edge edge1(v1, v2);
//    v1->Add(edge1);
}

Network::~Network(){}
