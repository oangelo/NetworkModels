#ifndef CLUSTERS_H
#define CLUSTERS_H 

#include <unordered_set>
#include <vector>
#include "../network.h"

//Use this when node proprietis are not important
bool StandardCompare(network_models::Vertex& a, network_models::Vertex& b){
    return true;
}

std::unordered_set<network_models::Vertex*> 
Burn(network_models::Vertex& target, bool(*comparison)(network_models::Vertex& a, network_models::Vertex& b));

template <typename vertex_type>
std::vector<std::unordered_set<network_models::Vertex*>> 
Clusters(network_models::Network<vertex_type>& network, 
    bool(*comparison)(network_models::Vertex& a, network_models::Vertex& b)=StandardCompare){
  std::unordered_set<network_models::Vertex*> burned;
  std::vector<std::unordered_set<network_models::Vertex*>> clusters;
  for(auto& i: network){
    if(burned.find(&i) == burned.end()){
      auto aux(Burn(i, comparison));
      clusters.push_back(aux);
      burned.insert(aux.begin(), aux.end());
    }
  }
  return clusters;
}

template<typename node>
std::vector<node*> GiantComponent(network_models::Network<node>& network){
  std::vector<node*> result;
  std::vector<std::unordered_set<network_models::Vertex*>> aux(Clusters(network));
  auto max(std::max_element(aux.begin(), aux.end(), 
        [] (std::unordered_set<network_models::Vertex*> a, std::unordered_set<network_models::Vertex*> b){
          if(a.size() < b.size())
            return true;
          else
            return false;
        }));
  for(auto& i: *max)
    result.push_back(dynamic_cast<node*>(i));
  return(result);
}

#endif /* CLUSTERS_H */
