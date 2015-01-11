#include "clusters.h"

using namespace network_models;

bool StandardCompare(network_models::Vertex& a, network_models::Vertex& b){
  a;b;
  return true;
}

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

