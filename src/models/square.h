#ifndef SQUARE_H
#define SQUARE_H 

#include <random>
#include <iostream>

#include "../network.h"


namespace network_models{

  template<typename Node>
  class Square: public Network<Node>
  {
    public:
      Square(unsigned nodes);
    private:
  };

  template<typename Node>
  Square<Node>::Square(unsigned nodes)
    :Network<Node>(nodes, "square")
  {
    unsigned m(sqrt(nodes));
    for (size_t i = 0; i < nodes; ++i)
    {
        if((i + 1) % m != 0)
          this->CreateUndirectedEdge(&((*this)[i]), &((*this)[i + 1]));
        if(i >= m)
          this->CreateUndirectedEdge(&((*this)[i]), &((*this)[i - m]));
    }
  }


} //namespace end
#endif /* SQUARE_H */
