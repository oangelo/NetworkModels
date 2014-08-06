#include "real-network.h"

namespace network_models{

  void DataAnalysis(const std::vector<std::vector<unsigned>>& data, std::unordered_map<unsigned, unsigned>& map){
    //Finding the number of vertex
    std::unordered_set<unsigned> set;
    for(auto& i: data){
      set.insert(i[0]);
      set.insert(i[1]);
    }
    unsigned counter(0);
    for(auto& i: set){
      map[i] = counter;
      ++counter;
    }
  }

  RealDirectedNetwork::RealDirectedNetwork(std::string file_name) : Network(0, "Real network"){
    std::vector<std::vector<unsigned>> data(ReadFile<unsigned>(file_name));
    std::unordered_map<unsigned, unsigned> map;
    DataAnalysis(data, map);
    //Creating Vertexes
    for(size_t i(0); i < map.size(); ++i)
      this->NewVertex();
    //Creating network
    Network& network(*this);
    for(auto& i: data){
      std::cout << map.size() << " " << map[i[0]] << " " << map[i[1]] << std::endl;
      Vertex* v1(&network[map[i[0]]]);
      Vertex* v2(&network[map[i[1]]]);
      v1->Add(Edge(v1, v2));
    }
  }

  RealUndirectedNetwork::RealUndirectedNetwork(std::string file_name) : Network(0, "Real network"){
    std::vector<std::vector<unsigned>> data(ReadFile<unsigned>(file_name));
    std::unordered_map<unsigned, unsigned> map;
    DataAnalysis(data, map);
    //Creating Vertexes
    for(size_t i(0); i < map.size(); ++i)
      this->NewVertex();
    //Creating network
    Network& network(*this);
    for(auto& i: data){
      Vertex* v1(&network[map[i[0]]]);
      Vertex* v2(&network[map[i[1]]]);
      CreateUndirectedEdge(v1, v2);
    }
  }

}  //namespace
