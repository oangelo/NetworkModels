#ifndef MEASURES_H
#define MEASURES_H 

#include <deque>
#include <vector>
#include <unordered_set>

#include "network.h"

namespace network_models{
  typedef std::unordered_set<Vertex*> VertexesSet;
  typedef std::vector<Vertex*> Path;
  typedef std::vector<VertexesSet> Paths;

  Paths ShortestPaths(Vertex& begin, Vertex& end, size_t max_iterations);

  class AllShortestPaths{
    public:
      AllShortestPaths(Network& network);
      Paths GetPaths(Vertex& a, Vertex& b);
    private:
      std::unordered_map<Vertex*, std::unordered_map<Vertex*, Paths>> all_spaths; 
  };

  class BetweennessCentrality{
    public:
      BetweennessCentrality(Network& network, AllShortestPaths& paths);
      double GetBetweenness(Vertex* v);
    private:
      std::unordered_map<Vertex*, double> betweenness; 
      void HungerBetweenness(Network& network, AllShortestPaths& paths);
  };

} //namespace network_model

#endif /* MEASURES_H */
