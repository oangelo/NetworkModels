#include "edge.h"


namespace network_models{
  Edge::Edge(Vertex* from, Vertex* to, bool bidirectional)
    :from(from), to(to), bidirectional(bidirectional), mark(0) {}

  Vertex* Edge::From() const{
    return from;
  }

  Vertex* Edge::To() const {
    return to;
  }

  bool Edge::IsBidirectional() const{
    return bidirectional;
  }

  void Edge::SetMark(int i){ mark = i; }
  int Edge::GetMark() const{ return(mark); }

  bool operator==(const Edge& rhs, const Edge& lhs){
    if(rhs.To() == lhs.To() and rhs.From() == lhs.From())
      return true;
    else
      return false;
  }
}
