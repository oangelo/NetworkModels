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
      virtual ~Vertex(){};

      iterator begin();
      iterator end();

      virtual Vertex& operator[](size_t index);
      Edge& operator()(size_t index);

      Edge* FindIncoming(Vertex* vertex);

      unsigned size() const;

      bool Add(const Edge& element);
      void AddIncoming(Vertex* vertex, Edge* edge);
      void Remove(const Edge& element);

      void SetMark(int i);
      int GetMark() const;

    protected:
      container edges; 

    private:
      Vertex& operator=(Vertex&);
      int mark;
      std::unordered_map<Vertex*,Edge*> incoming;
  };

  bool operator==(const Vertex& rhs, const Vertex& lhs);
}
#endif /* VERTEX_H */
