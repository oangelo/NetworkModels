#ifndef BETWEENNES_H
#define BETWEENNES_H 

#include <unordered_set>

#include "../network.h"
#include "interface.h"

namespace network_models{
  typedef std::unordered_set<Vertex*> VertexesSet;
  typedef std::vector<Vertex*> Path;
  typedef std::vector<VertexesSet> Paths;
  typedef std::unordered_map<Vertex*, Paths> PathsMap;

  Paths ShortestPaths(Vertex& begin, Vertex& end, size_t max_iterations);
  std::deque<Path> ShortestPaths_Hunger(Vertex& begin);

  class BetweennessCentrality: public Measures{
    public:
      BetweennessCentrality(Network& network);
    private:
      void HungerBetweenness(Network& network);
  };

} //namespace network_model

#endif /* BETWEENNES_H */
