#include <iostream>
#include <string>

#include <cstdio>

#include "models/erdos-renyi.h"
#include "models/barabasi-albert.h"

int main(int argc, char *argv[])
{
  using namespace network_models;
    for (int i = 1; i < argc; ++i)
    {
        if(std::string(argv[i]) == std::string("--erdos-renyi"))
        {
            unsigned nodes = atoi(argv[i + 1]);
            unsigned edges = atoi(argv[i + 2]);
            ErdosRenyi<Vertex> network(nodes, edges);
            NodesDistribution(network);
        }
        if(std::string(argv[i]) == std::string("--barabasi-albert"))
        {
            unsigned size = atoi(argv[i + 1]);
            unsigned connections = atoi(argv[i + 2]);
            unsigned initial_population = atoi(argv[i + 3]);
            BarabasiAlbert<Vertex> network(size, connections, initial_population);
            NodesDistribution(network);
        }

    }
    return EXIT_SUCCESS;
}

