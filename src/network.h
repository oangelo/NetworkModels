#ifndef NETWORK_H
#define NETWORK_H 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>

#include "vertex.h"

class Network{
    public:
        Vertex& operator[](unsigned index);
        unsigned size() const;
        std::string GetModelName();
        double GetMeanConnectivity();

    protected:
        Network(unsigned size, std::string model_name);
        virtual ~Network() = 0;

        Vertex* NewVertex();
        void CreateEdge(Vertex* v1, Vertex* v2);
        const std::vector<Vertex> get_vertexes();

    private:
        std::vector<Vertex> vertexes;
        std::string model_name;
        //the Network class should never be copied!
        Network& operator=(const Network& network);
        Network(const Network& network);
};

typedef std::pair<unsigned, unsigned> bin;
std::vector<bin> NodesDistribution(Network& neteork);

void Graphviz(Network& network, std::string file_name);

//Burn for Mark

std::set<Vertex*> Burn(Vertex* vertex);
std::map<int,std::vector<unsigned>> Clusters(Network& network);

#endif /* NETWORK_H */
