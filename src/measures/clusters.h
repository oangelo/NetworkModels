#ifndef CLUSTERS_H
#define CLUSTERS_H 

#include <unordered_set>
#include <vector>
#include "../network.h"

std::unordered_set<network_models::Vertex*> 
Burn(network_models::Vertex& target, bool(*comparison)(network_models::Vertex& a, network_models::Vertex& b));

template <typename vertex_type>
std::vector<std::unordered_set<network_models::Vertex*>> 
Clusters(network_models::Network<vertex_type>& network, bool(*comparison)(network_models::Vertex& a, network_models::Vertex& b));

#endif /* CLUSTERS_H */
