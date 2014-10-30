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
      unsigned count(0);
      unsigned count_all(0);
      unsigned max_count_all(100*nodes);
      while(count < edges) 
      {
        if(count_all > max_count_all){
          throw std::range_error("Maximum iterations reached, could not generate Erdos Renyi network.");
        }
        while(random1 == random2){
          random1 = dis(random_gen);
          random2 = dis(random_gen);
        }
        ++count_all;
        try{
          this->CreateUndirectedEdge(&((*this)[random1]), &((*this)[random2]));
          ++count;
        }catch(std::invalid_argument& e){
          random1=random2;
          continue;
        }
        random1=random2;
      }
    }

}

#endif /* ERDOS_RENYI_H */
