#ifndef REAL_NETWORK_H
#define REAL_NETWORK_H 

#include <unordered_set>
#include <algorithm>
#include <sstream>
#include <vector>
#include <string>

#include "network.h"


namespace network_models{

  //Simple Classes to read adjacencies list from a file
  template<typename Node>
  class RealDirectedNetwork: public Network<Node>
  {
    public:
      RealDirectedNetwork(std::string file_name);
  };

  template<typename Node>
  class RealUndirectedNetwork: public Network<Node>
  {
    public:
      RealUndirectedNetwork(std::string file_name);
  };

  template<class type>
  std::vector<std::vector<type>>  ReadFile(std::string file_name){
    std::vector<std::vector<type>> data;
    std::string line;
    std::ifstream myfile(file_name.c_str());
    if(myfile.is_open())
    {
      while (myfile.good())
      {
        std::vector<type> values;
        getline(myfile, line);
        if((line.front() != '#') && !line.empty() ){
          std::stringstream line_stream(line);
          type value;
          while(line_stream >> value)
            values.push_back(value);
          data.push_back(values);
        }
      }
      myfile.close();
    }
    else std::cout << "Unable to open file" << std::endl; 
    return data;
  }

  void DataAnalysis(const std::vector<std::vector<unsigned>>& data, std::unordered_map<unsigned, unsigned>& map);
  
  template<typename Node>
  RealDirectedNetwork<Node>::RealDirectedNetwork(std::string file_name) : Network<Node>(0, "Real network"){
    std::vector<std::vector<unsigned>> data(ReadFile<unsigned>(file_name));
    std::unordered_map<unsigned, unsigned> map;
    DataAnalysis(data, map);
    //Creating Vertexes
    for(size_t i(0); i < map.size(); ++i)
      this->NewVertex();
    //Creating network
    Network<Node>& network(*this);
    for(auto& i: data){
      std::cout << map.size() << " " << map[i[0]] << " " << map[i[1]] << std::endl;
      Vertex* v1(&network[map[i[0]]]);
      Vertex* v2(&network[map[i[1]]]);
      v1->Add(Edge(v1, v2));
    }
  }

  template<typename Node>
  RealUndirectedNetwork<Node>::RealUndirectedNetwork(std::string file_name) : Network<Node>(0, "Real network"){
    std::vector<std::vector<unsigned>> data(ReadFile<unsigned>(file_name));
    std::unordered_map<unsigned, unsigned> map;
    DataAnalysis(data, map);
    //Creating Vertexes
    for(size_t i(0); i < map.size(); ++i)
      this->NewVertex();
    //Creating network
    Network<Node>& network(*this);
    for(auto& i: data){
      Vertex* v1(&network[map[i[0]]]);
      Vertex* v2(&network[map[i[1]]]);
      this->CreateUndirectedEdge(v1, v2);
    }
  }

}  //namespace

#endif /* REAL_NETWORK_H */
