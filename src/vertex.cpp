#include "vertex.h"

namespace network_models{
  Vertex::Vertex(): edges(), incoming() {}

  Vertex::iterator Vertex::begin(){return edges.begin();}
  Vertex::iterator Vertex::end(){return edges.end();}

  Vertex& Vertex::operator[](size_t index){
    return *edges[index].To();
  }

  Edge& Vertex::operator()(size_t index){
    return edges[index];
  }

  Edge* Vertex::FindIncoming(Vertex* vertex){
    Edge* result(NULL);
    auto search = incoming.find(vertex);
    if(search != incoming.end()) 
      result = (*search).second;
    return result;
  }

  unsigned Vertex::size() const{
    return edges.size();
  }

  void Vertex::Add(const Edge& element){
    if(element.From() != this){
      throw std::invalid_argument("Trying to add an edge that is not from this vertex");
    }
    if(element.To() == this){
      throw std::invalid_argument("Trying to add an edge that will generate a loop.\
                                   Operation not allowed.");
    }
    for(auto edge: edges){
      if(edge.To() == element.To()){
        throw std::invalid_argument("Trying to add an edge that is already in vertex");
      }
    }
    edges.push_back(element);
    element.To()->AddIncoming(this, &edges.back());
  }

  void Vertex::AddIncoming(Vertex* vertex, Edge* edge){
    incoming[vertex] = edge;
  }

  void Vertex::Remove(const Edge& element){
    auto it(std::find(edges.begin(), edges.end(), element));
    if(it == edges.end())
      throw std::invalid_argument("Can't remove Edge!");
    else
      edges.erase(it);
  }

  void Vertex::Remove(const Vertex& vertex){
    auto it(std::find_if(edges.begin(), edges.end(), [&vertex](Edge& edge){return edge.To() == &vertex;}));
    if(it == edges.end())
      throw std::invalid_argument("Can't remove Edge pointing to the given (Vertex)!");
    else
      edges.erase(it);
  }

  bool operator==(const Vertex& rhs, const Vertex& lhs){
    if(&rhs == &lhs)
      return true;
    return false;
  }
}
