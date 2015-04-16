#ifndef VERTEX_H
#define VERTEX_H 

#include <vector>
#include <deque>
#include <cstddef>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>

#include "edge.h"


namespace network_models{
  class Edge;

  class Vertex{
    public:
      typedef std::deque<Edge> container;
      typedef container::iterator iterator;

      Vertex();
      virtual ~Vertex(){};

      iterator begin();
      iterator end();

      //This is virtual to return the 
      //correct type when derived
      virtual Vertex& operator[](size_t index);
      Edge& operator()(size_t index);

      unsigned size() const;

      void Add(const Edge& element);
      void Remove(const Edge& element);
      void Remove(const Vertex& vertex);

    protected:
      container edges; 

    private:
      Vertex& operator=(Vertex&);
      std::unordered_map<Vertex*,Edge*> incoming;

  };

  bool operator==(const Vertex& rhs, const Vertex& lhs);

}
#endif /* VERTEX_H */
