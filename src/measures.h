#ifndef MEASURES_H
#define MEASURES_H 

#include <deque>
#include <vector>
#include <unordered_set>

#include "network.h"

namespace network_models{
  typedef std::vector<Vertex*> Path;
  typedef std::unordered_set<Vertex*> VertexesSet;

  std::vector<VertexesSet> ShortestPaths(Vertex& begin, Vertex& end, size_t max_iterations);
}

#endif /* MEASURES_H */
