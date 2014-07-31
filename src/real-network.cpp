#include "real-network.h"

namespace network_models{

  RealNetwork::RealNetwork(std::string file_name) : Network(0, "Real network"){
    std::vector<std::vector<unsigned>> data(ReadFile<unsigned>(file_name));

    //Finding the number of vertex
    std::unordered_set<unsigned> set;
    for(auto& i: data){
      set.insert(i[0]);
      set.insert(i[1]);
    }
    //Creating Vertexes
    for(size_t i(0); i < set.size(); ++i)
      this->NewVertex();
    //Creating network
    Network& network(*this);
    for(auto& i: data){
      Vertex* v1(&network[i[0]]);
      Vertex* v2(&network[i[1]]);
      v1->Add(Edge(v1, v2));
    }
  }

}  //namespace
