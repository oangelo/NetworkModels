#include "erdos-renyi.h"

ErdosRenyi::ErdosRenyi(unsigned nodes, unsigned edges)
:Network(nodes), random_device(), random_gen(random_device()) 
{
    std::uniform_int_distribution<> dis(0, nodes - 1);
    unsigned random1(0), random2(0);
    for (size_t i = 0; i < edges; ++i)
    {
        while(random1 == random2){
            random1 = dis(random_gen);
            random2 = dis(random_gen);
        }
        CreateEdge(&((*this)[random1]), &((*this)[random2]));
        random1=random2;
    }
}
