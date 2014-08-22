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
}
