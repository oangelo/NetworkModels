#include "mean-field.h"

namespace network_models{

  MeanField::MeanField(unsigned nodes)
    :Network(nodes, "mean-field")
  {
    Network& network(*this);
    for(size_t i = 0; i < nodes; ++i){
      for(size_t j = 0; j < nodes; ++j){
        if(i != j)
          CreateEdge(&(network[i]), &(network[j]));
      }
    }
  }

} //namespace end
