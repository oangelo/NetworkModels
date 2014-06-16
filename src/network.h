#ifndef NETWORK_H
#define NETWORK_H 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

#include "vertex.h"

class Network{
    public:
        Vertex& operator[](unsigned index);
        unsigned size() const;

    protected:
        Network(unsigned size);
        virtual ~Network() = 0;

        Vertex* NewVertex();
        void CreateEdge(Vertex* v1, Vertex* v2);
        const std::vector<Vertex> get_vertexes();

    private:
        std::vector<Vertex> vertexes;

};

typedef std::pair<unsigned, unsigned> bin;
std::vector<bin> NodesDistribution(Network& neteork);

void Graphviz(Network& network, std::string file_name);

//Burn for Mark

std::set<Vertex*> Burn(Vertex* vertex);

#endif /* NETWORK_H */
