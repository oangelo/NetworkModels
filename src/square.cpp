#include "square.h"

namespace network_models{

  Square::Square(unsigned nodes)
    :Network(nodes, "square")
  {
    unsigned m(sqrt(nodes));
    for (size_t i = 0; i < nodes; ++i)
    {
      if(i > 0 and i % m != 0)
        CreateEdge(&((*this)[i]), &((*this)[i - 1]));
      if((i + 1) % m != 0)
        CreateEdge(&((*this)[i]), &((*this)[i + 1]));
      if(i >= m)
        CreateEdge(&((*this)[i]), &((*this)[i - m]));
      if(i < nodes - m - 1)
        CreateEdge(&((*this)[i]), &((*this)[i + m]));
    }
  }

} //namespace end
