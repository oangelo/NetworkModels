#include "clusters.h"

using namespace network_models;

std::unordered_set<Vertex*> Burn(Vertex& target, bool(*comparison)(Vertex& a, Vertex& b)){
  std::unordered_set<Vertex*> cluster; 
  std::deque<Vertex*> burning; 

  burning.push_back(&target);
  while(burning.size()){
    Vertex& burning_vertex(*burning.back());
    cluster.insert(burning.back());
    burning.pop_back();
    for(auto& i: burning_vertex){
      Vertex& neighbor(*i.To());
      if(comparison(neighbor, burning_vertex) and cluster.find(&neighbor) == cluster.end()){
        burning.push_back(&neighbor);
      }
    }
  }
  return cluster;
}

template <typename vertex_type>
std::vector<std::unordered_set<Vertex*>> Clusters(network_models::Network<vertex_type>& network, bool(*comparison)(Vertex& a, Vertex& b)){
  std::unordered_set<Vertex*> burned;
  std::vector<std::unordered_set<Vertex*>> clusters;
  for(auto& i: network){
    if(burned.find(&i) == burned.end()){
      auto aux(Burn(i, comparison));
      clusters.push_back(aux);
      burned.insert(aux.begin(), aux.end());
    }
  }
  return clusters;
}
