#include <iostream>
#include <string>

#include <cstdio>

#include "erdos-renyi.h"

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        if(std::string(argv[i]) == std::string("--solicitation-model"))
        {
            unsigned population = atoi(argv[i + 1]);
            unsigned advertisers_amount = atoi(argv[i + 2]);
            double probability_of_success = atof(argv[i + 3]);
//            PreferentialAttachment(population, advertisers_amount, probability_of_success);
        }
        if(std::string(argv[i]) == std::string("--erdos-renyi"))
        {
            unsigned nodes = atoi(argv[i + 1]);
            unsigned edges = atoi(argv[i + 2]);
            ErdosRenyi network(nodes, edges);
            NodesDistribution(network);
        }
    }
    return EXIT_SUCCESS;
}

