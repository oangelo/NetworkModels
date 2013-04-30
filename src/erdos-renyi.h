#ifndef ERDOS_RENYI_H
#define ERDOS_RENYI_H 

#include <random>

#include "network.h"


class ErdosRenyi: public Network
{
    public:
        ErdosRenyi(unsigned nodes, unsigned edges);
    private:
        std::random_device random_device;
        std::mt19937 random_gen;
};

#endif /* ERDOS_RENYI_H */
