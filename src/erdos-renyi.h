#ifndef ERDOS_RENYI_H
#define ERDOS_RENYI_H 

#include <random>
#include <iostream>

#include "network.h"

namespace network_models{

  template<typename Node>
  class ErdosRenyi: public Network<Node>
  {
    public:
      ErdosRenyi(unsigned nodes, unsigned edges);
    private:
      std::random_device random_device;
      std::mt19937 random_gen;
  };

  template<typename Node>
  ErdosRenyi<Node>::ErdosRenyi(unsigned nodes, unsigned edges)
    :Network<Node>(nodes, "erdos-renyi"), random_device(), random_gen(random_device()) 
  {
    std::uniform_int_distribution<> dis(0, nodes - 1);
    unsigned random1(0), random2(0);
    for (size_t i = 0; i < edges; ++i)
    {
      while(random1 == random2){
        random1 = dis(random_gen);
        random2 = dis(random_gen);
      }
      this->CreateUndirectedEdge(&((*this)[random1]), &((*this)[random2]));
      random1=random2;
    }
  }

}

#endif /* ERDOS_RENYI_H */
