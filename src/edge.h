#ifndef EDGE_H
#define EDGE_H 

#include "vertex.h"

namespace network_models{
  class Vertex;

  class Edge{
    public:
      Edge(Vertex* from, Vertex* to);
      Vertex* From() const;
      Vertex* To() const;
      int property;
    private:
      Vertex* from;
      Vertex* to;
  };


  bool operator==(const Edge& rhs, const Edge& lhs);
}

#endif /* EDGE_H */
