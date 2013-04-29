#include "edge.h"


Edge::Edge(Vertex* from, Vertex* to, bool bidirectional)
:from(from), to(to), bidirectional(bidirectional) {}

Vertex* Edge::From() const{
    return from;
}

Vertex* Edge::To() const {
    return to;
}

bool Edge::IsBidirectional() const{
    return bidirectional;
}
