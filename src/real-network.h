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
  class RealDirectedNetwork: public Network
  {
    public:
      RealDirectedNetwork(std::string file_name);
  };

  class RealUndirectedNetwork: public Network
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

}  //namespace

#endif /* REAL_NETWORK_H */
