#ifndef VERTEX_H
#define VERTEX_H 

#include <vector>
#include <deque>
#include <cstddef>
#include <iostream>
#include <unordered_map>

#include "edge.h"


namespace network_models{
  class Edge;

  class Vertex{
    public:
      typedef std::deque<Edge> container;
      typedef container::iterator iterator;

      Vertex();

      iterator begin();
      iterator end();

      Vertex& operator[](size_t index);
      Edge& operator()(size_t index);

      Edge* FindIncoming(Vertex* vertex);

      unsigned size() const;

      bool Add(const Edge& element);
      void AddIncoming(Vertex* vertex, Edge* edge);
      void Remove(const Edge& element);

      void SetMark(int i);
      int GetMark() const;

    private:
      Vertex& operator=(Vertex&);
      container edges; 
      int mark;
      std::unordered_map<Vertex*,Edge*> incoming;
  };

  bool operator==(const Vertex& rhs, const Vertex& lhs);
}
#endif /* VERTEX_H */
