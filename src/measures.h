#ifndef MEASURES_H
#define MEASURES_H 

#include <deque>
#include <vector>
#include <unordered_set>

#include "network.h"
#include "measures/eigenvector_centrality.h"

namespace network_models{
  typedef std::unordered_set<Vertex*> VertexesSet;
  typedef std::vector<Vertex*> Path;
  typedef std::vector<VertexesSet> Paths;
  typedef std::unordered_map<Vertex*, Paths> PathsMap;

  Paths ShortestPaths(Vertex& begin, Vertex& end, size_t max_iterations);
  std::deque<Path> ShortestPaths_Hunger(Vertex& begin);

  class BetweennessCentrality{
    public:
      BetweennessCentrality(Network& network);
      double GetBetweenness(Vertex* v);
    private:
      std::unordered_map<Vertex*, double> betweenness; 
      void HungerBetweenness(Network& network);
  };

} //namespace network_model

#endif /* MEASURES_H */
