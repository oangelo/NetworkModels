#ifndef MEAN_FIELD_H
#define MEAN_FIELD_H 

#include <random>
#include <iostream>

#include "network.h"


namespace network_models{

  template<typename Node>
  class MeanField: public Network<Node>
  {
    public:
      MeanField(unsigned nodes);
    private:
  };

  template<typename Node>
  MeanField<Node>::MeanField(unsigned nodes)
    :Network<Node>(nodes, "mean-field")
  {
    Network<Node>& network(*this);
    for(size_t i(0); i < nodes; ++i){
      for(size_t j(i + 1); j < nodes; ++j){
          this->CreateUndirectedEdge(&(network[i]), &(network[j]));
      }
    }
  }

} // namespace end

#endif /* MEAN_FIELD_H */
