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
      template<typename Node>
      BetweennessCentrality(Network<Node>& network);
    private:
      template<typename Node>
      void HungerBetweenness(Network<Node>& network);
  };

  inline Path NewPath(Path path, Vertex*& new_vertex);

  inline VertexesSet ToSet(Path& path);

  std::deque<Path> ShortestPaths_Hunger(Vertex& source);

  Paths ShortestPaths(Vertex& begin, Vertex& end, size_t max_iterations);

  VertexesSet  PathVertexSet(Path& path, Vertex& n, Vertex& m);

  PathsMap ShortPaths(Vertex& source, VertexesSet& visited);

  template<typename Node>
  void BetweennessCentrality::HungerBetweenness(Network<Node>& network){
    VertexesSet visited;
    for(Vertex& i: network){
      map[&i] = 0;
    }
    typename Network<Node>::iterator i;
    for(i = network.begin(); i != network.end(); ++i){
      PathsMap paths_map(ShortPaths((*i), visited));
      for(auto& j: paths_map){
        Paths& paths(j.second);
        for(auto& path_vertex_set: paths)
          for(auto& v: path_vertex_set){
            unsigned count_paths(0);
            for(auto& path: j.second){
              auto v_it(path.find(v));
              if(v_it != path.end()){
                ++count_paths;
              }
            }
            if(count_paths > 0){
              map[v] += static_cast<double>(count_paths) / j.second.size();
            }
          }
      }
      visited.insert(&(*i));
    }
  }


  template<typename Node>
  BetweennessCentrality::BetweennessCentrality(Network<Node>& network):Measures(){
    HungerBetweenness(network);
    //normalizing 
    unsigned net_size(network.size());
    double norm((net_size - 1.0) * (net_size - 2.0)/ 2.0);
    for(Vertex& v: network)
      map[&v] = map[&v] / norm;
  }



} //namespace network_model

#endif /* BETWEENNES_H */
