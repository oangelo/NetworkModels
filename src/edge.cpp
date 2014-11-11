#include "edge.h"


namespace network_models{
  Edge::Edge(Vertex* from, Vertex* to)
    :property(0), from(from), to(to) {}

  Vertex* Edge::From() const{
    return from;
  }

  Vertex* Edge::To() const {
    return to;
  }

  bool operator==(const Edge& rhs, const Edge& lhs){
    if(rhs.To() == lhs.To() and rhs.From() == lhs.From())
      return true;
    else
      return false;
  }
}
